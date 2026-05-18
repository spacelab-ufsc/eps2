/*
 * gpio_wrap.h
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
 * \brief GPIO driver wrap definition.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 2021/07/22
 *
 * \defgroup gpio_wrap GPIO Wrap
 * \ingroup tests
 * \{
 */

#ifndef GPIO_WRAP_H_
#define GPIO_WRAP_H_

#include <stdbool.h>

#include <drivers/gpio/gpio.h>

/**
 * \brief Mockup of the GPIO initialization function implemented as an wrap function.
 *
 * \param[in] pin is the GPIO pin to initialize.
 *
 * \param[in] config is the configuration to initialize the GPIO pin.
 *
 * \return The status/error code.
 */
int __wrap_gpio_init(gpio_pin_t pin, gpio_config_t config);

/**
 * \brief Mockup of the GPIO set state function implemented as an wrap function.
 *
 * \param[in] pin is the GPIO pin to set the state.
 *
 * \param[in] level is the new state of the given GPIO pin. It can be:
 * \parblock
 *      - GPIO_STATE_HIGH
 *      - GPIO_STATE_LOW
 *      .
 * \endparblock
 *
 * \return The status/error code.
 */
int __wrap_gpio_set_state(gpio_pin_t pin, bool level);

/**
 * \brief Mockup of the GPIO get state funcion implemented as an wrap function.
 *
 * \param[in] pin is the the GPIO pin to get the state.
 *
 * \return The GPIO pin state. It can be:
 * \parblock
 *      - GPIO_STATE_HIGH
 *      - GPIO_STATE_LOW
 *      - -1 on error
 *      .
 * \endparblock
 *
 * \return The status/error code.
 */
int __wrap_gpio_get_state(gpio_pin_t pin);

/**
 * \brief Mockup of the GPIO toggle function implemented as an wrap function.
 *
 * \param[in] pin is the the GPIO pin to get the state.
 *
 * \return The status/error code.
 */
int __wrap_gpio_toggle(gpio_pin_t pin);

#endif /* GPIO_WRAP_H_ */

/** \} End of gpio_wrap group */
