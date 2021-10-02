/*
 * battery_monitor.c
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
 * \brief Battery Monitor device implementation.
 *
 * \author Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 *
 * \version 0.1.12
 *
 * \date 2021/09/18
 *
 * \addtogroup battery_monitor
 * \{
 */

#include <stdint.h>

#include "battery_monitor.h"

#include <system/sys_log/sys_log.h>

#include <drivers/ds277Xg/ds277Xg.h>
#include <drivers/i2c/i2c.h>

#ifdef CONFIG_DRIVERS_DS277X_ONEWIRE_VERSION
ds277Xg_config_t battery_monitor_config = {.port = GPIO_PIN_69};
#else
ds277Xg_config_t battery_monitor_config = {.port = I2C_PORT_2, .slave_adr = DS277XG_DEFAULT_SLAVE_ADDRESS};
#endif

int battery_monitor_init()
{
    sys_log_print_event_from_module(SYS_LOG_INFO, BATTERY_MONITOR_MODULE_NAME, "Initializing the battery monitor...");
    sys_log_new_line();

    if(ds277Xg_init(&battery_monitor_config) != 0)
    {
       sys_log_print_event_from_module(SYS_LOG_ERROR, BATTERY_MONITOR_MODULE_NAME, "Error initializing the battery monitor!");
       sys_log_new_line();

       return -1;
    }

    return 0;
}

int bm_get_cell_one_voltage(int16_t *voltage)
{
    if (ds277Xg_read_voltage_mv(&battery_monitor_config, voltage, 1) != 0) {return -1;}
    return 0;
}

int bm_get_cell_two_voltage(int16_t *voltage)
{
    if (ds277Xg_read_voltage_mv(&battery_monitor_config, voltage, 2) != 0) {return -1;}
    return 0;
}

int bm_get_voltage(uint16_t *voltage)
{
    int16_t buf = 0;
    if (bm_get_cell_one_voltage(&buf) != 0) {return -1;}
    *voltage = buf;
    if (bm_get_cell_two_voltage(&buf) != 0) {return -1;}
    *voltage += buf;
    return 0;
}

int bm_get_temperature_kelvin(uint16_t *temp)
{
    if (ds277Xg_read_temperature_kelvin(&battery_monitor_config, temp) != 0) {return -1;}
    return 0;
}

int bm_get_instantaneous_current(int16_t *current)
{
    if (ds277Xg_read_current_ma(&battery_monitor_config, current, false) != 0) {return -1;}
    return 0;
}

int bm_get_average_current(int16_t *current)
{
    if (ds277Xg_read_current_ma(&battery_monitor_config, current, true) != 0) {return -1;}
    return 0;
}

int bm_get_status_register_data(uint8_t *data)
{
    if (ds277Xg_read_data(&battery_monitor_config, DS277XG_STATUS_REGISTER, data, 1) != 0) {return -1;}
    return 0;
}

int bm_get_protection_register_data(uint8_t *data)
{
    if (ds277Xg_read_data(&battery_monitor_config, DS277XG_PROTECTION_REGISTER, data, 1) != 0) {return -1;}
    return 0;
}
