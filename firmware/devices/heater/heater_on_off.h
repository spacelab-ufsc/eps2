/*
 * heater_on_off.h
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
 * \brief Heater device definition.
 *
 * \author Jo�o Cl�udio <joaoclaudiobarcellos@gmail.com>
 * 
 * \version 0.2.11
 *
 * \date 2021/08/04
 *
 * \defgroup heater Heater
 * \ingroup devices
 * \{
 */

#ifndef HEATER_ON_OFF_H_
#define HEATER_ON_OFF_H_

#include <stdint.h>
#include <stdbool.h>

#include <devices/temp_sensor/temp_sensor.h>
#include <drivers/gpio/gpio.h>

#define HEATER_ON_OFF_MODULE_NAME        "HEATER's ON/OFF CONTROLLER"

/**
 * \brief Hysteresis controller parameters.
 */
#define TEMP_LIMIT_MINIMUM                  303           /**< TODO. */
#define TEMP_LIMIT_MAXIMUM                  305           /**< TODO. */
#define HEATER_OFF                          false
#define HEATER_ON                           true

/**
 * \brief Hysteresis controller channels.
 */
#define HEATER_GPIO_MODE                GPIO_MODE_OUTPUT
#define HEATER_CONTROL_LOOP_CH_0        0
#define HEATER_CONTROL_LOOP_CH_1        1
#define HEATER_ACTUATOR_CH_0            GPIO_PIN_18
#define HEATER_ACTUATOR_CH_1            GPIO_PIN_19
#define HEATER_SENSOR_CH_0              TEMP_SENSOR_RTD_CH_4
#define HEATER_SENSOR_CH_1              TEMP_SENSOR_RTD_CH_5
#define HEATER_SENSOR_BOARD             TEMP_SENSOR_RTD_CH_3

/**
 * \brief Hysteresis controller channel type.
 */
typedef uint8_t heater_channel_t;

/**
 * \brief Heater state type.
 */
typedef uint8_t heater_state_t;

/**
 * \brief Temperature variable type.
 */
typedef uint16_t temperature_t;

/**
 * \brief Heater configuration variable type.
 */
typedef gpio_config_t heater_on_off_config_t;

/**
 * \brief Hysteresis controller variable type.
 */
//typedef struct {
//    /* Temperature limits */
//    float limMin;
//    float limMax;
//} hysteresis_controller_t;

/**
 * \brief Initialization routine of the heater device.
 *
 * \return The status/error code.
 */
int heater_on_off_init(void);

/**
 * \brief Function to implement the On/Off controller algorithm.
 *
 * \param[in] state is the desired temperature value.
 *
 * \param[in] measurement is the actual current temperature value.
 *
 * \return The control loop output value.
 */
bool heater_on_off_algorithm(heater_channel_t channel, float measurement);

/**
 * \brief Gets the temperature sensor value in kelvin.
 *
 * \param[in] channel is the channel to be used.
 *
 * \param[in] temp is the read temperature value.
 *
 * \return The status/error code.
 */
int heater_on_off_get_sensor(heater_channel_t channel, temperature_t *temp);

/**
 * \brief Sets the selected heater actuator state.
 *
 * \param[in] channel is the channel to be used.
 *
 * \param[in] heater_controller_output is the value to set the heater state.
 *
 * \return The status/error code.
 */
int heater_on_off_set_actuator(heater_channel_t channel, bool heater_controller_output);


#endif /* HEATER_ON_OFF_H_ */

/** \} End of heater group */
