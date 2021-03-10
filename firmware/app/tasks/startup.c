/*
 * startup.c
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
 * \brief Startup task implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 2021/03/09
 * 
 * \addtogroup startup
 * \{
 */

#include <stdbool.h>

#include <config/config.h>
#include <system/sys_log/sys_log.h>
#include <system/clocks.h>
#include <devices/leds/leds.h>
#include <devices/bat_manager/bat_manager.h>
#include <devices/current_sensor/current_sensor.h>
#include <devices/voltage_sensor/voltage_sensor.h>
#include <devices/temp_sensor/temp_sensor.h>
#include <devices/media/media.h>
#include <devices/mppt/mppt.h>
#include <devices/watchdog/watchdog.h>

#include "startup.h"

xTaskHandle xTaskStartupHandle;

void vTaskStartup(void *pvParameters)
{
    bool error = false;

    /* Logger device initialization */
    sys_log_init();

    /* Print the FreeRTOS version */
    sys_log_print_event_from_module(SYS_LOG_INFO, TASK_STARTUP_NAME, "FreeRTOS ");
    sys_log_print_msg(tskKERNEL_VERSION_NUMBER);
    sys_log_new_line();

    /* Print the hardware version */
    sys_log_print_event_from_module(SYS_LOG_INFO, TASK_STARTUP_NAME, "Hardware revision is ");
    sys_log_print_uint(system_get_hw_version());
    sys_log_new_line();

    /* Print the system clocks */
    clocks_config_t clks = clocks_read();
    sys_log_print_event_from_module(SYS_LOG_INFO, TASK_STARTUP_NAME, "System clocks: MCLK=");
    sys_log_print_uint(clks.mclk_hz);
    sys_log_print_msg(" Hz, SMCLK=");
    sys_log_print_uint(clks.smclk_hz);
    sys_log_print_msg(" Hz, ACLK=");
    sys_log_print_uint(clks.aclk_hz);
    sys_log_print_msg(" Hz");
    sys_log_new_line();

    /* Print last reset cause (code) */
    sys_log_print_event_from_module(SYS_LOG_INFO, TASK_STARTUP_NAME, "Last reset cause: ");
    sys_log_print_hex(system_get_reset_cause());
    sys_log_new_line();

    /* Battery manager device initialization */
    if (bat_manager_init() != 0)
    {
        error = true;
    }
    
    /* LEDs device initialization */
    if (leds_init() != 0)
    {
        error = true;
    }

    /* Current sensor device initialization */
    if (current_sensor_init() != 0)
    {
        error = true;
    }

    /* Voltage sensor device initialization */
    if (voltage_sensor_init() != 0)
    {
        error = true;
    }

    /* Temperature sensor device initialization */
    if (temp_sensor_init() != 0)
    {
        error = true;
    }

    /* Internal non-volatile memory initialization */
    if (media_init() != 0)
    {
        error = true;
    }

    /* MPPT device initialization */
    if (mppt_init() != 0)
    {
        error = true;
    }

    /* Watchdog device initialization */
    if (watchdog_init() != 0)
    {
        error = true;
    }

    if (error)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_STARTUP_NAME, "Boot completed with ERRORS!");
        sys_log_new_line();

        /* led_set(LED_FAULT); No led fault on EPS2 version 0.1*/
    }
    else
    {
        sys_log_print_event_from_module(SYS_LOG_INFO, TASK_STARTUP_NAME, "Boot completed with SUCCESS!");
        sys_log_new_line();

        /* led_clear(LED_FAULT); No led fault on EPS2 version 0.1 */
    }

    vTaskSuspend(xTaskStartupHandle);
}

/** \} End of startup group */
