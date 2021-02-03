/*
 * current_sensor.c
 * 
 * Copyright (C) 2020, SpaceLab.
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
 * \brief Current sensor device implementation.
 * 
 * \authors Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 30/01/2021
 * 
 * \addtogroup current_sensor
 * \{
 */

#include <drivers/max9934/max9934.h>
#include <drivers/adc/adc.h>

#include <system/sys_log/sys_log.h>

#include "current_sensor.h"

int current_sensor_init()
{
    return max9934_init((max9934_config_t){});
};

int current_sensor_read(adc_port_t port, float *cur)
{
    uint16_t raw_cur = 0;

    if (max9934_read((max9934_config_t){.adc_port = port}, &raw_cur) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, CURRENT_SENSOR_MODULE_NAME, "Error reading the raw current value!");
        sys_log_new_line();

        return -1;
    }

    *cur = (uint16_t)(1000 * raw_cur * (ADC_AVCC / (ADC_RANGE * CURRENT_SENSOR_RL_VALUE_OHM * CURRENT_SENSOR_GAIN * CURRENT_SENSOR_RSENSE_VALUE_OHM)));

    return 0;
};

/** \} End of current_sensor group */
