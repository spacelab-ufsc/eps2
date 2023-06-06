/*
 * sys_log.c
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
 * \brief System log implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.2
 * 
 * \date 2020/10/22
 * 
 * \addtogroup sys_log
 * \{
 */

#include <math.h>

#include <FreeRTOS.h>
#include <task.h>

#include <version.h>

#include "config/config.h"

#include "sys_log.h"
#include "sys_log_config.h"

static volatile uint8_t sys_log_current_level = SYS_LOG_INFO;

int sys_log_init()
{
    if (sys_log_uart_init())
    {
        sys_log_new_line();

        sys_log_print_license_msg();

        sys_log_print_splash_screen();

        sys_log_print_msg("===================================================================");
        sys_log_new_line();
        sys_log_print_msg("Version:\t");
        sys_log_print_firmware_version();
        sys_log_new_line();

        sys_log_print_msg("Status:\t\t");
        sys_log_print_msg(FIRMWARE_STATUS);
        sys_log_new_line();

        sys_log_print_msg("Author:\t\t");
        sys_log_print_msg(FIRMWARE_AUTHOR);
        sys_log_print_msg(" <");
        sys_log_print_msg(FIRMWARE_AUTHOR_EMAIL);
        sys_log_print_msg(">");
        sys_log_new_line();
        sys_log_print_msg("===================================================================");
        sys_log_new_line();
        sys_log_new_line();
        sys_log_new_line();

        sys_log_mutex_create();

        return 0;
    }
    else
    {
        return -1;
    }
}

void sys_log_set_color(uint8_t color)
{
    switch(color)
    {
        case SYS_LOG_COLOR_BLACK:
            sys_log_print_msg("\033[1;30m");
            break;
        case SYS_LOG_COLOR_RED:
            sys_log_print_msg("\033[1;31m");
            break;
        case SYS_LOG_COLOR_GREEN:
            sys_log_print_msg("\033[1;32m");
            break;
        case SYS_LOG_COLOR_YELLOW:
            sys_log_print_msg("\033[1;33m");
            break;
        case SYS_LOG_COLOR_BLUE:
            sys_log_print_msg("\033[1;34m");
            break;
        case SYS_LOG_COLOR_MAGENTA:
            sys_log_print_msg("\033[1;35m");
            break;
        case SYS_LOG_COLOR_CYAN:
            sys_log_print_msg("\033[1;36m");
            break;
        case SYS_LOG_COLOR_WHITE:
            sys_log_print_msg("\033[1;37m");
            break;
        default:
            sys_log_reset_color();
    }
}

void sys_log_reset_color()
{
    sys_log_print_msg("\033[0m");
}

void sys_log_print_event(uint8_t type, const char *event)
{
    sys_log_current_level = type;
    if (sys_log_current_level >= CONFIG_GLOBAL_LOG_LEVEL)
    {
        sys_log_mutex_take();

        sys_log_print_system_time();
        sys_log_print_msg(" ");

        switch(type)
        {
            case SYS_LOG_INFO:
                sys_log_set_color(SYS_LOG_INFO_COLOR);
                break;
            case SYS_LOG_WARNING:
                sys_log_set_color(SYS_LOG_WARNING_COLOR);
                break;
            case SYS_LOG_ERROR:
                sys_log_set_color(SYS_LOG_ERROR_COLOR);
                break;
            default:
                break;
        }

        sys_log_print_msg(event);
    }
}

void sys_log_print_event_from_module(uint8_t type, const char *module, const char *event)
{
    sys_log_current_level = type;
    if (sys_log_current_level >= CONFIG_GLOBAL_LOG_LEVEL)
    {
        sys_log_mutex_take();

        sys_log_print_system_time();

        sys_log_set_color(SYS_LOG_MODULE_NAME_COLOR);
        sys_log_print_msg(" ");
        sys_log_print_msg(module);
        sys_log_reset_color();
        sys_log_print_msg(": ");

        switch(type)
        {
            case SYS_LOG_INFO:
                sys_log_set_color(SYS_LOG_INFO_COLOR);
                break;
            case SYS_LOG_WARNING:
                sys_log_set_color(SYS_LOG_WARNING_COLOR);
                break;
            case SYS_LOG_ERROR:
                sys_log_set_color(SYS_LOG_ERROR_COLOR);
                break;
            default:
                break;
        }

        sys_log_print_msg(event);
    }
}

