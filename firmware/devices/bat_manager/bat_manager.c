/*
 * bat_manager.c
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
 * \brief Battery Manager device implementation.
 *
 * \author Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 *
 * \version 0.1.12
 *
 * \date 2021/06/11
 *
 * \addtogroup bat_manager
 * \{
 */

#include <stdint.h>

#include "bat_manager.h"

#include <system/sys_log/sys_log.h>

#include <drivers/ds2775g/ds2775g.h>
#include <drivers/onewire/onewire.h>

int bat_manager_init()
{

    sys_log_print_event_from_module(SYS_LOG_INFO, BAT_MANAGER_MODULE_NAME, "Initializing the battery manager...");
    sys_log_new_line();

    if(ds2775g_init(&bat_monitor_config) != 0)
    {
       sys_log_print_event_from_module(SYS_LOG_ERROR, BAT_MANAGER_MODULE_NAME, "Error initializing the battery manager!");
       sys_log_new_line();

       return -1;
    }

    return 0;

}

int get_bat_voltage(bat_voltage_t *bat_volt)
{

    uint8_t read;
    uint8_t cell_0_voltage_LSB;
    uint8_t cell_0_voltage_MSB;
    uint8_t cell_1_voltage_LSB;
    uint8_t cell_1_voltage_MSB;

    /* Reads cell_0 voltage LSB */
    if(ds2775g_read_register(bat_monitor_config.onewire_port, voltage_LSB1_register, &cell_0_voltage_LSB) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, BAT_MANAGER_MODULE_NAME, "Error reading the battery cell_0 voltage!");
        sys_log_new_line();

        return -1;
    }

    cell_0_voltage_LSB = cell_0_voltage_LSB >> 5;

    /* Reads cell_0 voltage MSB */
    if(ds2775g_read_register(bat_monitor_config.onewire_port, voltage_MSB1_register, &read) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, BAT_MANAGER_MODULE_NAME, "Error reading the battery cell_0 voltage!");
        sys_log_new_line();

        return -1;
    }

    cell_0_voltage_MSB = read >> 5;
    read = read << 3;
    cell_0_voltage_LSB |= read & 0xF8;

    /* Concatenate cell_0 voltage LSB and MSB */
    bat_volt->cell_0 =  ((uint32_t) cell_0_voltage_MSB << 8) | cell_0_voltage_LSB;

    /* Reads cell_1 voltage LSB */
    if(ds2775g_read_register(bat_monitor_config.onewire_port, voltage_LSB2_register, &cell_1_voltage_LSB) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, BAT_MANAGER_MODULE_NAME, "Error reading the battery cell_1 voltage!");
        sys_log_new_line();

        return -1;
    }

    cell_1_voltage_LSB = cell_1_voltage_LSB >> 5;

    /* Reads cell_1 voltage MSB */
    if(ds2775g_read_register(bat_monitor_config.onewire_port, voltage_MSB2_register, &read) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, BAT_MANAGER_MODULE_NAME, "Error reading the battery cell_1 voltage!");
        sys_log_new_line();

        return -1;
    }

    cell_1_voltage_MSB = read >> 5;
    read = read << 3;
    cell_1_voltage_LSB |= read & 0xF8;

    /* Concatenate cell_1 voltage LSB and MSB */
    bat_volt->cell_1 =  ((uint32_t) cell_1_voltage_MSB << 8) | (uint32_t) cell_1_voltage_LSB;

    return 0;

}

int get_bat_current(uint32_t *bat_cur)
{

    uint8_t current_LSB;
    uint8_t current_MSB;

    if(ds2775g_read_register(bat_monitor_config.onewire_port, current_LSB_register, &current_LSB) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, BAT_MANAGER_MODULE_NAME, "Error reading the battery current!");
        sys_log_new_line();

        return -1;
    }

    if(ds2775g_read_register(bat_monitor_config.onewire_port, current_MSB_register, &current_MSB) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, BAT_MANAGER_MODULE_NAME, "Error reading the battery current!");
        sys_log_new_line();

        return -1;
    }

    uint32_t read = ((uint32_t) current_MSB<<8) | (uint32_t) current_LSB;
    bat_cur = &read;

    return 0;

}

int get_bat_charge(uint32_t *charge)
{

    return -1;

}

int get_bat_data(bat_manager_data_t *data)
{

    if (get_bat_voltage(&data->bat_voltage) != 0)
    {
        return -1;
    }

    if (get_bat_current(&data->bat_current) != 0)
    {
        return -1;
    }

    return 0;

}
