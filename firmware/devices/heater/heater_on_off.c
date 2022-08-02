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

int heater_on_off_init(void)
{
    sys_log_print_event_from_module(SYS_LOG_INFO, HEATER_ON_OFF_MODULE_NAME, "Initializing the heater...");
    sys_log_new_line();

    heater_config_t conf = {0};
    conf.mode = HEATER_GPIO_MODE;

    if(gpio_init(HEATER_ACTUATOR_CH_0, conf))
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_ON_OFF_MODULE_NAME, "Error during the initialization (CH0)!");
        sys_log_new_line();
        return -1;
    }

    if(gpio_init(HEATER_ACTUATOR_CH_1, conf))
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_ON_OFF_MODULE_NAME, "Error during the initialization (CH1)!");
        sys_log_new_line();
        return -1;
    }

    if(gpio_set_state(HEATER_ACTUATOR_CH_0, HEATER_ON))
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_ON_OFF_MODULE_NAME, "Error while setting state (CH0)!");
        sys_log_new_line();
        return -1;
    }

    if(gpio_set_state(HEATER_ACTUATOR_CH_1, HEATER_ON))
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_ON_OFF_MODULE_NAME, "Error while setting state (CH1)!");
        sys_log_new_line();
        return -1;
    }

    return 0;
}

bool heater_on_off_algorithm(bool state, float measurement)
{

    if(measurement >= TEMP_LIMIT_MAXIMUM){
        /* Return controller output */
        return HEATER_OFF;
    }

    if(measurement <= TEMP_LIMIT_MINIMUM){
        /* Return controller output */
        return HEATER_ON;
    }

    if(measurement < TEMP_LIMIT_MAXIMUM && measurement > TEMP_LIMIT_MINIMUM){
        /* Return controller output */
        return state;
    }

    return state;
}

int heater_on_off_get_sensor(heater_channel_t channel, temperature_t *temp)
{   
    switch(channel) 
    {
        case HEATER_CONTROL_LOOP_CH_0:
            return temp_rtd_read_k(HEATER_SENSOR_CH_0, (uint16_t *)&temp);
        case HEATER_CONTROL_LOOP_CH_1:
            return temp_rtd_read_k(HEATER_SENSOR_CH_1, (uint16_t *)&temp);
        default:
            sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_ON_OFF_MODULE_NAME, "Invalid sensor channel!");
            sys_log_new_line();
            return -1;
    }
}

int heater_on_off_set_actuator(heater_channel_t channel, bool heater_controller_output)
{
    switch(channel) 
    {
        case HEATER_CONTROL_LOOP_CH_0:
            if (heater_controller_output == HEATER_OFF)
            {
                return gpio_set_state(HEATER_ACTUATOR_CH_0, HEATER_OFF);
            }
            else 
            {
                return gpio_set_state(HEATER_ACTUATOR_CH_0, HEATER_ON);
            }
        case HEATER_CONTROL_LOOP_CH_1:
            if (heater_controller_output == HEATER_OFF)
            {
                return gpio_set_state(HEATER_ACTUATOR_CH_1, HEATER_OFF);
            }
            else 
            {
                return gpio_set_state(HEATER_ACTUATOR_CH_1, HEATER_ON);
            }
        default:
            sys_log_print_event_from_module(SYS_LOG_ERROR, HEATER_ON_OFF_MODULE_NAME, "Invalid actuator channel!");
            sys_log_new_line();
            return -1;
    }
}

/** \} End of heater group */



