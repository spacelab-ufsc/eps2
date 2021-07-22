/*
 * gpio_wrap.c
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
 * \brief GPIO driver wrap implementation.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 2021/07/22
 *
 * \addtogroup gpio_wrap
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include "gpio_wrap.h"

int __wrap_gpio_init(gpio_pin_t pin, gpio_config_t config)
{
    check_expected(pin);

    return 0;
}

int __wrap_gpio_set_state(gpio_pin_t pin, bool level)
{
    check_expected(pin);
    check_expected(level);

    return 0;
}

int __wrap_gpio_get_state(gpio_pin_t pin)
{
    check_expected(pin);

    int pin_val = mock_type(int);

    if ((pin_val == 0) || (pin_val == 1))
    {
        return pin_val;
    }
    else
    {
        return -1;
    }
}

int __wrap_gpio_toggle(gpio_pin_t pin)
{
    check_expected(pin);

    return 0;
}

/** \} End of gpio_wrap group */
