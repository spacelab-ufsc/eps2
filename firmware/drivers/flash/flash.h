/*
 * flash.h
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
 * \brief Flash driver definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 2020/10/24
 * 
 * \defgroup flash Flash
 * \ingroup drivers
 * \{
 */

#ifndef FLASH_H_
#define FLASH_H_

#include <stdint.h>

/* 128 kB banks */
#define FLASH_BANK_0_ADR            0x00008000
#define FLASH_BANK_1_ADR            0x00028000
#define FLASH_BANK_2_ADR            0x00048000
#define FLASH_BANK_3_ADR            0x00068000

/* 128 B info segments */
#define FLASH_SEG_A_ADR             0x00001980
#define FLASH_SEG_B_ADR             0x00001900
#define FLASH_SEG_C_ADR             0x00001880
#define FLASH_SEG_D_ADR             0x00001800

/* 512 B bootstrap segments */
#define FLASH_BSL_0_ADR             0x00001600
#define FLASH_BSL_1_ADR             0x00001400
#define FLASH_BSL_2_ADR             0x00001200
#define FLASH_BSL_3_ADR             0x00001000

#define FLASH_MASS_ERASE            0X00FFFFFF

/* Overflow flag message adress */
#define FLASH_OVERFLOW_FLAG_ADDR    0x00026000

/* Last adress that can write a data(beyond this will enter the overflow) */
#define FLASH_LAST_WRITE_ADDR       0x00087FFF

/**
 * \brief Flash memory initialization.
 *
 * \return The status/error code.
 */
int flash_init();

/**
 * \brief Writes data into the flash memory.
 *
 * \param[in] data is an array of bytes to write.
 *
 * \param[in] len is the number of bytes to write.
 *
 * \return None.
 */
void flash_write(uint8_t *data, uint16_t len);

/**
 * \brief Writes a single byte.
 *
 * \param[in] data is the byte to be written.
 *
 * \param[in] addr is the address to write the given byte.
 *
 * \return None.
 */
void flash_write_single(uint8_t data, uint8_t *addr);

/**
 * \brief Reads an 8-bit data from a memory address.
 *
 * \param[in] addr is the address to read.
 *
 * \return None.
 */
uint8_t flash_read_single(uint8_t *addr);

/**
 * \brief Writes a 32-bits data.
 *
 * \param[in] data is the 32-bit data to be written.
 *
 * \param[in] addr is the address to write the given data.
 *
 * \return None.
 */
void flash_write_long(uint32_t data, uint32_t *addr);

/**
 * \brief Reads a 32-bit data from a memory address.
 *
 * \param[in] addr is the address to read.
 *
 * \return None.
 */
uint32_t flash_read_long(uint32_t *addr);

/**
 * \brief Erases a memory region.
 *
 * \param[in] region is the memory region to erase.
 *
 * \return None.
 */
void flash_erase(uint32_t *region);

#endif /* FLASH_H_ */

/** \} End of flash group */
