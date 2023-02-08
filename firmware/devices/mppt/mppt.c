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

int mppt_init(void)
{
    sys_log_print_event_from_module(SYS_LOG_INFO, MPPT_MODULE_NAME, "Initializing the MPPT...");
    sys_log_new_line();

    /* Initialize the PWM parameters */
    mppt_config.period_us = MPPT_PERIOD_INIT;
    mppt_config.duty_cycle = MPPT_DUTY_CYCLE_INIT;

    if(pwm_init(MPPT_CONTROL_LOOP_CH_SOURCE, MPPT_CONTROL_LOOP_CH_0, mppt_config) != 0) 
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, MPPT_MODULE_NAME, "Error during the initialization (CH0)!");
        sys_log_new_line();
        return -1;
    }

    if(pwm_init(MPPT_CONTROL_LOOP_CH_SOURCE, MPPT_CONTROL_LOOP_CH_1, mppt_config) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, MPPT_MODULE_NAME, "Error during the initialization (CH1)!");
        sys_log_new_line();
        return -1;
    }

    if(pwm_init(MPPT_CONTROL_LOOP_CH_SOURCE, MPPT_CONTROL_LOOP_CH_2, mppt_config) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, MPPT_MODULE_NAME, "Error during the initialization (CH2)!");
        sys_log_new_line();
        return -1;
    }

    return 0;
}

int mppt_algorithm(mppt_channel_t channel)
{
    if(get_power(channel) != 0) 
    {
        return -1;
    }
    get_duty_cycle(channel);

    if(power_measurement.power > power_measurement.previous_power)                          /* P(x)-P(x-1)>0 */
    {                         
        if(duty_cycle_measurement.duty_cycle > duty_cycle_measurement.previous_duty_cycle)  /* PWM(x)-PWM(x-1)>0 */
        {
            if(increase_duty_cycle(channel) != 0) 
            {
                return -1;
            }
        }
        else
        {
            if(decrease_duty_cycle(channel) != 0) 
            {
                return -1;
            }
        }
    }
    else                                                                                    /* P(x)-P(x-1)<0 */
    {                                                                                   
        if(duty_cycle_measurement.duty_cycle < duty_cycle_measurement.previous_duty_cycle)  /* PWM(x)-PWM(x-1)<0 */
        {
            if(increase_duty_cycle(channel) != 0) 
            {
                return -1;
            }
        }
        else
        {
            if(decrease_duty_cycle(channel) != 0) 
            {
                return -1;
            }
        }
    }

    switch(channel)
    {
        case MPPT_CONTROL_LOOP_CH_0:
            previous_values.previous_power_ch_0 = power_measurement.power;
            previous_values.previous_duty_cycle_ch_0 = duty_cycle_measurement.duty_cycle;
            break;
        case MPPT_CONTROL_LOOP_CH_1:
            previous_values.previous_power_ch_1 = power_measurement.power;
            previous_values.previous_duty_cycle_ch_1 = duty_cycle_measurement.duty_cycle;
            break;
        case MPPT_CONTROL_LOOP_CH_2:
            previous_values.previous_power_ch_2 = power_measurement.power;
            previous_values.previous_duty_cycle_ch_2 = duty_cycle_measurement.duty_cycle;
            break;
    }

    return 0;
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
    mppt_config.duty_cycle = duty_cycle;
    return pwm_update(MPPT_CONTROL_LOOP_CH_SOURCE, channel, mppt_config);
}


/** \} End of mppt group */
