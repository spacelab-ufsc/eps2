/*
 * leds.c
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
 * \brief System LEDs implementation.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.2.24
 *
 * \date 2021/05/28
 *
 * \addtogroup leds
 * \{
 */

#include <system/sys_log/sys_log.h>
#include <drivers/gpio/gpio.h>

#include "leds.h"

/* GPIO configuration */
#define LED_SYSTEM_PIN          GPIO_PIN_36
#define LED_FAULT_PIN           GPIO_PIN_35

int leds_init()
{
    sys_log_print_event_from_module(SYS_LOG_INFO, LEDS_MODULE_NAME, "Initializing system LEDs...");
    sys_log_new_line();

    gpio_config_t config_sys = {.mode = GPIO_MODE_OUTPUT};
    gpio_config_t config_fault = {.mode = GPIO_MODE_OUTPUT};

    if ((gpio_init(LED_SYSTEM_PIN, config_sys) != 0) ||
        (gpio_init(LED_FAULT_PIN, config_fault) != 0))
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, LEDS_MODULE_NAME, "Error initializing the system LEDs!");
        sys_log_new_line();

        return -1;
    }

    return 0;
}

int led_set(led_t l)
{
    switch(l)
    {
        case LED_SYSTEM:    return gpio_set_state(LED_SYSTEM_PIN, true);
        case LED_FAULT:     return gpio_set_state(LED_FAULT_PIN, true);
        default:            return -1;      /* Invalid LED */
    }
}

int led_clear(led_t l)
{
    switch(l)
    {
        case LED_SYSTEM:    return gpio_set_state(LED_SYSTEM_PIN, false);
        case LED_FAULT:     return gpio_set_state(LED_FAULT_PIN, false);
        default:            return -1;      /* Invalid LED */
    }
}

int led_toggle(led_t l)
{
    switch(l)
    {
        case LED_SYSTEM:    return gpio_toggle(LED_SYSTEM_PIN);
        case LED_FAULT:     return gpio_toggle(LED_FAULT_PIN);
        default:            return -1;      /* Invalid LED */
    }
}

/** \} End of leds group */
