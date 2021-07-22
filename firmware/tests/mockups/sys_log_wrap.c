/*
 * sys_log_wrap.c
 *
 * Copyright (C) 2021, SpaceLab.
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
 * \brief System log wrap implementation.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 2021/07/22
 *
 * \addtogroup sys_log_wrap
 * \{
 */

#include <stdint.h>

#include "sys_log_wrap.h"

int __wrap_sys_log_init(void)
{
    return 0;
}

void __wrap_sys_log_print_event(uint8_t type, const char *event)
{
    return;
}

void __wrap_sys_log_print_event_from_module(uint8_t type, const char *module, const char *event)
{
    return;
}

void __wrap_sys_log_print_msg(const char *msg)
{
    return;
}

void __wrap_sys_log_print_str(char *str)
{
    return;
}

void __wrap_sys_log_new_line(void)
{
    return;
}

void __wrap_sys_log_print_uint(uint32_t uint)
{
    return;
}

void __wrap_sys_log_print_int(int32_t sint)
{
    return;
}

void __wrap_sys_log_print_hex(uint32_t hex)
{
    return;
}

void __wrap_sys_log_dump_hex(uint8_t *data, uint16_t len)
{
    return;
}

void __wrap_sys_log_print_float(float flt, uint8_t digits)
{
    return;
}

void __wrap_sys_log_print_byte(uint8_t byte)
{
    return;
}

void __wrap_sys_log_print_system_time(void)
{
    return;
}

void __wrap_sys_log_print_license_msg(void)
{
    return;
}

void __wrap_sys_log_print_splash_screen(void)
{
    return;
}

void __wrap_sys_log_print_firmware_version(void)
{
    return;
}
