/*
 * temp_sensors.h
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
 * \brief Temperature sensor device definition.
 * 
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 2021/03/18
 * 
 * \defgroup temp_sensor Temperature Sensor
 * \ingroup devices
 * \{
 */

#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

#include <stdint.h>

#include <drivers/ads1248/ads1248.h>

#define TEMP_SENSOR_MODULE_NAME     "Temperature Sensor"

#define TEMP_SENSOR_REF_VOLTAGE     3.3

#define TEMP_SENSOR_SPI_PORT        SPI_PORT_1
#define TEMP_SENSOR_SPI_MODE        SPI_MODE_0
#define TEMP_SENSOR_SPI_SPEED_HZ    1000000
#define TEMP_SENSOR_START_PIN       GPIO_PIN_60
#define TEMP_SENSOR_SPI_CS          GPIO_PIN_59
#define TEMP_SENSOR_RESET_PIN       GPIO_PIN_58

/**
 * \brief Temperature sensor device type.
 */
typedef ads1248_config_t temp_sensor_t;

/**
 * \brief Temperature sensor power down type.
 */
typedef uint8_t temp_sensor_power_down_t;

/**
 * \brief Temperature sensor command type.
 */
typedef uint8_t temp_sensor_cmd_t;

/**
 * \brief Temperature sensor device initialization routine.
 *
 * \param[in,out] config is a pointer to the configuration parameters of the temperature sensor device.
 *
 * \return The status/error code.
 */
int temp_sensor_init(temp_sensor_t *config);

/**
 * \brief Temperature sensor power-down.
 *
 * \param[in,out] config is a pointer to the configuration parameters of the temperature sensor device.
 *
 * \param[in] mode is the power-down mode. It can be:
 * \parblock
 *      -\b ADS1248_POWER_DOWN_PIN
 *      -\b ADS1248_POWER_DOWN_CMD
 *      .
 * \endparblock
 *
 * \return The status/error code.
 */
int temp_sensor_suspend(temp_sensor_t *config, temp_sensor_power_down_t mode);

/**
 * \brief Reads the temperature from the temperature sensor.
 *
 * \param[in,out] config is a pointer to the configuration parameters of the temperature sensor device.
 *
 * \param[in] temp is a pointer to store the read temperature.
 *
 * \param[in,out] temp is a pointer to store the read temperature.
 *
 * \return The status/error code.
 */
int temp_sensor_read_c(temp_sensor_t *config, uint8_t positive_channel, float *temp);

/**
 * \brief Converts a raw reading of the temperature sensor to a real temperature in oC.
 *
 * \param[in] raw_volt is a pointer to the raw reading of the temperature.
 *
 * \return The converted temperature in Celsius.
 */
float temp_sensor_convert_raw_to_c(uint8_t *raw_volt);

#endif /* TEMP_SENSOR_H_ */

/** \} End of temp_sensor group */
