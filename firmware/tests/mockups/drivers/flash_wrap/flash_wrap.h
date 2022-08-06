/*
 * flash_wrap.h
 *
 * Copyright (C) 2022, SpaceLab.
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
 * \brief Flash driver wrap definition.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 2022/06/16
 *
 * \defgroup flash_wrap Flash Wrap
 * \ingroup tests
 * \{
 */

#ifndef FLASH_WRAP_H_
#define FLASH_WRAP_H_

#include <stdint.h>

#include <drivers/flash/flash.h>

int __wrap_flash_init(void);

void __wrap_flash_write(uint8_t *data, uint16_t len);

void __wrap_flash_write_single(uint8_t data, uint8_t *addr);

uint8_t __wrap_flash_read_single(uint8_t *addr);

void __wrap_flash_write_long(uint32_t data, uint32_t *addr);

uint32_t __wrap_flash_read_long(uint32_t *addr);

void __wrap_flash_erase(uint32_t *region);

#endif /* FLASH_WRAP_H_ */

/** \} End of flash_wrap group */