void sys_log_print_msg(const char *msg)
{
    if (sys_log_current_level >= CONFIG_GLOBAL_LOG_LEVEL)
    {
        uint16_t i = 0;
        while(msg[i] != '\0')
        {
            sys_log_print_byte(msg[i]);
            i++;
        }
    }
}

void sys_log_new_line()
{
    if (sys_log_current_level >= CONFIG_GLOBAL_LOG_LEVEL)
    {
        sys_log_reset_color();
        sys_log_print_msg("\n\r");
        sys_log_mutex_give();
    }
}

void sys_log_print_digit(uint8_t digit)
{
    if (sys_log_current_level >= CONFIG_GLOBAL_LOG_LEVEL)
    {
        if (digit < 0x0A)
        {
            sys_log_print_byte(digit + 0x30);    /* 0x30 = ascii 0 */
        }
        else if (digit <= 0x0F)
        {
            sys_log_print_byte(digit + 0x37);    /* 0x37 = ascii 7 */
        }
        else
        {
            sys_log_print_byte('N');
        }
    }
}

void sys_log_print_str(char *str)
{
    if (sys_log_current_level >= CONFIG_GLOBAL_LOG_LEVEL)
    {
        uint16_t i = 0;
        while(str[i] != '\0')
        {
            sys_log_print_byte(str[i]);
            i++;
        }
    }
}

void sys_log_print_uint(uint32_t uint)
{
    if (sys_log_current_level >= CONFIG_GLOBAL_LOG_LEVEL)
    {
        if (uint == 0)
        {
            sys_log_print_digit(0);
        }
        else
        {
            uint8_t uint_str[10];               /* 32-bits = decimal with 10 digits */

            uint8_t digits = log10(uint) + 1;

            uint8_t i = 0;
            for(i=0; i<digits; ++i, uint /= 10)
            {
                uint_str[i] = uint % 10;
            }

            uint8_t j = 0;
            for(j=i; j>0; j--)
            {
                sys_log_print_digit(uint_str[j-1]);
            }
        }
    }
}

void sys_log_print_int(int32_t sint)
{
    if (sys_log_current_level >= CONFIG_GLOBAL_LOG_LEVEL)
    {
        if (sint < 0)
        {
            sint = abs(sint);
            sys_log_print_msg("-");
        }

        sys_log_print_uint((uint32_t)sint);
    }
}

void sys_log_print_hex(uint32_t hex)
{
    if (sys_log_current_level >= CONFIG_GLOBAL_LOG_LEVEL)
    {
        sys_log_print_msg("0x");
        
        if (hex > 0x00FFFFFF)
        {
            sys_log_print_digit((uint8_t)(hex >> 28) & 0x0F);
            sys_log_print_digit((uint8_t)(hex >> 24) & 0x0F);
        }

        if (hex > 0x0000FFFF)
        {
            sys_log_print_digit((uint8_t)(hex >> 20) & 0x0F);
            sys_log_print_digit((uint8_t)(hex >> 16) & 0x0F);
        }

        if (hex > 0x000000FF)
        {
            sys_log_print_digit((uint8_t)(hex >> 12) & 0x0F);
            sys_log_print_digit((uint8_t)(hex >> 8) & 0x0F);
        }

        sys_log_print_digit((uint8_t)(hex >> 4) & 0x0F);
        sys_log_print_digit((uint8_t)(hex & 0x0F));
    }
}

void sys_log_dump_hex(uint8_t *data, uint16_t len)
{
    if (sys_log_current_level >= CONFIG_GLOBAL_LOG_LEVEL)
    {
        uint16_t i = 0;
        for(i=0; i<len; i++)
        {
            sys_log_print_hex(data[i]);

            if (i < len-1)
            {
                sys_log_print_msg(", ");
            }
        }
    }
}

void sys_log_print_float(float flt, uint8_t digits)
{
    if (sys_log_current_level >= CONFIG_GLOBAL_LOG_LEVEL)
    {
        if (flt < 0)
        {
            sys_log_print_msg("-");

            flt = abs(flt);
        }

        /* Extract integer part */
        uint32_t ipart = (uint32_t)flt;

        /* Extract floating part */
        float fpart = flt - (float)ipart;

        /* Print integer part */
        sys_log_print_uint(ipart);

        /* Print decimal point */
        sys_log_print_msg(".");

        /* Print floating part */
        sys_log_print_uint((uint32_t)(fpart*pow(10, digits)));
    }
}

