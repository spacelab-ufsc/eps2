/*
 * watchdog.c
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
 * \brief Watchdog device implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 2020/10/26
 * 
 * \addtogroup watchdog
 * \{
 */

#include <drivers/wdt/wdt.h>

#include "watchdog.h"

int watchdog_init()
{
    wdt_config_t int_wdt;

    int_wdt.clk_src = WDT_CLK_SRC_ACLK;
    int_wdt.clk_div = WDT_CLK_DIV_32K;

    return wdt_init(int_wdt);
}

void watchdog_reset()
{
    wdt_reset();
}

/** \} End of watchdog group */
