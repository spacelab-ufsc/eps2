/*
 * current_sensor.h
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
 * \brief Current sensor device definition.
 * 
 * \authors Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 30/01/2021
 * 
 * \defgroup current_sensor Current Sensor
 * \ingroup devices
 * \{
 */

#ifndef CURRENT_SENSOR_H_
#define CURRENT_SENSOR_H_

#include <stdint.h>

#include <drivers/adc/adc.h>

#define CURRENT_SENSOR_MODULE_NAME "Current Sensor"

#define PANNEL_MINUS_Y_CURRENT_SENSOR_ADC_PORT ADC_PORT_1
#define PANNEL_PLUS_X_CURRENT_SENSOR_ADC_PORT ADC_PORT_2
#define PANNEL_MINUS_X_CURRENT_SENSOR_ADC_PORT ADC_PORT_3
#define PANNEL_PLUS_Z_CURRENT_SENSOR_ADC_PORT ADC_PORT_4
#define PANNEL_MINUS_Z_CURRENT_SENSOR_ADC_PORT ADC_PORT_5
#define PANNEL_PLUS_Y_CURRENT_SENSOR_ADC_PORT ADC_PORT_6
#define EPS_BEACON_CURRENT_SENSOR_ADC_PORT ADC_PORT_7

#define CURRENT_SENSOR_RSENSE_VALUE_OHM 0.05 /**< Rsense resistor value in Ohms. */
#define CURRENT_SENSOR_RL_VALUE_OHM 47000    /**< RL resistor value in Ohms. */
#define CURRENT_SENSOR_GAIN 0.005            /**< Current gain of max9934 in A/V. */

/**
 * \brief Current sensor device initialization routine.
 *
 * \return The status/error code.
 */
int current_sensor_init();

/**
 * \brief Reads the current from all the current sensors.
 * 
 * \param[in] port is the ADC port to read from.
 *
 * \param[in,out] cur is a pointer to store all the read currents in mA.
 *
 * \return The status/error code.
 */
int current_sensor_read(adc_port_t port, float *cur);

#endif /* CURRENT_SENSOR_H_ */

/** \} End of current_sensor group */
