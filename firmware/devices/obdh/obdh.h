/*
 * obdh.h
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
 * \brief OBDH device definition.
 *
 * \author Andre M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * \author Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.2.40
 *
 * \date 2020/04/22
 *
 * \defgroup obdh OBDH
 * \ingroup devices
 * \{
 */

#ifndef OBDH_H_
#define OBDH_H_

#include <stdint.h>

#include <drivers/tca4311a/tca4311a.h>

#define OBDH_MODULE_NAME         "OBDH"

#define EPS_SLAVE_ADDRESS        0x36

#define OBDH_COMMAND_READ_SIZE	 2
#define OBDH_COMMAND_WRITE_SIZE	 6

/**
 * \brief OBDH command types.
 */
typedef enum
{
    OBDH_COMMAND_WRITE=0,        /**< OBDH command for writing an EPS register. */
    OBDH_COMMAND_READ            /**< OBDH command for reading an EPS register. */
} obdh_command_e;

/**
 * \brief Configuration parameters structure of the driver.
 */
typedef tca4311a_config_t obdh_config_t;

/**
 * \brief Initialization routine of the OBDH device.
 *
 * \return The status/error code.
 */
int obdh_init(void);

/**
 * \brief Decodes a command from the OBDH.
 *
 * \param[out] adr is the decoded register address.
 *
 * \param[out] val is the decoded register data.
 *
 * \param[out] cmd is the decoded command resquested.
 *
 * \return The status/error code.
 */
int obdh_decode(uint8_t *adr, uint32_t *val, uint8_t *cmd);

/**
 * \brief Writes data to the output buffer.
 *
 * \param[in] adr is the register address requested.
 *
 * \param[in,out] val is the value to be read by the OBDH.
 *
 * \return The status/error code.
 */
int obdh_write_output_buffer(uint8_t adr, uint32_t val);

/**
 * \brief Computes the CRC-8 of a sequence of bytes.
 *
 * \param[in] data is an array of data to compute the CRC-8.
 *
 * \param[in] len is the number of bytes of the given array.
 *
 * \return The computed CRC-8 value of the given data.
 */
uint8_t obdh_crc8(uint8_t *data, uint8_t len);

/**
 * \brief Checks the CRC value of a given sequence of bytes.
 *
 * \param[in] data is the data to check the CRC.
 *
 * \param[in] len is the number of bytes to check the CRC value.
 *
 * \param[in] crc is the CRC-8 value to check.
 *
 * \return TRUE/FALSE if the given CRC value is correct or not.
 */
bool obdh_check_crc(uint8_t *data, uint8_t len, uint8_t crc);

#endif /* OBDH_H_ */

/** \} End of obdh group */
