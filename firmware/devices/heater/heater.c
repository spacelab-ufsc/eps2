/*
 * heater.c
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
 * \brief Heater device implementation.
 *
 * \author Jo�o Cl�udio <joaoclaudiobarcellos@gmail.com>
 * \author Andr� M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 *
 * \version 0.2.27
 *
 * \date 2021/08/04
 *
 * \addtogroup heater
 * \{
 */

#include <system/sys_log/sys_log.h>

#include "heater.h"

#if defined _UNIT_TEST_
    #define STATIC
#else
    #define STATIC static
#endif

heater_config_t heater_config;

/**
 * \brief PI controller state for each heater channel.
 */
STATIC heater_pi_t heater_controller[2];

int heater_init(heater_channel_t channel)
{
    sys_log_print_event_from_module(SYS_LOG_INFO, HEATER_MODULE_NAME, "Initializing Heater device.");
    sys_log_new_line();

    /* Reset PI controller state */
    heater_controller[channel].integral = 0.0f;

    /* Initialize the PWM parameters */
    heater_config.period_us         = HEATER_PERIOD_INIT;
    heater_config.duty_cycle        = HEATER_DUTY_CYCLE_INIT;

    switch(channel){

        case HEATER_CONTROL_LOOP_CH_0:

            if(pwm_init(HEATER_CONTROL_LOOP_CH_SOURCE, HEATER_ACTUATOR_CH_0, heater_config))
            {
                sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_MODULE_NAME, "Error during the initialization (CH0)!");
                sys_log_new_line();
                return -1;
            }

            break;

        case HEATER_CONTROL_LOOP_CH_1:

            if(pwm_init(HEATER_CONTROL_LOOP_CH_SOURCE, HEATER_ACTUATOR_CH_1, heater_config))
            {
                sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_MODULE_NAME, "Error during the initialization (CH1)!");
                sys_log_new_line();
                return -1;
            }

            break;

    }

    return 0;
}

float heater_algorithm(heater_channel_t channel, float setpoint, float measurement)
{
    float error;
    float p_term;
    float provisional_output;
    float output;
    float integral_max;
    float integral_min;

    /* Error signal */
    error = setpoint - measurement;

    /* Proportional term */
    p_term = HEATER_PI_KP * error;

    /* Provisional output using current integral state */
    provisional_output = p_term + HEATER_PI_KI * heater_controller[channel].integral;

    /* Conditional Integration anti-windup */
    if ((provisional_output >= HEATER_OUTPUT_MAXIMUM) && (error > 0.0f))
    {
        /* Output saturated high and error pushes higher: do not integrate */
    }
    else if ((provisional_output <= HEATER_OUTPUT_MINIMUM) && (error < 0.0f))
    {
        /* Output saturated low and error pushes lower: do not integrate */
    }
    else
    {
        heater_controller[channel].integral += error * HEATER_SAMPLE_TIME_S;
    }

    /*
     * Clamp integral to non-negative range. Negative integral would represent
     * stored cooling effort, which is meaningless for a heat-only actuator and
     * would delay heating when the battery becomes cold again.
     */
    integral_max = HEATER_OUTPUT_MAXIMUM / HEATER_PI_KI;
    integral_min = 0.0f;

    if (heater_controller[channel].integral > integral_max)
    {
        heater_controller[channel].integral = integral_max;
    }
    else if (heater_controller[channel].integral < integral_min)
    {
        heater_controller[channel].integral = integral_min;
    }

    /* Recompute output with updated integral */
    output = p_term + HEATER_PI_KI * heater_controller[channel].integral;

    /* Clamp output to actuator limits */
    if (output > HEATER_OUTPUT_MAXIMUM)
    {
        output = HEATER_OUTPUT_MAXIMUM;
    }
    else if (output < HEATER_OUTPUT_MINIMUM)
    {
        output = HEATER_OUTPUT_MINIMUM;
    }

    /* Return controller output */
    return output;
}

int heater_get_sensor(heater_channel_t channel, temperature_t *temp) 
{   
    switch(channel) 
    {
        case HEATER_CONTROL_LOOP_CH_0:
            return temp_rtd_read_k(HEATER_SENSOR_CH_0, (uint16_t *)&temp);
        case HEATER_CONTROL_LOOP_CH_1:
            return temp_rtd_read_k(HEATER_SENSOR_CH_1, (uint16_t *)&temp);
        default:
            sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_MODULE_NAME, "Invalid sensor channel!");
            sys_log_new_line();
            return -1;
    }
}

int heater_set_actuator(heater_channel_t channel, float pid_output) 
{
    switch(channel) 
    {
        case HEATER_CONTROL_LOOP_CH_0:
            heater_config.duty_cycle = pid_output;
            if (pid_output == 0)
            {
                return pwm_stop(HEATER_CONTROL_LOOP_CH_SOURCE, HEATER_ACTUATOR_CH_0, heater_config);
            }
            else 
            {
                return pwm_update(HEATER_CONTROL_LOOP_CH_SOURCE, HEATER_ACTUATOR_CH_0, heater_config);
            }
        case HEATER_CONTROL_LOOP_CH_1:
            heater_config.duty_cycle = pid_output;
            if (pid_output == 0)
            {
                return pwm_stop(HEATER_CONTROL_LOOP_CH_SOURCE, HEATER_ACTUATOR_CH_1, heater_config);
            }
            else 
            {
                return pwm_update(HEATER_CONTROL_LOOP_CH_SOURCE, HEATER_ACTUATOR_CH_1, heater_config);
            }
        default:
            sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_MODULE_NAME, "Invalid actuator channel!");
            sys_log_new_line();
            return -1;
    }
}

/** \} End of heater group */



