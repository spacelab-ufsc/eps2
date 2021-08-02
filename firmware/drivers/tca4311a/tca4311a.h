/*
 * tca4311a.h
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
 * \brief TCA4311A driver definition.
 * 
 * \authors Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>, Vinicius Pimenta Bernardo <viniciuspibi@gmail.com> and Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 * 
 * \version 0.2.7
 * 
 * \date 2021/07/05
 * 
 * \defgroup tca4311a TCA4311A
 * \ingroup drivers
 * \{
 */

#ifndef TCA4311A_H_
#define TCA4311A_H_

#include <stdint.h>
#include <stdbool.h>

#include <drivers/i2c_slave/i2c_slave.h>
#include <drivers/gpio/gpio.h>

#define TCA4311A_MODULE_NAME            "TCA4311A"

/**
 * \brief TCA4311A configuration parameters.
 */
typedef struct
{
    i2c_slave_port_t i2c_port;          /**< I2C (as slave) port number.*/
    i2c_slave_config_t i2c_config;      /**< I2C (as slave) port configuration. */
    gpio_pin_t en_pin;                  /**< EN GPIO pin. */
    gpio_pin_t ready_pin;               /**< READY GPIO pin. */
} tca4311a_config_t;

/**
 * \brief Chip status.
 */
typedef enum
{
    TCA4311A_ERROR=-1,                  /**< Error during initialization. */
    TCA4311A_READY,                     /**< The chip is ready. */
    TCA4311A_NOT_READY                  /**< The chip is not ready. */
} tca4311a_status_e;

/**
 * \brief Driver initialization.
 *
 * This function initializes the GPIO pins of EN and READY pins.
 *
 * \param[in] config is the configuration parameters of the TCA4311A chip.
 *
 * \param[in] en is a flag to enable or disables the chip after the initialization.
 *
 * \return The status of the chip. It can be:
 * \parblock
 *      -\b TCA4311A_ERROR
 *      -\b TCA4311A_NOT_READY
 *      -\b TCA4311A_READY
 *      .
 * \endparblock
 */
int tca4311a_init(tca4311a_config_t config, bool en);

/**
 * \brief Enables the chip.
 *
 * Puts the EN pin high. EN should be high (at VCC) for normal operation.
 *
 * \see SCPS226C - TCA4311A Hot Swappable 2-Wire Bus Buffers
 *
 * \param[in] config is the configuration parameters of the TCA4311A chip.
 *
 * \return The status of the chip. It can be:
 * \parblock
 *      -\b TCA4311A_ERROR
 *      -\b TCA4311A_NOT_READY
 *      -\b TCA4311A_READY
 *      .
 * \endparblock
 */
int tca4311a_enable(tca4311a_config_t config);

/**
 * \brief Disables the chip.
 *
 * Puts the EN pin low. If EN is low, the TCA4311A is in a low current (<1 μA) mode. It also disables the
 * rise-time accelerators, disables the bus pre-charge circuitry, drives READY low, isolates SDAIN from SDAOUT
 * and isolates SCLIN from SCLOUT.
 *
 * \see SCPS226C - TCA4311A Hot Swappable 2-Wire Bus Buffers
 *
 * \param[in] config is the configuration parameters of the TCA4311A chip.
 *
 * \return The status of the chip. It can be:
 * \parblock
 *      -\b TCA4311A_ERROR
 *      -\b TCA4311A_NOT_READY
 *      -\b TCA4311A_READY
 *      .
 * \endparblock
 */
int tca4311a_disable(tca4311a_config_t config);

/**
 * \brief Verifies if the chip is ready for transfers.
 *
 * Reads the READY pin state. The READY pin is a connection flag/rise-time accelerator control. READY is low when
 * either EN is low or the start-up sequence described in the operation section has not been completed. READY
 * goes high when EN is high and start-up is complete.
 *
 * \see SCPS226C - TCA4311A Hot Swappable 2-Wire Bus Buffers
 *
 * \param[in] config is the configuration parameters of the TCA4311A chip.
 *
 * \return The status of the chip. It can be:
 * \parblock
 *      -\b TCA4311A_ERROR
 *      -\b TCA4311A_NOT_READY
 *      -\b TCA4311A_READY
 *      .
 * \endparblock
 */
int tca4311a_is_ready(tca4311a_config_t config);

#endif /* TCA4311A_H_ */

/** \} End of tca4311a group */
