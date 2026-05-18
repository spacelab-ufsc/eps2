/*
 * leds.h
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
 * \brief System LEDs definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 2020/10/26
 * 
 * \defgroup leds LEDs
 * \ingroup devices
 * \{
 */

#ifndef LEDS_H_
#define LEDS_H_

#include <stdint.h>

#define LEDS_MODULE_NAME        "LEDs"

/* LEDs types */
#define LED_SYSTEM              0       /**< System LED. */
#define LED_FAULT               1       /**< Fault LED. */

/**
 * \brief LED type.
 */
typedef uint8_t led_t;

/**
 * \brief Initialization routine of the LEDs.
 *
 * \return The status/error code.
 */
int leds_init();

/**
 * \brief Sets a given LED.
 *
 * \param[in] l is the LED to set.
 *
 * \return The status/error code.
 */
int led_set(led_t l);

/**
 * \brief Clears a given LED.
 *
 * \param[in] l is the LED to clear.
 *
 * \return The status/error code.
 */
int led_clear(led_t l);

/**
 * \brief Toggles a given LED.
 *
 * \param[in] l is the LED to toggle.
 *
 * \return The status/error code.
 */
int led_toggle(led_t l);

#endif /* LEDS_H_ */

/** \} End of leds group */
