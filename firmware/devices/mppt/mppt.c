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
 * along with EPS 2.0. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief MPPT device implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * \author Jo�o Cl�udio <joaoclaudiobarcellos@gmail.com>
 * \author Andr� M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * 
 * \version 0.2.22
 * 
 * \date 2021/02/10
 * 
 * \addtogroup mppt
 * \{
 */
#include <system/sys_log/sys_log.h>

#include "mppt.h"

mppt_config_t mppt_config;

power_measurement_t power_measurement;
duty_cycle_measurement_t duty_cycle_measurement;
previous_values_t previous_values;

/**
 * \brief Get power from a given MPPT control loop channel.
 *
 * \param[in] channel is the control loop channel to be used.
 *
 * \return The status/error code.
 */
int get_power(mppt_channel_t channel);

/**
 * \brief Get power from a given MPPT control loop channel.
 *
 * \param[in] channel is the control loop channel to be used.
 *
 * \return None.
 */
void get_duty_cycle(mppt_channel_t channel);

/**
 * \brief Get power from a given MPPT control loop channel.
 *
 * \param[in] channel is the control loop channel to be used.
 *
 * \return The status/error code.
 */
int increase_duty_cycle(mppt_channel_t channel);

/**
 * \brief Get power from a given MPPT control loop channel.
 *
 * \param[in] channel is the control loop channel to be used.
 *
 * \return The status/error code.
 */
int decrease_duty_cycle(mppt_channel_t channel);

int read_ch_power(mppt_paramemters_t *params);

void update_step(mppt_paramemters_t *params);

void update_duty_cycle(mppt_paramemters_t *params);

int mppt_init(void)
{
    sys_log_print_event_from_module(SYS_LOG_INFO, MPPT_MODULE_NAME, "Initializing MPPT device.");
    sys_log_new_line();

    /* Initialize the PWM parameters */
    const mppt_config_t config = { .period_us = MPPT_PERIOD_INIT, .duty_cycle = MPPT_DUTY_CYCLE_INIT };

    if(pwm_init(MPPT_CONTROL_LOOP_CH_SOURCE, MPPT_CONTROL_LOOP_CH_0, config) != 0) 
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, MPPT_MODULE_NAME, "Error during the initialization (CH0)!");
        sys_log_new_line();
        return -1;
    }

    if(pwm_init(MPPT_CONTROL_LOOP_CH_SOURCE, MPPT_CONTROL_LOOP_CH_1, config) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, MPPT_MODULE_NAME, "Error during the initialization (CH1)!");
        sys_log_new_line();
        return -1;
    }

    if(pwm_init(MPPT_CONTROL_LOOP_CH_SOURCE, MPPT_CONTROL_LOOP_CH_2, config) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, MPPT_MODULE_NAME, "Error during the initialization (CH2)!");
        sys_log_new_line();
        return -1;
    }

    return 0;
}

