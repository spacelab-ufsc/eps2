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
 * \author João Cláudio <joaoclaudiobarcellos@gmail.com>
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
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

pid_controller_t pid_controller;
heater_config_t heater_config;

int heater_init(void) 
{
    sys_log_print_event_from_module(SYS_LOG_INFO, HEATER_MODULE_NAME, "Initializing the heater...");
    sys_log_new_line();   

    /* PID controller initialization */
    pid_controller.tau              = PID_TAU_INIT; 
    pid_controller.limMin           = PID_LIMIT_MINIMUM_INIT;    
    pid_controller.limMax           = PID_LIMIT_MAXIMUM_INIT;    
    pid_controller.limMinInt        = PID_LIMIT_MINIMUM_INTEGRATOR_INIT;        
    pid_controller.limMaxInt        = PID_LIMIT_MAXIMUM_INTEGRATOR_INIT;        
    pid_controller.sample_time      = PID_SAMPLE_TIME_INIT;
    pid_controller.integrator       = PID_INTEGRATOR_INIT;        
    pid_controller.prevError        = PID_PREVIOUS_ERROR_INIT;        
    pid_controller.differentiator   = PID_DIFFERENTIATOR_INIT;               
    pid_controller.prevMeasurement  = PID_PREVIOUS_MEASUREMENT_INIT;              
    pid_controller.out              = PID_OUTPUT_INIT;

    /* Initialize the PWM parameters */
    heater_config.period_us         = HEATER_PERIOD_INIT;
    heater_config.duty_cycle        = HEATER_DUTY_CYCLE_INIT;

    if(pwm_init(HEATER_CONTROL_LOOP_CH_SOURCE, HEATER_ACTUATOR_CH_0, heater_config))
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_MODULE_NAME, "Error during the initialization (CH0)!");
        sys_log_new_line();
        return -1;
    }

    if(pwm_init(HEATER_CONTROL_LOOP_CH_SOURCE, HEATER_ACTUATOR_CH_1, heater_config))
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_MODULE_NAME, "Error during the initialization (CH1)!");
        sys_log_new_line();
        return -1;
    }

    return 0;
}

float heater_algorithm(float setpoint, float measurement) 
{
    /* Error signal */
    float error = setpoint - measurement;

    /* Proportional: 
     * p[n]=Kp*e[n] 
     */
    float proportional = PID_PROPORTIONAL_CONSTANT*error;

    /* Integral: 
     * i[n]= ((Ki*T)/2)*(e[n]-e[n-1])+i[n-1] 
     */
    pid_controller.integrator += 0.5f * PID_INTEGRATOR_CONSTANT * pid_controller.sample_time * (error + pid_controller.prevError);

    /* Anti-wind-up via integrator clamping */
    if (pid_controller.integrator > pid_controller.limMaxInt) {

        pid_controller.integrator = pid_controller.limMaxInt;

    } else if (pid_controller.integrator < pid_controller.limMinInt) {

        pid_controller.integrator = pid_controller.limMinInt;

    }

    /* Derivative (band-limited differentiator): 
     * d[n]=(2*Kd*(e[n]-e[n-1])+(2*tau-T)*d[n-1])/(2*tau+T) 
     */
    pid_controller.differentiator = -(2.0f * PID_DIFFERENTIATOR_CONSTANT * (measurement - pid_controller.prevMeasurement)   /* Note: derivative on measurement, therefore minus sign in front of equation! */
                        + (2.0f * pid_controller.tau - pid_controller.sample_time) * pid_controller.differentiator)
                        / (2.0f * pid_controller.tau + pid_controller.sample_time);

    /*
     * Compute output and apply limits
     * out[n]=p[n]+i[n]+d[n]
     */
    pid_controller.out = proportional + pid_controller.integrator + pid_controller.differentiator;

    if (pid_controller.out > pid_controller.limMax) {

        pid_controller.out = pid_controller.limMax;

    } else if (pid_controller.out < pid_controller.limMin) {

        pid_controller.out = pid_controller.limMin;

    }

    /* Store error and measurement for later use */
    pid_controller.prevError       = error;
    pid_controller.prevMeasurement = measurement;

    /* Return controller output */
    return pid_controller.out;
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



