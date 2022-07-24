/*
 * flash_wrap.c
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
 * \brief Flash driver wrap implementation.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 2022/08/07
 *
 * \addtogroup flash_wrap
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include "flash_wrap.h"

int __wrap_flash_init(void)
{
    return mock_type(int);
}

void __wrap_flash_write(uint8_t *data, uint16_t len)
{
    check_expected_ptr(data);
    check_expected(len);

    return;
}

void __wrap_flash_write_single(uint8_t data, uint8_t *addr)
{
    check_expected(data);
    if (addr != NULL)
    {
        *addr = mock_type(uint8_t);
    }

    return;
}

uint8_t __wrap_flash_read_single(uint8_t *addr)
{
    return mock_type(uint8_t);
}

void __wrap_flash_write_long(uint32_t data, uint32_t *addr)
{
    check_expected(data);
}

uint32_t __wrap_flash_read_long(uint32_t *addr)
{
    return mock_type(uint8_t);
}

void __wrap_flash_erase(uint32_t *region)
{
    check_expected_ptr(region);

    return;
}

/** \} End of flash_wrap group */
