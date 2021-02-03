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
 * \authors Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 03/02/2021
 * 
 * \defgroup voltage_sensor Voltage Sensor
 * \ingroup devices
 * \{
 */

#ifndef VOLTAGE_SENSOR_H_
#define VOLTAGE_SENSOR_H_

#include <stdint.h>

#include <drivers/adc/adc.h>

#define VOLTAGE_SENSOR_MODULE_NAME "Voltage Sensor"

#define PANNELS_MINUS_Y_PLUS_X_VOLTAGE_SENSOR_ADC_PORT ADC_PORT_12
#define PANNELS_MINUS_X_PLUS_Z_VOLTAGE_SENSOR_ADC_PORT ADC_PORT_13
#define PANNELS_MINUS_Z_PLUS_Y_VOLTAGE_SENSOR_ADC_PORT ADC_PORT_14
#define MAIN_SOLAR_PANNELS_VOLTAGE_SENSOR_ADC_PORT ADC_PORT_15
#define VOLTAGE_SENSOR_DIV_1 4.0  /**< Voltage divisor factor for main voltage. */
#define VOLTAGE_SENSOR_DIV_2 1.93 /**< Voltage divisor factor for other voltages. */

/**
 * \brief Voltage sensor device initialization routine.
 *
 * \return The status/error code.
 */
int voltage_sensor_init();

/**
 * \brief Reads the voltage from the voltage sensor.
 * 
 * \param[in] port is the ADC port to read from.
 *
 * \param[in,out] volt is a pointer to store the read voltage in mV.
 *
 * \return The status/error code.
 */
int voltage_sensor_read(adc_port_t port, uint16_t *volt);

#endif /* VOLTAGE_SENSOR_H_ */

/** \} End of voltage_sensor group */
