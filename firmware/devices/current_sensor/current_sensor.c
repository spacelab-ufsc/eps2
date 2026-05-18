/*
 * current_sensor.c
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
 * \brief Current sensor device implementation.
 * 
 * \authors Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * 
 * \version 0.2.21
 * 
 * \date 2021/06/11
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
    sys_log_print_event_from_module(SYS_LOG_INFO, CURRENT_SENSOR_MODULE_NAME, "Initializing Current Sensor device.");
    sys_log_new_line();
    
    static const max9934_config_t curr_sense_max9934_config = {0};

    int err = max9934_init(curr_sense_max9934_config);

    if (err != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, CURRENT_SENSOR_MODULE_NAME, "Error initializing Current Sensor device!");
        sys_log_new_line();
    }

    return err;
};

uint16_t current_sensor_raw_to_ma(adc_port_t port, uint16_t raw)
{
    if(port == EPS_BEACON_CURRENT_SENSOR_ADC_PORT)
    {
        return (uint16_t)(1000UL * (uint32_t)raw * (ADC_VREF_MV / (ADC_RANGE * EPS_CURRENT_SENSOR_RL_VALUE_KOHM * EPS_CURRENT_SENSOR_GAIN * EPS_CURRENT_SENSOR_RSENSE_VALUE_MOHM)));
    }
    else 
    {
        return (uint16_t)(1000UL * (uint32_t)raw * (ADC_VREF_MV / (ADC_RANGE * SP_CURRENT_SENSOR_RL_VALUE_KOHM * SP_CURRENT_SENSOR_GAIN * SP_CURRENT_SENSOR_RSENSE_VALUE_MOHM)));
    }
};

int current_sensor_read(adc_port_t port, uint16_t *cur)
{
    uint16_t raw_cur = 0;
    int err = 0;

    adc_mutex_take();
    err = max9934_read((max9934_config_t){.adc_port = port}, &raw_cur);
    adc_mutex_give();

    if (err != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, CURRENT_SENSOR_MODULE_NAME, "Error reading the raw current value!");
        sys_log_new_line();

        return -1;
    }

    *cur = current_sensor_raw_to_ma(port, raw_cur);

    return 0;
};

/** \} End of current_sensor group */
