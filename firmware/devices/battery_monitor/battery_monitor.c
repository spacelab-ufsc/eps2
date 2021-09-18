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

#include <drivers/ds2777g/ds2777g.h>
#include <drivers/i2c/i2c.h>

const ds2777g_config_t battery_monitor_config = {.port = I2C_PORT_2, .slave_adr = DS2777G_DEFAULT_SLAVE_ADDRESS};

int battery_monitor_init()
{
    sys_log_print_event_from_module(SYS_LOG_INFO, BATTERY_MONITOR_MODULE_NAME, "Initializing the battery monitor...");
    sys_log_new_line();

    if(ds2777g_init(battery_monitor_config) != 0)
    {
       sys_log_print_event_from_module(SYS_LOG_ERROR, BATTERY_MONITOR_MODULE_NAME, "Error initializing the battery monitor!");
       sys_log_new_line();

       return -1;
    }

    return 0;
}

int get_cell_one_voltage(int16_t *voltage)
{
    if (ds2777g_read_voltage_mv(battery_monitor_config, voltage, 1) != 0) {return -1;}
    return 0;
}

int get_cell_two_voltage(int16_t *voltage)
{
    if (ds2777g_read_voltage_mv(battery_monitor_config, voltage, 2) != 0) {return -1;}
    return 0;
}

int get_instantaneous_current(int16_t *current)
{
    if (ds2777g_read_current_ma(battery_monitor_config, current, false) != 0) {return -1;}
    return 0;
}

int get_average_current(int16_t *current)
{
    if (ds2777g_read_current_ma(battery_monitor_config, current, true) != 0) {return -1;}
    return 0;
}
