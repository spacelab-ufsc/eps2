/*
 * voltage_sensor.h
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
 * \author Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 2021/01/31
 *
 * \defgroup voltage_sensor Voltage Sensor
 * \ingroup devices
 * \{
 */

#ifndef VOLTAGE_SENSOR_H_
#define VOLTAGE_SENSOR_H_

#include <stdint.h>

#include <drivers/adc/adc.h>

#define VOLTAGE_SENSOR_MODULE_NAME     "Voltage Sensor"

/**
 * \brief Voltage sensor device initialization routine.
 *
 * \return The status/error code.
 */
int voltage_sensor_init();

/**
 * \brief Reads the raw voltage from the voltage sensor.
 *
 * \param[in,out] val is a pointer to store the raw value of the voltage.
 *
 * \return The status/error code.
 */
int voltage_sensor_read_raw(uint16_t *val);

/**
 * \brief Reads the voltage from the voltage sensor.
 *
 * \param[in,out] volt is a pointer to store the read voltage in mV.
 *
 * \return The status/error code.
 */
int voltage_sensor_read(uint16_t *volt);

#endif /* VOLTAGE_SENSOR_H_ */

/** \} End of voltage_sensor group */
