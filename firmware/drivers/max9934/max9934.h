/*
 * max9934.h
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
 * \brief MAX9934 driver definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 2020/10/24
 * 
 * \defgroup max9934 MAX9934
 * \ingroup drivers
 * \{
 */

#ifndef MAX9934_H_
#define MAX9934_H_

#include <drivers/gpio/gpio.h>
#include <drivers/adc/adc.h>

/**
 * \brief MAX9934 configuration parameters.
 */
typedef struct
{
    gpio_pin_t cs_pin;          /**< CS pin. */
    gpio_config_t cs_config;    /**< Configuration parameters of the CS pin. */
    adc_port_t adc_port;        /**< ADC port. */
    adc_config_t adc_config;    /**< Configuration parameters of the ADC port. */
} max9934_config_t;

/**
 * \brief MAX9934 initialization.
 *
 * \param[in,out] config is a pointer to the MAX9934 configuration parameters.
 *
 * \return The status/error code.
 */
int max9934_init(max9934_config_t *config);

/**
 * \brief Enables a given MAX9934 device.
 *
 * This funcition sets the CS pin of the given MAX9934 device.
 *
 * \param[in,out] config is a pointer to the MAX9934 configuration parameters.
 *
 * \return The status/error code.
 */
int max9934_enable(max9934_config_t *config);

/**
 * \brief Disables a given MAX9934 device.
 *
 * This funcition clears the CS pin of the given MAX9934 device.
 *
 * \param[in,out] config is a pointer to the MAX9934 configuration parameters.
 *
 * \return The status/error code.
 */
int max9934_disable(max9934_config_t *config);

/**
 * \brief Reads the raw current value of the sensor.
 *
 * \param[in,out] config is a pointer to the MAX9934 configuration parameters.
 *
 * \param[in,out] raw_val is a pointer to store the read value.
 *
 * \return The status/error code.
 */
int max9934_read(max9934_config_t *config, uint16_t *raw_val);

#endif /* MAX9934_H_ */

/** \} End of max9934 group */
