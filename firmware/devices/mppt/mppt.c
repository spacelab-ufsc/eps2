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
 * \author João Cláudio <joaoclaudiobarcellos@gmail.com>
 * 
 * \version 0.1.3
 * 
 * \date 2021/02/10
 * 
 * \addtogroup mppt
 * \{
 */
#include <system/sys_log/sys_log.h>

#include "mppt.h"


int mppt_init()
{

    sys_log_print_event_from_module(SYS_LOG_INFO, MPPT_MODULE_NAME, "Initializing the MPPT...");
    sys_log_new_line();

    pwm_config_t initial_pwm_config;
    initial_pwm_config.duty_cycle=50;
    initial_pwm_config.period_us=2;


    pwm_init(TIMER_B0, PWM_PORT_0, initial_pwm_config);
    pwm_init(TIMER_B0, PWM_PORT_1, initial_pwm_config);
    pwm_init(TIMER_B0, PWM_PORT_2, initial_pwm_config);

    return 0;
}

/*
 * Function to implement the P&O MPPT algorithm
 *
 */

int update_duty_cycle(pwm_port_t port, pwm_config_t config)
{
    get_power(port);
    get_duty_cycle(port,config);

    if(power_measurement.power > power_measurement.previous_power){                         // P(x)-P(x-1)>0
        if(duty_cycle_measurement.duty_cycle > duty_cycle_measurement.previous_duty_cycle)  // PWM(x)-PWM(x-1)>0
        {
            increase_duty_cycle(config, port);
        }
        else
        {
            decrease_duty_cycle(config, port);
        }
    }
    else{                                                                                   // P(x)-P(x-1)<0
        if(duty_cycle_measurement.duty_cycle < duty_cycle_measurement.previous_duty_cycle)  // PWM(x)-PWM(x-1)<0
        {
            increase_duty_cycle(config, port);
        }
        else
        {
            decrease_duty_cycle(config, port);

        }
    }

    switch(port)
    {
        case PWM_PORT_0:
            previous_values.previous_power_PWM_0 = power_measurement.power;
            previous_values.previous_duty_cycle_PWM_0 = duty_cycle_measurement.duty_cycle;
            break;
        case PWM_PORT_1:
            previous_values.previous_power_PWM_1 = power_measurement.power;
            previous_values.previous_duty_cycle_PWM_1 = duty_cycle_measurement.duty_cycle;
            break;
        case PWM_PORT_2:
            previous_values.previous_power_PWM_2 = power_measurement.power;
            previous_values.previous_duty_cycle_PWM_2 = duty_cycle_measurement.duty_cycle;
            break;
    }
    return 0;
}


int get_duty_cycle(pwm_port_t port, pwm_config_t config)
{
    switch(port)
        {
            case PWM_PORT_0:
                duty_cycle_measurement.duty_cycle = config.duty_cycle;
                duty_cycle_measurement.previous_duty_cycle = previous_values.previous_duty_cycle_PWM_0;
                break;
            case PWM_PORT_1:
                duty_cycle_measurement.duty_cycle = config.duty_cycle;
                duty_cycle_measurement.previous_duty_cycle = previous_values.previous_duty_cycle_PWM_1;
                break;
            case PWM_PORT_2:
                duty_cycle_measurement.duty_cycle = config.duty_cycle;
                duty_cycle_measurement.previous_duty_cycle = previous_values.previous_duty_cycle_PWM_2;
                break;
        }
        return 0;

}

int get_power(pwm_port_t port)
{
    uint16_t current_1 = 0;
    uint16_t current_2 = 0;
    uint16_t voltage = 0;

    switch(port)
    {
        case PWM_PORT_0:
            current_sensor_read(ADC_PORT_0, &current_1);
            current_sensor_read(ADC_PORT_1, &current_2);
            voltage_sensor_read(ADC_PORT_12, &voltage);
            power_measurement.power = (current_1+current_2)*voltage;
            power_measurement.previous_power = previous_values.previous_power_PWM_0;
            break;
        case PWM_PORT_1:
            current_sensor_read(ADC_PORT_2, &current_1);
            current_sensor_read(ADC_PORT_3, &current_2);
            voltage_sensor_read(ADC_PORT_13, &voltage);
            power_measurement.power = (current_1+current_2)*voltage;
            power_measurement.previous_power = previous_values.previous_power_PWM_1;
            break;
        case PWM_PORT_2:
            current_sensor_read(ADC_PORT_4, &current_1);
            current_sensor_read(ADC_PORT_5, &current_2);
            voltage_sensor_read(ADC_PORT_14, &voltage);
            power_measurement.power = (current_1+current_2)*voltage;
            power_measurement.previous_power = previous_values.previous_power_PWM_2;
            break;
    }
    return 0;
}

void increase_duty_cycle(pwm_config_t config, pwm_port_t port)
{
    config.duty_cycle += K;
    pwm_update(TIMER_B0, port, config);
}

void decrease_duty_cycle(pwm_config_t config, pwm_port_t port)
{
    config.duty_cycle -= K;
    pwm_update(TIMER_B0, port, config);
}
/** \} End of mppt group */
