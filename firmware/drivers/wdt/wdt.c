/*
 * wdt.c
 * 
 * Copyright (C) 2019, SpaceLab.
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
 * \brief Internal watchdog timer driver implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 2020/10/24
 * 
 * \addtogroup wdt
 * \{
 */

#include <hal/wdt_a.h>

#include <config/config.h>
#include <system/sys_log/sys_log.h>

#include "wdt.h"

int wdt_init(wdt_config_t config)
{
    /* Checking clock source value */
    switch(config.clk_src)
    {
        case WDT_CLK_SRC_SMCLK:       break;
        case WDT_CLK_SRC_ACLK:        break;
        case WDT_CLK_SRC_VLOCLK:      break;
        case WDT_CLK_SRC_XCLK:        break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, WDT_MODULE_NAME, "Error during initialization: Invalid clock source!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;      /* Invalid clock source */
    }

    /* Checking clock divider value */
    switch(config.clk_div)
    {
        case WDT_CLK_DIV_2G:         break;
        case WDT_CLK_DIV_128M:       break;
        case WDT_CLK_DIV_8192K:      break;
        case WDT_CLK_DIV_512K:       break;
        case WDT_CLK_DIV_32K:        break;
        case WDT_CLK_DIV_8192:       break;
        case WDT_CLK_DIV_512:        break;
        case WDT_CLK_DIV_64:         break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, WDT_MODULE_NAME, "Error during initialization: Invalid clock divider!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;      /* Invalid clock divider value */
    }

    /* Watchdog initialization */
    WDT_A_initWatchdogTimer(WDT_A_BASE, config.clk_src, config.clk_div);

    /* Start counter */
    WDT_A_start(WDT_A_BASE);

    return 0;
}

void wdt_reset()
{
    WDT_A_resetTimer(WDT_A_BASE);
}

/** \} End of wdt group */
