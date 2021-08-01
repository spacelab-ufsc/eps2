/*
 * ttc.h
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
 * \brief TTC device definition.
 *
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * \author Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 *
 * \version 0.2.4
 *
 * \date 22/04/2020
 *
 * \defgroup ttc TTC
 * \ingroup devices
 * \{
 */

#ifndef TTC_H_
#define TTC_H_

#include <stdint.h>

#define TTC_MODULE_NAME         "TTC"

#define TTC_COMMAND_READ_SIZE	 2
#define TTC_COMMAND_WRITE_SIZE	 6

/**
 * \brief UART ports.
 */
typedef enum
{
    TTC_COMMAND_WRITE=0,        /**< TTC command for writing an EPS register. */
    TTC_COMMAND_READ            /**< TTC command for reading an EPS register. */
} ttc_command_e;

/**
 * \brief TTC configuration type.
 */
typedef struct
{
    uart_interrupt_port_t uart_port;      		/**< UART port number. */
    uart_interrupt_config_t uart_config;		/**< UART port configuration. */
} ttc_config_t;

/**
 * \brief Initialization routine of the TTC device.
 *
 * \return The status/error code.
 */
int ttc_init(void);

/**
 * \brief Answers a command from the TTC.
 *
 * \param[in] adr is the register address requested.
 *
 * \param[in,out] val is the value to answer to the TTC.
 *
 * \return The status/error code.
 */
int sl_ttc2_answer(uint8_t adr, uint32_t val);

#endif /* TTC_H_ */

/** \} End of ttc group */
