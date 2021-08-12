/*
 * voltage_sensor.c
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
 * \brief Voltage sensor device definition.
 * 
 * \authors Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * 
 * \version 0.2.21
 * 
 * \date 2021/06/07
 * 
 * \addtogroup voltage_sensor
 * \{
 */

#include <system/sys_log/sys_log.h>

#include "voltage_sensor.h"

int voltage_sensor_init(void)
{
    sys_log_print_event_from_module(SYS_LOG_INFO, VOLTAGE_SENSOR_MODULE_NAME, "Initializing the voltage sensor...");
    sys_log_new_line();

    static const adc_config_t volt_sense_adc_config = {0};

    if (adc_init((adc_port_t){0}, volt_sense_adc_config) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, VOLTAGE_SENSOR_MODULE_NAME, "Error initializing voltage sensor device!");
        sys_log_new_line();
        return -1;
    }

    return 0;
}

uint16_t voltage_sensor_raw_to_mv(adc_port_t port, uint16_t raw)
{
    if (port == TOTAL_SOLAR_PANNELS_VOLTAGE_SENSOR_ADC_PORT || port == MAIN_POWER_BUS_VOLTAGE_SENSOR_ADC_PORT)
    {
        return (uint16_t)(raw * ADC_VREF_MV * VOLTAGE_SENSOR_DIV_1 / ADC_RANGE);
    }
    else
    {
        return (uint16_t)(raw * ADC_VREF_MV * VOLTAGE_SENSOR_DIV_2 / ADC_RANGE);
    }
}

int voltage_sensor_read(adc_port_t port, uint16_t *volt)
{
    uint16_t raw_volt = 0;
    int err = 0;

    adc_mutex_take();
    err = adc_read(port, &raw_volt);
    adc_mutex_give();

    if (err != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, VOLTAGE_SENSOR_MODULE_NAME, "Error reading the raw voltage value!");
        sys_log_new_line();

        return -1;
    }

    *volt = voltage_sensor_raw_to_mv(port, raw_volt);

    return 0;
}

/** \} End of voltage_sensor group */