void sys_log_print_byte(uint8_t byte)
{
    if (sys_log_current_level >= CONFIG_GLOBAL_LOG_LEVEL)
    {
        sys_log_uart_write_byte(byte);
    }
}

void sys_log_print_system_time()
{
    sys_log_set_color(SYS_LOG_SYSTEM_TIME_COLOR);

    sys_log_print_msg("[ ");
    sys_log_print_uint(xTaskGetTickCount());    /* System time in milliseconds */
    sys_log_print_msg(" ]");

    sys_log_reset_color();
}

void sys_log_print_license_msg()
{
    sys_log_print_msg("EPS 2.0 Copyright (C) 2020, SpaceLab;");
    sys_log_new_line();
    sys_log_print_msg("This program comes with ABSOLUTELY NO WARRANTY.");
    sys_log_new_line();
    sys_log_print_msg("This is free software, and you are welcome to redistribute it");
    sys_log_new_line();
    sys_log_print_msg("under certain conditions.");
    sys_log_new_line();
    sys_log_new_line();
    sys_log_print_msg("Source code: https://github.com/spacelab-ufsc/eps2");
    sys_log_new_line();
    sys_log_print_msg("Documentation: https://github.com/spacelab-ufsc/eps2/tree/master/doc");
    sys_log_new_line();
}

void sys_log_print_splash_screen()
{
    sys_log_print_msg("                                                                   ");
    sys_log_new_line();
    sys_log_print_msg("                                                                   ");
    sys_log_new_line();
    sys_log_print_msg("...................................................................");
    sys_log_new_line();
    sys_log_print_msg("...................................................................");
    sys_log_new_line();
    sys_log_print_msg("..........                                               ..........");
    sys_log_new_line();
    sys_log_print_msg("..........  ____                       _          _      ..........");
    sys_log_new_line();
    sys_log_print_msg(".......... / ___| _ __   __ _  ___ ___| |    __ _| |__   ..........");
    sys_log_new_line();
    sys_log_print_msg(".......... \\___ \\| '_ \\ / _` |/ __/ _ \\ |   / _` | '_ \\  ..........");
    sys_log_new_line();
    sys_log_print_msg("..........  ___) | |_) | (_| | (_|  __/ |__| (_| | |_) | ..........");
    sys_log_new_line();
    sys_log_print_msg(".......... |____/| .__/ \\__,_|\\___\\___|_____\\__,_|_.__/  ..........");
    sys_log_new_line();
    sys_log_print_msg("..........       |_|                                     ..........");
    sys_log_new_line();
    sys_log_print_msg("..........                                               ..........");
    sys_log_new_line();
    sys_log_print_msg("..........        _____ ____  ____    ____    ___        ..........");
    sys_log_new_line();
    sys_log_print_msg("..........       | ____|  _ \\/ ___|  |___ \\  / _ \\       ..........");
    sys_log_new_line();
    sys_log_print_msg("..........       |  _| | |_) \\___ \\    __) || | | |      ..........");
    sys_log_new_line();
    sys_log_print_msg("..........       | |___|  __/ ___) |  / __/ | |_| |      ..........");
    sys_log_new_line();
    sys_log_print_msg("..........       |_____|_|   |____/  |_____(_)___/       ..........");
    sys_log_new_line();
    sys_log_print_msg("..........                                               ..........");
    sys_log_new_line();
    sys_log_print_msg("..........                                               ..........");
    sys_log_new_line();
    sys_log_print_msg("...................................................................");
    sys_log_new_line();
    sys_log_print_msg("...................................................................");
    sys_log_new_line();
    sys_log_print_msg("                                                                   ");
    sys_log_new_line();
    sys_log_print_msg("                                                                   ");
    sys_log_new_line();
}

void sys_log_print_firmware_version()
{
    sys_log_print_msg("[ ");
    sys_log_print_msg(FIRMWARE_VERSION);
    sys_log_print_msg(" ]");
}

/** \} End of sys_log group */
