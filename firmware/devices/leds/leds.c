/*
 * leds.c
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
 * \brief System LEDs implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 2020/10/26
 * 
 * \addtogroup leds
 * \{
 */

#include <system/sys_log/sys_log.h>
#include <drivers/gpio/gpio.h>

#include "leds.h"

int leds_init()
{
    sys_log_print_event_from_module(SYS_LOG_INFO, LEDS_MODULE_NAME, "Initializing system LEDs...");
    sys_log_new_line();

    gpio_config_t config_sys = {.mode = GPIO_MODE_OUTPUT};
    gpio_config_t config_fault = {.mode = GPIO_MODE_OUTPUT};

    if (gpio_init(GPIO_PIN_35, config_sys) == 0)
    {
        return gpio_init(GPIO_PIN_34, config_fault);
    }
    else
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, LEDS_MODULE_NAME, "Error initializing the system LEDs!");
        sys_log_new_line();

        return -1;
    }
}

int led_set(led_t l)
{
    switch(l)
    {
        case LED_SYSTEM:    return gpio_set_state(GPIO_PIN_35, true);
        case LED_FAULT:     return gpio_set_state(GPIO_PIN_34, true);
        default:            return -1;      /* Invalid LED */
    }
}

int led_clear(led_t l)
{
    switch(l)
    {
        case LED_SYSTEM:    return gpio_set_state(GPIO_PIN_35, false);
        case LED_FAULT:     return gpio_set_state(GPIO_PIN_34, false);
        default:            return -1;      /* Invalid LED */
    }
}

int led_toggle(led_t l)
{
    switch(l)
    {
        case LED_SYSTEM:    return gpio_toggle(GPIO_PIN_35);
        case LED_FAULT:     return gpio_toggle(GPIO_PIN_34);
        default:            return -1;      /* Invalid LED */
    }
}

/** \} End of leds group */
