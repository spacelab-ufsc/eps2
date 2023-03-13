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
 * \version 0.2.25
 * 
 * \date 2021/03/09
 * 
 * \addtogroup startup
 * \{
 */

#include <stdbool.h>

#include <config/config.h>
#include <app/structs/eps2_data.h>
#include <system/system.h>
#include <system/sys_log/sys_log.h>
#include <system/clocks.h>
#include <devices/leds/leds.h>
#include <devices/bat_manager/bat_manager.h>
#include <devices/battery_monitor/battery_monitor.h>
#include <devices/current_sensor/current_sensor.h>
#include <devices/voltage_sensor/voltage_sensor.h>
#include <devices/temp_sensor/temp_sensor.h>
#include <devices/media/media.h>
#include <devices/mppt/mppt.h>
// #include <devices/heater/heater.h>
#include <devices/heater/heater_on_off.h>
#include <devices/watchdog/watchdog.h>
#include <devices/obdh/obdh.h>
#include <devices/ttc/ttc.h>

#include "startup.h"

xTaskHandle xTaskStartupHandle;

EventGroupHandle_t task_startup_status;

void vTaskStartup(void *pvParameters)
{
    unsigned int error_counter = 0;

    /* Logger device initialization */
    sys_log_init();

    /* Print the FreeRTOS version */
    sys_log_print_event_from_module(SYS_LOG_INFO, TASK_STARTUP_NAME, "FreeRTOS ");
    sys_log_print_msg(tskKERNEL_VERSION_NUMBER);
    sys_log_new_line();

    /* Print the hardware version */
    sys_log_print_event_from_module(SYS_LOG_INFO, TASK_STARTUP_NAME, "Hardware revision is ");
    uint32_t hw_version = system_get_hw_version();
    sys_log_print_uint(hw_version);
    sys_log_new_line();
    eps_buffer_write(EPS2_PARAM_ID_HW_VERSION, (uint32_t*)&hw_version);

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
    uint32_t reset_cause = system_get_reset_cause();
    sys_log_print_hex(reset_cause);
    sys_log_new_line();
    eps_buffer_write(EPS2_PARAM_ID_LAST_RESET_CAUSE, (uint32_t*)&reset_cause);

#if CONFIG_DEV_LEDS_ENABLED == 1
    /* LEDs device initialization */
    if (leds_init() != 0)
    {
        error_counter++;
    }
#endif /* CONFIG_DEV_LEDS_ENABLED */

#if CONFIG_DEV_HEATER_ENABLED == 1
    /* Heater device initialization */
    if (heater_on_off_init() != 0)
    {
        error_counter++;
    }
#endif /* CONFIG_DEV_HEATER_ENABLED */

#if CONFIG_DEV_MPPT_ENABLED == 1
    /* MPPT device initialization */
    if (mppt_init() != 0)
    {
        error_counter++;
    }
#endif /* CONFIG_DEV_MPPT_ENABLED */

#if CONFIG_DEV_BAT_MANAGER_ENABLED == 1
    /* Battery manager device initialization */
    if (bat_manager_init() != 0)
    {
        error_counter++;
    }
#endif /* CONFIG_DEV_BAT_MANAGER_ENABLED */

#if CONFIG_DEV_BATTERY_MONITOR_ENABLED == 1
    /* Battery monitor device initialization */
    if (battery_monitor_init() != 0)
    {
        error_counter++;
    }
#endif /* CONFIG_DEV_BATTERY_MONITOR_ENABLED */

#if CONFIG_DEV_MEDIA_ENABLED == 1
    /* Internal non-volatile memory initialization */
    if (media_init() != 0)
    {
        error_counter++;
    }
#endif /* CONFIG_DEV_MEDIA_ENABLED */

#if CONFIG_DEV_CURRENT_SENSOR_ENABLED == 1
    /* Current sensor device initialization */
    if (current_sensor_init() != 0)
    {
        error_counter++;
    }
#endif /* CONFIG_DEV_CURRENT_SENSOR_ENABLED */

#if CONFIG_DEV_VOLTAGE_SENSOR_ENABLED == 1
    /* Voltage sensor device initialization */
    if (voltage_sensor_init() != 0)
    {
        error_counter++;
    }
#endif /* CONFIG_DEV_VOLTAGE_SENSOR_ENABLED */

#if CONFIG_DEV_TEMP_SENSOR_ENABLED == 1
    /* Temperature sensor device initialization */
    if (temp_sensor_init() != 0)
    {
        error_counter++;
    }
#endif /* CONFIG_DEV_TEMP_SENSOR_ENABLED */

#if CONFIG_DEV_OBDH_ENABLED == 1
    /* OBDH device initialization */
    if (obdh_init() != 0)
    {
        error_counter++;
    }
#endif /* CONFIG_DEV_OBDH_ENABLED */

#if CONFIG_DEV_TTC_ENABLED == 1
    /* TTC device initialization */
    if (ttc_init() != 0)
    {
        error_counter++;
    }
#endif /* CONFIG_DEV_TTC_ENABLED */

    if (error_counter > 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_STARTUP_NAME, "Boot completed with ");
        sys_log_print_uint(error_counter);
        sys_log_print_msg(" ERROR(S)!");
        sys_log_new_line();

        led_set(LED_FAULT);
    }
    else
    {
        sys_log_print_event_from_module(SYS_LOG_INFO, TASK_STARTUP_NAME, "Boot completed with SUCCESS!");
        sys_log_new_line();

        led_clear(LED_FAULT);
    }

    /* Startup task status = Done */
    xEventGroupSetBits(task_startup_status, TASK_STARTUP_DONE);

    vTaskSuspend(xTaskStartupHandle);
}

/** \} End of startup group */
