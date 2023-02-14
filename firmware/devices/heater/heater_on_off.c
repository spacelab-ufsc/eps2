/*
 * heater_on_off.c
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
 *
 * \version 0.2.27
 *
 * \date 2021/08/04
 *
 * \addtogroup heater_on_off
 * \{
 */

#include <system/sys_log/sys_log.h>

#include "heater_on_off.h"

int heater_on_off_init(heater_on_off_channel_t channel)
{
    sys_log_print_event_from_module(SYS_LOG_INFO, HEATER_ON_OFF_MODULE_NAME, "Initializing the heater...");
    sys_log_new_line();

    heater_on_off_config_t conf = {0};
    conf.mode = HEATER_GPIO_MODE;

    /* Initialize heaters pins and sets them to off state */
    switch(channel){

        case HEATER_CONTROL_LOOP_CH_0:

            if(gpio_init(HEATER_DRIVER_CH_0, conf))
            {
                sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_ON_OFF_MODULE_NAME, "Error during the initialization (CH0)!");
                sys_log_new_line();
                return -1;
            }

            if(gpio_set_state(HEATER_DRIVER_CH_0, HEATER_OFF))
            {
                sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_ON_OFF_MODULE_NAME, "Error while setting state (CH0)!");
                sys_log_new_line();
                return -1;
            }            

            break;
        
        case HEATER_CONTROL_LOOP_CH_1:

            if(gpio_init(HEATER_DRIVER_CH_1, conf))
            {
                sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_ON_OFF_MODULE_NAME, "Error during the initialization (CH1)!");
                sys_log_new_line();
                return -1;
            }

            if(gpio_set_state(HEATER_DRIVER_CH_1, HEATER_OFF))
            {
                sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_ON_OFF_MODULE_NAME, "Error while setting state (CH1)!");
                sys_log_new_line();
                return -1;
            }        

            break;
    }

    return 0;
}

bool heater_on_off_algorithm(heater_on_off_channel_t channel, float measurement)
{
    static bool heater1_status = false;
    static bool heater2_status = false;
    bool new_status = false;

    /* Check the temperature limits and return the updated heater status */
    if(measurement >= TEMP_LIMIT_MAXIMUM)
    {
        new_status = HEATER_OFF;
    }
    else if(measurement <= TEMP_LIMIT_MINIMUM)
    {
        new_status = HEATER_ON;
    }
    else
    {
        switch (channel)
        {
        case HEATER_CONTROL_LOOP_CH_0:
            return heater1_status;
            break;
            
        case HEATER_CONTROL_LOOP_CH_1:
            return heater2_status;
            break;
        
        default:
            break;
        }   
    }

    switch (channel)
    {
    case HEATER_CONTROL_LOOP_CH_0:
        heater1_status = new_status;
        break;
        
    case HEATER_CONTROL_LOOP_CH_1:
        heater2_status = new_status;
        break;
    
    default:
        break;
    }   
    return new_status;
}

int heater_on_off_get_sensor(heater_on_off_channel_t channel, temperature_t *temp)
{   
    switch(channel) 
    {
        case HEATER_CONTROL_LOOP_CH_0:
            return temp_rtd_read_k(HEATER_RTD_CH_0, temp);
        case HEATER_CONTROL_LOOP_CH_1:
            return temp_rtd_read_k(HEATER_RTD_CH_1, temp);
        default:
            sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_ON_OFF_MODULE_NAME, "Invalid sensor channel!");
            sys_log_new_line();
            return -1;
    }
}

int heater_on_off_set_actuator(heater_on_off_channel_t channel, bool heater_controller_output)
{
    switch(channel) 
    {
        case HEATER_CONTROL_LOOP_CH_0:
            if (heater_controller_output == HEATER_OFF)
            {
                return gpio_set_state(HEATER_DRIVER_CH_0, HEATER_OFF);
            }
            else 
            {
                return gpio_set_state(HEATER_DRIVER_CH_0, HEATER_ON);
            }
        case HEATER_CONTROL_LOOP_CH_1:
            if (heater_controller_output == HEATER_OFF)
            {
                return gpio_set_state(HEATER_DRIVER_CH_1, HEATER_OFF);
            }
            else 
            {
                return gpio_set_state(HEATER_DRIVER_CH_1, HEATER_ON);
            }
        default:
            sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_ON_OFF_MODULE_NAME, "Invalid actuator channel!");
            sys_log_new_line();
            return -1;
    }
}

/** \} End of heater group */



