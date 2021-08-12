/*
 * sys_log_wrap.h
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
 * \brief System log wrap definition.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 2021/07/22
 *
 * \defgroup sys_log_wrap System Log Wrap
 * \ingroup tests
 * \{
 */

#ifndef SYS_LOG_WRAP_H_
#define SYS_LOG_WRAP_H_

#include <stdint.h>

int __wrap_sys_log_init(void);

void __wrap_sys_log_print_event(uint8_t type, const char *event);

void __wrap_sys_log_print_event_from_module(uint8_t type, const char *module, const char *event);

void __wrap_sys_log_print_msg(const char *msg);

void __wrap_sys_log_print_str(char *str);

void __wrap_sys_log_new_line(void);

void __wrap_sys_log_print_uint(uint32_t uint);

void __wrap_sys_log_print_int(int32_t sint);

void __wrap_sys_log_print_hex(uint32_t hex);

void __wrap_sys_log_dump_hex(uint8_t *data, uint16_t len);

void __wrap_sys_log_print_float(float flt, uint8_t digits);

void __wrap_sys_log_print_byte(uint8_t byte);

void __wrap_sys_log_print_system_time(void);

void __wrap_sys_log_print_license_msg(void);

void __wrap_sys_log_print_splash_screen(void);

void __wrap_sys_log_print_firmware_version(void);

#endif /* SYS_LOG_WRAP_H_ */

/** \} End of sys_log_wrap group */
