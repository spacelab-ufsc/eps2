/*
 * crc.h
 * 
 * Copyright (C) 2017-2019, Federal University of Santa Catarina
 * 
 * This file is part of FloripaSat-FSP.
 * 
 * FloripaSat-FSP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FloripaSat-FSP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with FloripaSat-FSP. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief CRC functions.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.0
 * 
 * \date 07/11/2017
 * 
 * \defgroup crc CRC
 * \{
 */

#ifndef CRC_H_
#define CRC_H_

#include <stdint.h>

/**
 * \brief Computes the CRC16-CCITT value of an array of data.
 * 
 * \param initial_value is the initial value to compute the crc16 value.
 * \param data is the data to compute the crc16 value.
 * \param size is the length of the data array.
 * 
 * \return Returns the crc16 value of the data.
 */
uint16_t crc16_CCITT(uint16_t initial_value, uint8_t* data, uint8_t size);

#endif // CRC_H_

//! \} End of crc group
