/*
 * bat_manager.h
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
 * \brief Battery Manager device definition.
 *
 * \author Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 2021/02/07
 *
 * \defgroup bat_manager Battery Manager
 * \ingroup devices
 * \{
 */

#ifndef BAT_MANAGER_H_
#define BAT_MANAGER_H_

#include <stdint.h>

#include "drivers/ds2775g/ds2775g.h"

#define BAT_MANAGER_MODULE_NAME         "Battery Manager"

ds2775g_config_t bat_monitor_config;

/**
 * \brief battery measured voltage.
 */
typedef struct
{
    uint32_t cell_0;                /**< Battery cell 0 voltage. */
    uint32_t cell_1;                /**< Battery cell 1 voltage. */
} bat_voltage_t;

/**
 * \brief Battery Manager data structure.
 */
typedef struct
{
    bat_voltage_t bat_voltage;  /**< Battery voltage. */
    uint32_t bat_current;           /**< Battery current. */
    uint32_t bat_charge;            /**< Battery charge. */
} bat_manager_data_t;

/**
 * \brief Initialization of the Battery Manager device.
 *
 * \return The status/error code.
 */
int bat_manager_init();

/**
 * \brief Reads the battery voltage from the Battery Monitor.
 *
 * \param[in,out] bar_volt is a pointer to store the battery voltage.
 *
 * \return The status/error code.
 */
int get_bat_voltage(bat_voltage_t *bat_volt);

/**
 * \brief Reads the battery current from the Battery Monitor.
 *
 * \param[in,out] bat_cur is a pointer to store the raw battery current.
 *
 * \return The status/error code.
 */
int get_bat_current(uint32_t *bat_cur);

/**
 * \brief Reads the battery charge from the Battery Monitor.
 *
 * \param[in,out] charge is a pointer to store the raw battery charge.
 *
 * \return The status/error code.
 */
int get_bat_charge(uint32_t *charge);

/**
 * \brief Reads all the Battery Monitor available data.
 *
 * \param[in,out] data is a pointer to store the Battery Monitor data.
 *
 * \return The status/error code.
 */
int get_bat_data(bat_manager_data_t *data);

#endif /* BAT_MANAGER_H_ */

/** \} End of bat_manager group */
