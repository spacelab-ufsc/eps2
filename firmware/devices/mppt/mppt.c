/*
 * mppt.c
 *
 * Copyright (C) 2021, SpaceLab.
 *
 * This file is part of EPS 2.0.
 *
 * EPS 2.0 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EPS 2.0 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EPS 2.0. If not, see <http:/\/www.gnu.org/licenses/>.
 *
 */

/**
 * \brief MPPT device implementation.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * \author João Cláudio <joaoclaudiobarcellos@gmail.com>
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * \author Ramon de Araujo Borba <ramonborba97@gmail.com>
 *
 * \version 0.4.0
 *
 * \date 2021/02/10
 *
 * \addtogroup mppt
 * \{
 */
#include <system/sys_log/sys_log.h>

#include "mppt.h"

#if defined _UNIT_TEST_
    #define STATIC
#else
    #define STATIC static
#endif

/**
 * \brief Array of parameters for each channel
 * 
 */
STATIC mppt_paramemters_t mppt_channel_params[] = {
                        {   .channel = MPPT_CONTROL_LOOP_CH_0,
                            .config = { .period_us = MPPT_PERIOD_INIT, .duty_cycle = MPPT_DUTY_CYCLE_INIT },
                            .pwr_meas = { 0 },
                            .step = INCREASE_STEP,
                            .prev_step = DECREASE_STEP },

                        {   .channel = MPPT_CONTROL_LOOP_CH_1,
                            .config = { .period_us = MPPT_PERIOD_INIT, .duty_cycle = MPPT_DUTY_CYCLE_INIT },
                            .pwr_meas = { 0 },
                            .step = INCREASE_STEP,
                            .prev_step = DECREASE_STEP },

                        {   .channel = MPPT_CONTROL_LOOP_CH_2,
                            .config = { .period_us = MPPT_PERIOD_INIT, .duty_cycle = MPPT_DUTY_CYCLE_INIT },
                            .pwr_meas = { 0 },
                            .step = INCREASE_STEP,
                            .prev_step = DECREASE_STEP }
                            };

/**
 * \brief Read power measurement from a given MPPT control loop channel.
 *
 * \param[in] channel is the control loop channel to be used.
 *
 * \return The status/error code.
 */
static int read_ch_power(mppt_paramemters_t *params);

/**
 * \brief Update PWM step from a given MPPT control loop channel.
 *
 * \param[in] channel is the control loop channel to be used.
 *
 */
static void update_step(mppt_paramemters_t *params);

/**
 * \brief Update PWM duty cycle from a given MPPT control loop channel.
 *
 * \param[in] channel is the control loop channel to be used.
 *
 */
static void update_duty_cycle(mppt_paramemters_t *params);


int mppt_init(void)
{
    int err = 0;
    sys_log_print_event_from_module(SYS_LOG_INFO, MPPT_MODULE_NAME, "Initializing MPPT device.");
    sys_log_new_line();

    /* Initialize the PWM parameters */
    const mppt_config_t config = { .period_us = MPPT_PERIOD_INIT, .duty_cycle = MPPT_DUTY_CYCLE_INIT };

    if(pwm_init(MPPT_CONTROL_LOOP_CH_SOURCE, MPPT_CONTROL_LOOP_CH_0, config) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, MPPT_MODULE_NAME, "Error during the initialization (CH0)!");
        sys_log_new_line();
        err += -1;
    }

    if(pwm_init(MPPT_CONTROL_LOOP_CH_SOURCE, MPPT_CONTROL_LOOP_CH_1, config) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, MPPT_MODULE_NAME, "Error during the initialization (CH1)!");
        sys_log_new_line();
        err += -1;
    }

    if(pwm_init(MPPT_CONTROL_LOOP_CH_SOURCE, MPPT_CONTROL_LOOP_CH_2, config) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, MPPT_MODULE_NAME, "Error during the initialization (CH2)!");
        sys_log_new_line();
        err += -1;
    }

    return err;
}

