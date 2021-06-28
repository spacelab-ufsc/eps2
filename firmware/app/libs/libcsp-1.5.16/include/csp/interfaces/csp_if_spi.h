/*
 * csp_if_spi.h
 * 
 * Copyright (C) 2020, SpaceLab.
 * 
 * This file is part of OBDH 2.0.
 * 
 * OBDH 2.0 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * OBDH 2.0 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with OBDH 2.0. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief libcsp SPI interface definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.7
 * 
 * \date 05/04/2020
 * 
 * \defgroup csp_if_spi CSP SPI interface
 * \{
 */

#ifndef CSP_IF_SPI_H_
#define CSP_IF_SPI_H_

#include <csp/csp.h>
#include <csp/csp_interface.h>

/**
 * \brief SPI interface.
 */
extern csp_iface_t csp_if_spi;

/**
 * \brief SPI interface initialization.
 *
 * \return The status/error code.
 */
int csp_spi_init();

/**
 * \brief SPI TX routine.
 *
 * \return The status/error code.
 */
int csp_spi_write();

/**
 * \brief SPI RX routine.
 *
 * \return None.
 */
void csp_spi_read();

#endif /* CSP_IF_SPI_H_ */

/** \} End of csp_if_spi group */
