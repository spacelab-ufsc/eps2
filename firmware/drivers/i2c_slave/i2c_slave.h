/*
 * i2c_slave.h
 * 
 * Copyright The EPS 2.0 Contributors.
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
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.39
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

#define I2C_SLAVE_MODULE_NAME               "I2C_SLAVE"

#define I2C_RX_BUFFER_MAX_SIZE              16              /**< Number of bytes of the maximum I2C RX buffer size. */
#define I2C_TX_BUFFER_MAX_SIZE              16              /**< Number of bytes of the maximum I2C TX buffer size. */

#define I2C_SLAVE_NOTI_VAL_TO_I2C_RX_ISR    (1UL << 0UL)    /**< Bit to set on I2C RX notification for tasks. */
#define I2C_SLAVE_NOTI_VAL_TO_I2C_TX_ISR    (1UL << 1UL)    /**< Bit to set on I2C TX notification for tasks. */

/**
 * \brief I2C port type.
 */
typedef uint8_t i2c_slave_port_t;

/**
 * \brief I2C address type.
 */
typedef uint8_t i2c_slave_address_t;

/**
 * \brief I2C modes.
 */
typedef enum
{
    I2C_SLAVE_RECEIVE_MODE = 0,
    I2C_SLAVE_TRANSMIT_MODE
} i2c_mode_t;

/**
 * \brief I2C interface configuration as slave.
 * 
 * \param[in] port is the I2C port to initialize as slave. It can be:
 * \parblock
 *      -\b I2C_PORT_0
 *      -\b I2C_PORT_1
 *      -\b I2C_PORT_2
 *      .
 * \endparblock
 * 
 * \param[in] adr is the address to use as an slave device.
 * 
 * \return The status/error code.
 */
int i2c_slave_init(i2c_slave_port_t port, i2c_slave_address_t adr);

/**
 * \brief I2C interface operation start as slave and interrupt enabling.
 * 
 * \return The status/error code.
 */
int i2c_slave_enable(void);

/**
 * \brief I2C interface operation stop as slave and interrupt disabling.
 * 
 * \return The status/error code.
 */
int i2c_slave_disable(void);

/**
 * \brief Reads the I2C slave buffer.
 *
 * \param[in,out] data is the array to store the read data.
 *
 * \param[in,out] len is the number of read bytes.
 *
 * \reutrn The status/error code.
 */
int i2c_slave_read(uint8_t *data, uint16_t *len);

/**
 * \brief Writes data to a given I2C port.
 *
 * \param[in] data is the data to write to the I2C port.
 *
 * \param[in] len is the number of bytes to write.
 *
 * \return The status/error code.
 */
int i2c_slave_write(uint8_t *data, uint16_t len);

/**
 * @brief Notifies the I2C slave RX handler task.
 *
 * @note This function should be implemented at a higher level.
 */
void i2c_slave_notify_from_i2c_rx_isr(void);

#endif /* I2C_SLAVE_H_ */

/** \} End of i2c_slave group */
