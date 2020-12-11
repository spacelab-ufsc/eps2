/*
 * system.c
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
 * \brief System management routines implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 2020/10/22
 * 
 * \addtogroup system
 * \{
 */

#include <msp430.h>
#include <drivers/gpio/gpio.h>

#include "system.h"

sys_time_t sys_time = 0;

void system_reset(void)
{
    PMMCTL0 = PMMPW | PMMSWBOR;     /* Triggers a software BOR */

    WDTCTL = 0xDEAD;                /* Reset system by writing to the WDT register without using the proper password */
}

uint8_t system_get_reset_cause(void)
{
    return (SYSRSTIV & 0xFF);
}

void system_set_time(sys_time_t tm)
{
    sys_time = tm;
}

void system_increment_time(void)
{
    sys_time++;
}

sys_time_t system_get_time(void)
{
    return sys_time;
}

sys_hw_version_t system_get_hw_version()
{
    gpio_pin_t bit_0_pin = GPIO_PIN_20;
    gpio_pin_t bit_1_pin = GPIO_PIN_21;

    /* Initializing bit 0 GPIO pin */
    if (gpio_init(bit_0_pin, (gpio_config_t){.mode=GPIO_MODE_INPUT}) != 0)
    {
        return HW_VERSION_UNKNOWN;
    }

    /* Initializing bit 1 GPIO pin */
    if (gpio_init(bit_1_pin, (gpio_config_t){.mode=GPIO_MODE_INPUT}) != 0)
    {
        return HW_VERSION_UNKNOWN;
    }

    int bit_0_state = gpio_get_state(bit_0_pin);
    int bit_1_state = gpio_get_state(bit_1_pin);

    if ((bit_0_state == -1) || (bit_1_state == -1))
    {
        return HW_VERSION_UNKNOWN;
    }

    return ((uint8_t)bit_1_state << 1) | (uint8_t)bit_0_state;
}

/** \} End of system group */
