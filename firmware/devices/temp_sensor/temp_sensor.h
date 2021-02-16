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
 * \version 0.1.0
 * 
 * \date 2021/01/28
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

#define TEMP_SENSOR_SPI_PORT        SPI_PORT_1
#define TEMP_SENSOR_SPI_MODE        SPI_MODE_0
#define TEMP_SENSOR_SPI_SPEED_HZ    1000000
#define TEMP_SENSOR_START_PIN       GPIO_PIN_60
#define TEMP_SENSOR_SPI_CS          GPIO_PIN_59
#define TEMP_SENSOR_RESET_PIN       GPIO_PIN_58

/**
 * \brief Temperature sensor device initialization routine.
 *
 * \return The status/error code.
 */
int temp_sensor_init();

/**
 * \brief Temperature sensor power-down.
 *
 * \param[in,out] config is a pointer to the configuration parameters of the ADS1248 device.
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
int temp_sensor_suspend(ads1248_config_t *config, ads1248_power_down_t mode);

/**
 * \brief Reads the raw temperature from the temperature sensor.
 *
 * \param[in,out] val is a pointer to store the raw value of the temperature.
 *
 * \return The status/error code.
 */
int temp_sensor_read_raw(uint16_t *val);

/**
 * \brief Reads the temperature from the temperature sensor.
 *
 * \param[in,out] temp is a pointer to store the read temperature.
 *
 * \return The status/error code.
 */
int temp_sensor_read(float *temp);

#endif /* TEMP_SENSOR_H_ */

/** \} End of temp_sensor group */