int mppt_algorithm(mppt_channel_t channel)
{
    int err = 0;

    /* convert mppt channel defines, that map to pwm ports which are 1 indexed, to 0 indexing */
    const uint8_t channel_index = channel - 1;

    /* Point to correct channel */
    mppt_paramemters_t *params = &mppt_channel_params[channel_index];

    if (read_ch_power(params) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, MPPT_MODULE_NAME, "Error reading MPPT channel power!");
        sys_log_new_line();
        err += -1;
    }
    else
    {
        update_step(params);
        update_duty_cycle(params);

        if (pwm_update(MPPT_CONTROL_LOOP_CH_SOURCE, params->channel, params->config) != 0)
        {
            sys_log_print_event_from_module(SYS_LOG_ERROR, MPPT_MODULE_NAME, "Error updating MPPT channel duty cycle!");
            sys_log_new_line();
            err += -1;
        }
    }

    return err;
}


int mppt_set_duty_cycle(mppt_channel_t channel, uint32_t duty_cycle)
{
    const mppt_config_t config = { .period_us = MPPT_PERIOD_INIT, .duty_cycle = duty_cycle };
    return pwm_update(MPPT_CONTROL_LOOP_CH_SOURCE, channel, config);
}


static int read_ch_power(mppt_paramemters_t *params)
{
    int err = 0;

    uint16_t current0;
    uint16_t current1;
    uint16_t voltage;

    switch(params->channel)
    {
        case MPPT_CONTROL_LOOP_CH_0:
            err += current_sensor_read(MPPT_CURRENT_SENSOR_0_CH_0, &current0);
            err += current_sensor_read(MPPT_CURRENT_SENSOR_1_CH_0, &current1);
            err += voltage_sensor_read(MPPT_VOLTAGE_SENSOR_CH_0, &voltage);
            break;
        case MPPT_CONTROL_LOOP_CH_1:
            err += current_sensor_read(MPPT_CURRENT_SENSOR_0_CH_1, &current0);
            err += current_sensor_read(MPPT_CURRENT_SENSOR_1_CH_1, &current1);
            err += voltage_sensor_read(MPPT_VOLTAGE_SENSOR_CH_1, &voltage);
            break;
        case MPPT_CONTROL_LOOP_CH_2:
            err += current_sensor_read(MPPT_CURRENT_SENSOR_0_CH_2, &current0);
            err += current_sensor_read(MPPT_CURRENT_SENSOR_1_CH_2, &current1);
            err += voltage_sensor_read(MPPT_VOLTAGE_SENSOR_CH_2, &voltage);
            break;

        default:
            err += -1;
            break;
    }

    params->pwr_meas.prev_power = params->pwr_meas.power;
    params->pwr_meas.power = (((uint32_t)current0 + (uint32_t)current1) * (uint32_t)voltage);

    return err;
}

static void update_step(mppt_paramemters_t *params)
{

    if (params->pwr_meas.power == 0U)
    {
        params->step = DECREASE_STEP;
    }
    else
    {
        if (params->pwr_meas.power >= params->pwr_meas.prev_power)
        {
            params->step = params->prev_step;
        }
        else
        {
            params->step = (params->prev_step == INCREASE_STEP) ? DECREASE_STEP : INCREASE_STEP;
        }
    }

    params->prev_step = params->step;

}

static void update_duty_cycle(mppt_paramemters_t *params)
{
    switch (params->step)
    {
    case INCREASE_STEP:
        if (params->config.duty_cycle >= MPPT_MAX_DUTY_CYCLE)
        {
            params->config.duty_cycle = MPPT_MAX_DUTY_CYCLE;
        }
        else
        {
            params->config.duty_cycle += MPPT_DUTY_CYCLE_STEP;
        }
        break;

    case DECREASE_STEP:
        if (params->config.duty_cycle <= MPPT_MIN_DUTY_CYCLE)
        {
            params->config.duty_cycle = MPPT_MIN_DUTY_CYCLE;
        }
        else
        {
            params->config.duty_cycle -= MPPT_DUTY_CYCLE_STEP;
        }
        break;

    default:
        sys_log_print_event_from_module(SYS_LOG_ERROR, MPPT_MODULE_NAME, "Error: invalid pwm step!");
        sys_log_new_line();
        break;
    }

}

/** \} End of mppt group */