int mppt_algorithm(mppt_channel_t channel)
{
    int err = 0;
    
    static mppt_paramemters_t mppt_channel_params[] = {
        (mppt_paramemters_t){    .channel = MPPT_CONTROL_LOOP_CH_0,
                                .config = { .period_us = MPPT_PERIOD_INIT, .duty_cycle = MPPT_DUTY_CYCLE_INIT },
                                .power = 0,
                                .prev_power=0,
                                .step = INCREASE_STEP,
                                .prev_step = DECREASE_STEP },

        (mppt_paramemters_t){   .channel = MPPT_CONTROL_LOOP_CH_1,
                                .config = { .period_us = MPPT_PERIOD_INIT, .duty_cycle = MPPT_DUTY_CYCLE_INIT },
                                .power = 0,
                                .prev_power=0,
                                .step = INCREASE_STEP,
                                .prev_step = DECREASE_STEP },

        (mppt_paramemters_t){   .channel = MPPT_CONTROL_LOOP_CH_2,
                                .config = { .period_us = MPPT_PERIOD_INIT, .duty_cycle = MPPT_DUTY_CYCLE_INIT },
                                .power = 0,
                                .prev_power=0,
                                .step = INCREASE_STEP,
                                .prev_step = DECREASE_STEP }    };
    
    mppt_paramemters_t *params = &mppt_channel_params[channel];
    
    
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

void get_duty_cycle(mppt_channel_t channel)
{
    switch(channel)
    {
        case MPPT_CONTROL_LOOP_CH_0:
            duty_cycle_measurement.duty_cycle = mppt_config.duty_cycle;
            duty_cycle_measurement.previous_duty_cycle = previous_values.previous_duty_cycle_ch_0;
            break;
        case MPPT_CONTROL_LOOP_CH_1:
            duty_cycle_measurement.duty_cycle = mppt_config.duty_cycle;
            duty_cycle_measurement.previous_duty_cycle = previous_values.previous_duty_cycle_ch_1;
            break;
        case MPPT_CONTROL_LOOP_CH_2:
            duty_cycle_measurement.duty_cycle = mppt_config.duty_cycle;
            duty_cycle_measurement.previous_duty_cycle = previous_values.previous_duty_cycle_ch_2;
            break;
    }
}

int get_power(mppt_channel_t channel)
{
    uint16_t current_0 = 0;
    uint16_t current_1 = 0;
    uint16_t voltage = 0;

    int err = 0;

    switch(channel)
    {
        case MPPT_CONTROL_LOOP_CH_0:
            err |= current_sensor_read(MPPT_CURRENT_SENSOR_0_CH_0, &current_0);
            err |= current_sensor_read(MPPT_CURRENT_SENSOR_1_CH_0, &current_1);
            err |= voltage_sensor_read(MPPT_VOLTAGE_SENSOR_CH_0, &voltage);
            power_measurement.power = (current_0 + current_1) * (uint32_t)voltage;
            power_measurement.previous_power = previous_values.previous_power_ch_0;
            break;
        case MPPT_CONTROL_LOOP_CH_1:
            err |= current_sensor_read(MPPT_CURRENT_SENSOR_0_CH_1, &current_0);
            err |= current_sensor_read(MPPT_CURRENT_SENSOR_1_CH_1, &current_1);
            err |= voltage_sensor_read(MPPT_VOLTAGE_SENSOR_CH_1, &voltage);
            power_measurement.power = (current_0 + current_1) * (uint32_t)voltage;
            power_measurement.previous_power = previous_values.previous_power_ch_1;
            break;
        case MPPT_CONTROL_LOOP_CH_2:
            err |= current_sensor_read(MPPT_CURRENT_SENSOR_0_CH_2, &current_0);
            err |= current_sensor_read(MPPT_CURRENT_SENSOR_1_CH_2, &current_1);
            err |= voltage_sensor_read(MPPT_VOLTAGE_SENSOR_CH_2, &voltage);
            power_measurement.power = (current_0 + current_1) * (uint32_t)voltage;
            power_measurement.previous_power = previous_values.previous_power_ch_2;
            break;
    }

    if(err != 0)
    {
        return -1;
    }
    
    return 0;
}

int increase_duty_cycle(mppt_channel_t channel)
{   
    if(mppt_config.duty_cycle >= MPPT_MAX_DUTY_CYCLE)
    {
        mppt_config.duty_cycle = MPPT_MAX_DUTY_CYCLE;
        return pwm_update(MPPT_CONTROL_LOOP_CH_SOURCE, channel, mppt_config);
    }
    else
    {
        mppt_config.duty_cycle += MPPT_DUTY_CYCLE_STEP;
        return pwm_update(MPPT_CONTROL_LOOP_CH_SOURCE, channel, mppt_config);
    }
}

int decrease_duty_cycle(mppt_channel_t channel)
{
    if(mppt_config.duty_cycle == MPPT_MIN_DUTY_CYCLE)
    {
        mppt_config.duty_cycle = MPPT_MIN_DUTY_CYCLE;
        return pwm_update(MPPT_CONTROL_LOOP_CH_SOURCE, channel, mppt_config);
    }
    else
    {
        mppt_config.duty_cycle -= MPPT_DUTY_CYCLE_STEP;
        return pwm_update(MPPT_CONTROL_LOOP_CH_SOURCE, channel, mppt_config);    
    }
}

int mppt_set_duty_cycle(mppt_channel_t channel, uint32_t duty_cycle)
{
    const mppt_config_t config = { .period_us = MPPT_PERIOD_INIT, .duty_cycle = duty_cycle };
    return pwm_update(MPPT_CONTROL_LOOP_CH_SOURCE, channel, config);
}


int read_ch_power(mppt_paramemters_t *params)
{
    int err = 0;

    uint16_t current_0 = 0;
    uint16_t current_1 = 0;
    uint16_t voltage = 0;
    
    switch(params->channel)
    {
        case MPPT_CONTROL_LOOP_CH_0:
            err += current_sensor_read(MPPT_CURRENT_SENSOR_0_CH_0, &current_0);
            err += current_sensor_read(MPPT_CURRENT_SENSOR_1_CH_0, &current_1);
            err += voltage_sensor_read(MPPT_VOLTAGE_SENSOR_CH_0, &voltage);
            break;
        case MPPT_CONTROL_LOOP_CH_1:
            err += current_sensor_read(MPPT_CURRENT_SENSOR_0_CH_1, &current_0);
            err += current_sensor_read(MPPT_CURRENT_SENSOR_1_CH_1, &current_1);
            err += voltage_sensor_read(MPPT_VOLTAGE_SENSOR_CH_1, &voltage);
            break;
        case MPPT_CONTROL_LOOP_CH_2:
            err += current_sensor_read(MPPT_CURRENT_SENSOR_0_CH_2, &current_0);
            err += current_sensor_read(MPPT_CURRENT_SENSOR_1_CH_2, &current_1);
            err += voltage_sensor_read(MPPT_VOLTAGE_SENSOR_CH_2, &voltage);
            break;
            
        default:
            err += -1;
    }
    
    // uint16_t new_power = moving_avg();
    params->prev_power = params->power;
    params->power = (current_0 + current_1) * voltage;
    
    return err;
}

void update_step(mppt_paramemters_t *params)
{

    if (params->power > params->prev_power)
    {
        params->step = params->prev_step;
    }
    else
    {
        params->step = params->prev_step ? DECREASE_STEP : INCREASE_STEP;
    }
    
}

void update_duty_cycle(mppt_paramemters_t *params)
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
