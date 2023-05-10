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
 * \version 0.2.13
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

#define WDT_MODULE_NAME             "WDT"

/* Clock sources */
typedef enum
{
    WDT_CLK_SRC_SMCLK=0,    /**< SMCLK as clock source. */
    WDT_CLK_SRC_ACLK,       /**< ACLK as clock source. */
    WDT_CLK_SRC_VLOCLK,     /**< VLOCLK as clock source. */
    WDT_CLK_SRC_XCLK        /**< XCLK as clock source. */
} wdt_clk_src_e;

/* Clock divider values */
typedef enum
{
    WDT_CLK_DIV_2G=0,       /**< Divider = 2G. */
    WDT_CLK_DIV_128M,       /**< Divider = 128M. */
    WDT_CLK_DIV_8192K,      /**< Divider = 8192K. */
    WDT_CLK_DIV_512K,       /**< Divider = 512K. */
    WDT_CLK_DIV_32K,        /**< Divider = 32K. */
    WDT_CLK_DIV_8192,       /**< Divider = 8192. */
    WDT_CLK_DIV_512,        /**< Divider = 512. */
    WDT_CLK_DIV_64          /**< Divider = 64. */
} wdt_clk_div_e;

/**
 * \brief Watchdog timer configuration.
 */
typedef struct
{
    wdt_clk_src_e clk_src;        /**< Clock source of the watchdog peripheral. */
    wdt_clk_div_e clk_div;        /**< Clock divider. */
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
void wdt_reset(void);

#endif /* WDT_H_ */

/** \} End of wdt group */
