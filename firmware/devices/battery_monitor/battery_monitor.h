/*
 * battery_monitor.h
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
 * \brief Battery Monitor device definition.
 *
 * \author Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 *
 * \version 0.1.12
 *
 * \date 2021/09/18
 *
 * \defgroup battery_monitor Battery Manager
 * \ingroup devices
 * \{
 */

#ifndef BATTERY_MONITOR_H_
#define BATTERY_MONITOR_H_

#include <stdint.h>

#include "drivers/ds277Xg/ds277Xg.h"

#define BATTERY_MONITOR_MODULE_NAME         "Battery Monitor"

extern ds277Xg_config_t battery_monitor_config;

/**
 * \brief Battery Monitor device initialization.
 * 
 * \return int The status/error code.
 */
int battery_monitor_init();

/**
 * \brief Get the cell one voltage.
 * 
 * \param[in,out] voltage Voltage in mV.
 * \return int The status/error code.
 */
int bm_get_cell_one_voltage(int16_t *voltage);

/**
 * \brief Get the cell two voltage.
 * 
 * \param[in,out] voltage Voltage in mV.
 * \return int The status/error code.
 */
int bm_get_cell_two_voltage(int16_t *voltage);

/**
 * \brief Get the batteries voltage in mV.
 * 
 * \param[in,out] voltage Voltage in mV.
 * \return int The status/error code.
 */
int bm_get_voltage(uint16_t *voltage);

/**
 * \brief Get the batteries temperature in kelvin.
 * 
 * \param[in,out] temp Temperature in kelvin
 * \return int The status/error code.
 */
int bm_get_temperature_kelvin(uint16_t *temp);

/**
 * \brief Get the last read current value.
 * 
 * \param[in,out] current Current in mA.
 * \return int The status/error code.
 */
int bm_get_instantaneous_current(int16_t *current);

/**
 * \brief Get the average from last eight read current values.
 * 
 * \param[in,out] current Current in mA.
 * \return int The status/error code.
 */
int bm_get_average_current(int16_t *current);

/**
 * \brief Get the status register data.
 * 
 * \param[in,out] data Register data.
 * \return int The status/error code.
 */
int bm_get_status_register_data(uint8_t *data);

/**
 * \brief Get the protection register data.
 * 
 * \param[in,out] data Register data.
 * \return int The status/error code.
 */
int bm_get_protection_register_data(uint8_t *data);

#endif /* BATTERY_MONITOR_H_ */

/** \} End of battery_monitor group */
