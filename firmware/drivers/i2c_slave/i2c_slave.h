/*
 * i2c_slave.h
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
 * \brief I2C driver definition.
 * 
 * \author Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * 
 * \version 0.1.15
 * 
 * \date 2021/06/22
 * 
 * \defgroup i2c_slave I2C_Slave
 * \ingroup drivers
 * \{
 */

#ifndef I2C_SLAVE_H_
#define I2C_SLAVE_H_

#include <stdint.h>

#include <drivers/i2c/i2c.h>

#define I2C_SLAVE_MODULE_NAME "I2C_SLAVE"

#define EPS_SLAVE_ADDRESS 0x36 /**< 7-bit slave address. */

/**
 * \brief I2C modes.
 */
typedef enum
{
    I2C_RECEIVE_MODE = 0,
    I2C_TRANSMIT_MODE
} i2c_mode_e;

/**
 * \brief I2C mode.
 */
typedef uint8_t i2c_mode_t;

/**
 * @brief I2C interface configuration as slave.
 * 
 * @param[in] port
 * \parblock
 *      -\b I2C_PORT_0
 *      -\b I2C_PORT_1
 *      -\b I2C_PORT_2
 * \endparblock
 * 
 * @param[in] config 
 * 
 * @return The status/error code.
 */
int i2c_slave_init(i2c_port_t port);

/**
 * @brief I2C interface mode selection.
 *
 * @param[in] port
 * \parblock
 *      -\b I2C_PORT_0
 *      -\b I2C_PORT_1
 *      -\b I2C_PORT_2
 * \endparblock
 *
 * @param[in] mode
 * \parblock
 *      -\b I2C_RECEIVE_MODE
 *      -\b I2C_TRANSMIT_MODE
 * \endparblock
 *
 * @return The status/error code.
 */
int i2c_slave_set_mode(i2c_port_t port, i2c_mode_t mode);

/**
 * @brief I2C interface operation start as slave and interrupt enabling.
 * 
 * @param[in] port 
 * @return The status/error code.
 */
int i2c_slave_enable(i2c_port_t port);

/**
 * @brief I2C interface operation stop as slave and interrupt disabling.
 * 
 * @param[in] port 
 * @return The status/error code. 
 */
int i2c_slave_disable(i2c_port_t port);

/**
 * @brief I2C ISR function.
 * 
 */
void USCIB0_ISR(void);

#endif /* I2C_SLAVE_H_ */

/** \} End of i2c_slave group */
