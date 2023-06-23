/*
 * read_sensors.c
 * 
 * Copyright The EPS 2.0 Contributors.
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
 * along with EPS 2.0. If not, see <http:/\/www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief Read external sensors task implementation.
 * 
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.35
 * 
 * \date 2021/04/23
 * 
 * \addtogroup read_sensors
 * \{
 */

#include <system/sys_log/sys_log.h>

#include <devices/current_sensor/current_sensor.h>
#include <devices/voltage_sensor/voltage_sensor.h>
#include <devices/temp_sensor/temp_sensor.h>
#include <devices/battery_monitor/battery_monitor.h>

#include <structs/eps2_data.h>

#include "read_sensors.h"
#include "startup.h"

xTaskHandle xTaskReadSensorsHandle;

void vTaskReadSensors(void)
{
    /* Wait startup task to finish */
    xEventGroupWaitBits(task_startup_status, TASK_STARTUP_DONE, pdFALSE, pdTRUE, pdMS_TO_TICKS(TASK_READ_SENSORS_INIT_TIMEOUT_MS));

    while(1)
    {
        TickType_t last_cycle = xTaskGetTickCount();

        uint16_t buf = 0U;

        /* -Y Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_MINUS_Y_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MY_CURRENT, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "SP -Y current: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* +X Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_PLUS_X_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_PX_CURRENT, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "SP +X current: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* -X Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_MINUS_X_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MX_CURRENT, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "SP -X current: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* +Z Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_PLUS_Z_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_PZ_CURRENT, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "SP +Z current: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* -Z Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_MINUS_Z_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MZ_CURRENT, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "SP -Z current: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* +Y Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_PLUS_Y_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_PY_CURRENT, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "SP +Y current: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* -Y and +X Solar Panels voltage in mV.*/
        if (voltage_sensor_read(PANNELS_MINUS_Y_PLUS_X_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MY_PX_VOLTAGE, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "SP -Y|+X voltage: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* -X and +Z Solar Panels voltage in mV.*/
        if (voltage_sensor_read(PANNELS_MINUS_X_PLUS_Z_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MX_PZ_VOLTAGE, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "SP -X|+Z voltage: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* -Z and +Y Solar Panels voltage in mV.*/
        if (voltage_sensor_read(PANNELS_MINUS_Z_PLUS_Y_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MZ_PY_VOLTAGE, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "SP -Z|+Y voltage: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* Total solar panels output voltage after MPPT in mV.*/
        if (voltage_sensor_read(TOTAL_SOLAR_PANNELS_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_VOLTAGE_MPPT, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "SP total voltage: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* Main power bus voltage in mV.*/
        if (voltage_sensor_read(MAIN_POWER_BUS_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_MAIN_POWER_BUS_VOLTAGE, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "Main Bus voltage: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* EPS and TTC circuitry current in mA.*/
        if (current_sensor_read(EPS_BEACON_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_EPS_CURRENT, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "EPS/Beacon current: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* RTD 0 temperature. */
        if (temp_rtd_read_k(TEMP_SENSOR_RTD_CH_0, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_RTD_0_TEMP, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "RTD 0 temp: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* RTD 1 temperature. */
        if (temp_rtd_read_k(TEMP_SENSOR_RTD_CH_1, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_RTD_1_TEMP, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "RTD 1 temp: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* RTD 2 temperature. */
        if (temp_rtd_read_k(TEMP_SENSOR_RTD_CH_2, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_RTD_2_TEMP, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "RTD 2 temp: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* RTD 3 temperature. */
        if (temp_rtd_read_k(TEMP_SENSOR_RTD_CH_3, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_RTD_3_TEMP, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "RTD 3 temp: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* RTD 4 temperature. */
        if (temp_rtd_read_k(TEMP_SENSOR_RTD_CH_4, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_RTD_4_TEMP, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "RTD 4 temp: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* RTD 5 temperature. */
        if (temp_rtd_read_k(TEMP_SENSOR_RTD_CH_5, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_RTD_5_TEMP, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "RTD 5 temp: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* RTD 6 temperature. */
        if (temp_rtd_read_k(TEMP_SENSOR_RTD_CH_6, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_RTD_6_TEMP, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "RTD 6 temp: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* Battery monitor voltage.*/
        if (bm_get_voltage(&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_VOLTAGE, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "Bat monitor voltage: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* Battery monitor CI temperature.*/
        if (bm_get_temperature_kelvin(&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_MONITOR_TEMP, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "Bat monitor temp: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* Battery monitor current.*/
        if (bm_get_instantaneous_current((int16_t*)&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_CURRENT, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "Bat monitor current: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* Battery monitor average current.*/
        if (bm_get_average_current((int16_t*)&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_AVERAGE_CURRENT, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "Bat monitor avg current");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* Battery monitor status register.*/
        if (bm_get_status_register_data((uint8_t*)&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_MONITOR_STATUS, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "Bat monitor status reg:");
                sys_log_print_hex(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* Battery monitor protection register.*/
        if (bm_get_protection_register_data((uint8_t*)&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_MONITOR_PROTECT, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "Bat monitor protection reg: ");
                sys_log_print_hex(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* Battery monitor RAAC */
        if (bm_get_raac_mah(&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_MONITOR_RAAC, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "Bat monitor RAAC: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        /* Battery monitor RSAC */
        vTaskDelay(pdMS_TO_TICKS(50));

        if (bm_get_rsac_mah(&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_MONITOR_RSAC, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "Bat monitor RSAC: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        /* Battery monitor RARC */
        vTaskDelay(pdMS_TO_TICKS(50));

        if (bm_get_rarc_percent((uint8_t*)&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_MONITOR_RARC, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "Bat monitor RARC: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        vTaskDelay(pdMS_TO_TICKS(50));

        /* Battery monitor RSRC */
        if (bm_get_rsrc_percent((uint8_t*)&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_MONITOR_RSRC, (uint32_t*)&buf);
            #if defined (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED) && (CONFIG_TASK_READ_SENSORS_DEBUG_ENABLED == 1)
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_READ_SENSORS_NAME, "Bat monitor RSRC: ");
                sys_log_print_uint(buf);
                sys_log_new_line();
            #endif
        }

        /* Data timestamp */
        uint32_t time_counter = (uint32_t)xTaskGetTickCount();

        eps_buffer_write(EPS2_PARAM_ID_TIME_COUNTER, &time_counter);

        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_READ_SENSORS_PERIOD_MS));
    }
}

/** \} End of read_sensors group */
