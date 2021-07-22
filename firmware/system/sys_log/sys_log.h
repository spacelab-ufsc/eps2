/*
 * sys_log.h
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
 * \brief Functions for printing messages and variables over an UART port.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.1.1
 *
 * \date 2020/10/22
 *
 * \defgroup sys_log System Log
 * \ingroup system
 * \{
 */

#ifndef SYS_LOG_H_
#define SYS_LOG_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * \brief Event types.
 */
typedef enum
{
    SYS_LOG_INFO,               /**< Information message. */
    SYS_LOG_WARNING,            /**< Warning message. */
    SYS_LOG_ERROR               /**< Error message. */
} sys_log_event_type_e;

/**
 * \brief System log text colors list.
 */
typedef enum
{
    SYS_LOG_COLOR_BLACK = 0,    /**< Color black. */
    SYS_LOG_COLOR_RED,          /**< Color red. */
    SYS_LOG_COLOR_GREEN,        /**< Color green. */
    SYS_LOG_COLOR_YELLOW,       /**< Color yellow. */
    SYS_LOG_COLOR_BLUE,         /**< Color blue. */
    SYS_LOG_COLOR_MAGENTA,      /**< Color magenta. */
    SYS_LOG_COLOR_CYAN,         /**< Color cyan. */
    SYS_LOG_COLOR_WHITE         /**< Color white. */
} sys_log_colors_e;


/**
 * \brief Initialization of the system log.
 *
 * \return The error/status code.
 */
int sys_log_init(void);

/**
 * \brief Sets the foreground color for the next log message.
 *
 * This function uses the ANSI color code to output color log messages.
 *
 * \param[in] color is the foreground color of text to select. It can be:
 * \parblock
 *      -\b SYS_LOG_COLOR_BLACK
 *      -\b SYS_LOG_COLOR_RED
 *      -\b SYS_LOG_COLOR_GREEN
 *      -\b SYS_LOG_COLOR_YELLOW
 *      -\b SYS_LOG_COLOR_BLUE
 *      -\b SYS_LOG_COLOR_MAGENTA
 *      -\b SYS_LOG_COLOR_CYAN
 *      -\b SYS_LOG_COLOR_WHITE
 *      .
 * \endparblock
 *
 * \return None.
 */
void sys_log_set_color(uint8_t color);

/**
 * \brief Resets the color back to normal.
 *
 * \return None.
 */
void sys_log_reset_color(void);

/**
 * \brief Prints a general event.
 *
 * \param[in] type is the type of event. It can be:
 * \parblock
 *      -\b SYS_LOG_INFO
 *      -\b SYS_LOG_WARNING
 *      -\b SYS_LOG_ERROR
 *      .
 * \endparblock
 *
 * \param[in] event is the event text.
 *
 * \return None.
 */
void sys_log_print_event(uint8_t type, const char *event);

/**
 * \brief Prints an event from a system module.
 *
 * \param[in] type is the type of event. It can be:
 * \parblock
 *      -\b SYS_LOG_INFO
 *      -\b SYS_LOG_WARNING
 *      -\b SYS_LOG_ERROR
 *      .
 * \endparblock
 *
 * \param[in] module is the module name.
 *
 * \param[in] event is the event text.
 *
 * \return None.
 */
void sys_log_print_event_from_module(uint8_t type, const char *module, const char *event);

/**
 * \brief Prints a message over the system log module.
 *
 * \param[in] msg is the message to be written.
 *
 * \return None.
 */
void sys_log_print_msg(const char *msg);

/**
 * \brief Prints an string over the system log module.
 *
 * \param[in] str is a pointer to an string.
 *
 * \return None.
 */
void sys_log_print_str(char *str);

/**
 * \brief Prints a new line.
 *
 * \return None.
 */
void sys_log_new_line(void);

/**
 * \brief Prints a integer digit over the system log module.
 *
 * \param[in] d is the digit to be written (0 to 9)
 *
 * \return None.
 */
void sys_log_print_digit(uint8_t d);

/**
 * \brief Prints an unsigned integer over the system log module.
 *
 * \param[in] uint is the unsigned integer number to print.
 *
 * \return None.
 */
void sys_log_print_uint(uint32_t uint);

/**
 * \brief Prints a signed integer over the system log module.
 *
 * \param[in] sint is the signed integer number to print.
 *
 * \return None.
 */
void sys_log_print_int(int32_t sint);

/**
 * \brief Prints a hexadecimal value over the system log module.
 *
 * Example:
 *      - Integer   = 0x65
 *      - Output    = "0x65"
 *
 * \note The integer is printed in ASCII code.
 *
 * \param hex is the hexadecimal to be written.
 *
 * \return None.
 */
void sys_log_print_hex(uint32_t hex);

/**
 * \brief Prints a array of bytes in hexadecimal format.
 *
 * \param[in] data is an array of bytes to print.
 *
 * \param[in] len is the number of bytes to print.
 *
 * \return None.
 */
void sys_log_dump_hex(uint8_t *data, uint16_t len);

/**
 * \brief Prints a float number over the system log module.
 *
 * \param[in] flt is the float number to print.
 *
 * \param[in] digits is the number of digits to print.
 *
 * \return None.
 */
void sys_log_print_float(float flt, uint8_t digits);

/**
 * \brief Prints a raw byte over the system log module.
 *
 * \param[in] byte is the byte to be printed.
 *
 * \return None.
 */
void sys_log_print_byte(uint8_t byte);

/**
 * \brief Prints the system time in milliseconds.
 *
 * \return None.
 */
void sys_log_print_system_time(void);

/**
 * \brief Prints the license text and genreal firmware information.
 *
 * \return None.
 */
void sys_log_print_license_msg(void);

/**
 * \brief Prints the splash screen of the firmware.
 *
 * \return None.
 */
void sys_log_print_splash_screen(void);

/**
 * \brief Writes the current firmware version.
 *
 * \return None.
 */
void sys_log_print_firmware_version(void);

/**
 * \brief Initialization of the system log UART port.
 *
 * UART settings:
 *      -\b MCU interface = USCI_A1
 *      -\b Baudrate      = 115200 bps
 *      -\b Data bits     = 8
 *      -\b Parity bit    = None
 *      -\b Stop bits     = 1
 *      .
 *
 * \return TRUE/FALSE if successful or not.
 */
bool sys_log_uart_init(void);

/**
 * \brief Writes a byte over the UART port.
 *
 * \param[in] byte is the byte to be written.
 *
 * \return None.
 */
void sys_log_uart_write_byte(uint8_t byte);

/**
 * \brief Creates a mutex to use the system log module.
 *
 * \return TRUE/FALSE if successful or not.
 */
bool sys_log_mutex_create(void);

/**
 * \brief Holds the resource (system log module).
 *
 * \return TRUE/FALSE if successful or not.
 */
bool sys_log_mutex_take(void);

/**
 * \brief Frees the resource (system log).
 *
 * \return TRUE/FALSE if successful or not.
 */
bool sys_log_mutex_give(void);

#endif /* SYS_LOG_H_ */

/** \} End of sys_log group */
