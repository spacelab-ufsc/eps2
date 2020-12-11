/*
 * wdt.h
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
 * \brief Internal watchdog timer driver definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 2020/10/24
 * 
 * \defgroup wdt WDT
 * \ingroup drivers
 * \{
 */

#ifndef WDT_H_
#define WDT_H_

#include <stdint.h>

#include <hal/wdt_a.h>

#define WDT_MODULE_NAME             "WDT"

/* Clock sources */
#define WDT_CLK_SRC_SMCLK           WDT_A_CLOCKSOURCE_SMCLK         /* SMCLK as clock source */
#define WDT_CLK_SRC_ACLK            WDT_A_CLOCKSOURCE_ACLK          /* ACLK as clock source */
#define WDT_CLK_SRC_VLOCLK          WDT_A_CLOCKSOURCE_VLOCLK        /* VLOCLK as clock source */
#define WDT_CLK_SRC_XCLK            WDT_A_CLOCKSOURCE_XCLK          /* XCLK as clock source */

/* Clock divider values */
#define WDT_CLK_DIV_2G              WDT_A_CLOCKDIVIDER_2G           /* Divider = 2G */
#define WDT_CLK_DIV_128M            WDT_A_CLOCKDIVIDER_128M         /* Divider = 128M */
#define WDT_CLK_DIV_8192K           WDT_A_CLOCKDIVIDER_8192K        /* Divider = 8192K */
#define WDT_CLK_DIV_512K            WDT_A_CLOCKDIVIDER_512K         /* Divider = 512K */
#define WDT_CLK_DIV_32K             WDT_A_CLOCKDIVIDER_32K          /* Divider = 32K */
#define WDT_CLK_DIV_8192            WDT_A_CLOCKDIVIDER_8192         /* Divider = 8192 */
#define WDT_CLK_DIV_512             WDT_A_CLOCKDIVIDER_512          /* Divider = 512 */
#define WDT_CLK_DIV_64              WDT_A_CLOCKDIVIDER_64           /* Divider = 64 */

/**
 * \brief Watchdog timer configuration.
 */
typedef struct
{
    uint8_t clk_src;        /**< Clock source of the watchdog peripheral. */
    uint8_t clk_div;        /**< Clock divider. */
} wdt_config_t;

/**
 * \brief Internal watchdog initialization routine.
 *
 * This function configures the WDT peripheral of the MCU.
 *
 * \param[in] config is the configuration parameters of the watchdog timer peripheral.
 *
 * \return The status/error code.
 */
int wdt_init(wdt_config_t config);

/**
 * \brief Resets the watchdog timer counter.
 *
 * \return None.
 */
void wdt_reset();

#endif /* WDT_H_ */

/** \} End of wdt group */
