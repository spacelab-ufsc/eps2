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
 * \version 0.2.26
 * 
 * \date 2021/06/11
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

#define TEMP_SENSOR_ADC_PORT        ADC_PORT_0
#define TEMP_SENSOR_SPI_PORT        SPI_PORT_1
#define TEMP_SENSOR_SPI_MODE        SPI_MODE_0
#define TEMP_SENSOR_SPI_SPEED_HZ    (100000UL)
#define TEMP_SENSOR_START_PIN       GPIO_PIN_60
#define TEMP_SENSOR_SPI_CS          GPIO_PIN_59
#define TEMP_SENSOR_RESET_PIN       GPIO_PIN_58

#define TEMP_SENSOR_CONV(VALUE)     ((((uint32_t)VALUE * (1.65 * 2 / 16777216) * 1000) - 1000 ) * (1/3.85))   /**< TODO: Solve magic conversion */

/**
 * \brief Temperature sensor RTD channels.
 */
typedef enum
{
    TEMP_SENSOR_RTD_CH_0=0,
    TEMP_SENSOR_RTD_CH_1,
    TEMP_SENSOR_RTD_CH_2,
    TEMP_SENSOR_RTD_CH_3,
    TEMP_SENSOR_RTD_CH_4,
    TEMP_SENSOR_RTD_CH_5,
    TEMP_SENSOR_RTD_CH_6,
} temp_rtd_channel_e;

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
 * This function initilizes both the MCU internal temperature sensor and the external ADC (ADS1248) used for reading temperature from RTDs.
 *
 * \param[in,out] config is a pointer to the configuration parameters of the temperature sensor device.
 *
 * \return The status/error code.
 */
int temp_sensor_init(void);

/**
 * \brief External temperature sensor device (ADS1248) power-down.
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
 * \brief Reads the raw MCU temperature from its internal sensor.
 *
 * \param[in,out] val is a pointer to store the raw value of the temperature.
 *
 * \return The status/error code.
 */
int temp_mcu_read_raw(uint16_t *val);

/**
 * \brief Converts a raw reading of the internal temperature sensor of the MCU to real temperature in degrees celsius.
 *
 * \param[in] raw is the raw reading of the temperature.
 *
 * \return The converted temperature in degrees celsius.
 */
int16_t temp_mcu_raw_to_c(uint16_t raw);

/**
 * \brief Converts a raw reading of the internal temperature sensor of the MCU to a real temperature in kelvin.
 *
 * \param[in] raw is the raw reading of the temperature.
 *
 * \return The converted temperature in Kelvin.
 */
uint16_t temp_mcu_raw_to_k(uint16_t raw);

/**
 * \brief Reads the temperature from the internal MCU temperature sensor in degrees celsius.
 *
 * \param[in,out] temp is a pointer to store the read temperature.
 *
 * \return The status/error code.
 */
int temp_mcu_read_c(int16_t *temp);

/**
 * \brief Reads the temperature from the internal MCU temperature sensor in Kelvin.
 *
 * \param[in,out] temp is a pointer to store the read temperature.
 *
 * \return The status/error code.
 */
int temp_mcu_read_k(uint16_t *temp);

/**
 * \brief Reads the raw temperature from rtds acquired by external temperature sensor device (ADS1248).
 *
 * \param[in,out] config is a pointer to the configuration parameters of the device.
 *
 * \param[in] positive_channel selects channel to read the temperature.
 *
 * \param[in,out] val is a pointer to store the read temperature.
 *
 * \return The status/error code.
 */
int temp_rtd_read_raw(uint8_t positive_channel, uint32_t *val);

/**
 * \brief Converts a raw reading of temperature from rtds to a real temperature in degrees celsius.
 *
 * \param[in] raw is the raw reading of the temperature.
 *
 * \return The converted temperature in degrees celsius.
 */
int16_t temp_rtd_raw_to_c(uint32_t raw);

/**
 * \brief Converts a raw reading of temperature from rtds to a real temperature in kelvin.
 *
 * \param[in] raw is the raw reading of the temperature.
 *
 * \return The converted temperature in kelvin.
 */
uint16_t temp_rtd_raw_to_k(uint32_t raw);

/**
 * \brief read temperatures from rtds in degrees celsius.
 *
 * \return The status/error code.
 */
int temp_rtd_read_c(uint8_t channel, uint16_t *temp);

/**
 * \brief read temperatures from rtds in kelvin.
 *
 * \return The status/error code.
 */
int temp_rtd_read_k(uint8_t channel, uint16_t *temp);

#endif /* TEMP_SENSOR_H_ */

/** \} End of temp_sensor group */
