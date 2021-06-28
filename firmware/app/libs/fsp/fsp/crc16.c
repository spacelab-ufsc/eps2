/*
 * crc16.c
 * 
 * Copyright (C) 2017-2019, Federal University of Santa Catarina.
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
 * \brief CRC16 implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.0
 * 
 * \date 07/11/2017
 * 
 * \addtogroup crc
 * \{
 */

#include "crc.h"

uint16_t crc16_CCITT(uint16_t initial_value, uint8_t* data, uint8_t size)
{
    uint8_t x;
    uint16_t crc = initial_value;
    
    while(size--)
    {
        x = crc >> 8 ^ *data++;
        x ^= x >> 4;
        crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ ((uint16_t)(x << 5)) ^ ((uint16_t)x);
    }
    
    return crc;
}

//! \} End of crc group
