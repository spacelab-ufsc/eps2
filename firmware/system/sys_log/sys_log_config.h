/*
 * sys_log_config.h
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EPS 2.0. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * \brief System log configuration parameters.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 2020/10/22
 *
 * \defgroup sys_log_config Configuration
 * \ingroup sys_log
 * \{
 */

#ifndef SYS_LOG_CONFIG_H_
#define SYS_LOG_CONFIG_H_

#include <config/config.h>

#include "sys_log.h"

/* Device name */
#define SYS_LOG_DEVICE_NAME             "System Log"

/* UART */
#define SYS_LOG_UART_BAUDRATE_BPS       115200

/* Mutex config. */
#define SYS_LOG_MUTEX_WAIT_TIME_MS      100

/* Log messages colors */
#define SYS_LOG_SYSTEM_TIME_COLOR       SYS_LOG_COLOR_CYAN
#define SYS_LOG_MODULE_NAME_COLOR       SYS_LOG_COLOR_MAGENTA
#define SYS_LOG_INFO_COLOR              SYS_LOG_COLOR_GREEN
#define SYS_LOG_WARNING_COLOR           SYS_LOG_COLOR_YELLOW
#define SYS_LOG_ERROR_COLOR             SYS_LOG_COLOR_RED

#endif /* SYS_LOG_CONFIG_H_ */

/** \} End of sys_log_config group */
