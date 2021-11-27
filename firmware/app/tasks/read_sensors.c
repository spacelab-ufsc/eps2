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
            eps_buffer_write(EPS2_PARAM_ID_SP_MY_CURRENT, (uint32_t *)&buf);
        }

        /* +X Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_PLUS_X_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_PX_CURRENT, (uint32_t *)&buf);
        }

        /* -X Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_MINUS_X_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MX_CURRENT, (uint32_t *)&buf);
        }
        
        /* +Z Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_PLUS_Z_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_PZ_CURRENT, (uint32_t *)&buf);
        }

        /* -Z Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_MINUS_Z_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MZ_CURRENT, (uint32_t *)&buf);
        }

        /* +Y Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_PLUS_Y_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_PY_CURRENT, (uint32_t *)&buf);
        }
        
        /* -Y and +X Solar Panels voltage in mV.*/
        if (voltage_sensor_read(PANNELS_MINUS_Y_PLUS_X_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MY_PX_VOLTAGE, (uint32_t *)&buf);
        }
        
        /* -X and +Z Solar Panels voltage in mV.*/
        if (voltage_sensor_read(PANNELS_MINUS_X_PLUS_Z_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MX_PZ_VOLTAGE, (uint32_t *)&buf);
        }

        /* -Z and +Y Solar Panels voltage in mV.*/
        if (voltage_sensor_read(PANNELS_MINUS_Z_PLUS_Y_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MZ_PY_VOLTAGE, (uint32_t *)&buf);
        }

        /* Total solar panels output voltage after MPPT in mV.*/
        if (voltage_sensor_read(TOTAL_SOLAR_PANNELS_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_VOLTAGE_MPPT, (uint32_t *)&buf);
        }
        
        /* Main power bus voltage in mV.*/
        if (voltage_sensor_read(MAIN_POWER_BUS_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_MAIN_POWER_BUS_VOLTAGE, (uint32_t *)&buf);
        }

        /* EPS and TTC circuitry current in mA.*/
        if (current_sensor_read(EPS_BEACON_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_EPS_CURRENT, (uint32_t *)&buf);
        }

        vTaskDelay(pdMS_TO_TICKS(5));

        /* RTD 0 temperature. */
        if (temp_rtd_read_k(TEMP_SENSOR_RTD_CH_0, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_RTD_0_TEMP, (uint32_t *)&buf);
        }

        /* RTD 1 temperature. */
        if (temp_rtd_read_k(TEMP_SENSOR_RTD_CH_1, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_RTD_1_TEMP, (uint32_t *)&buf);
        }

        /* RTD 2 temperature. */
        if (temp_rtd_read_k(TEMP_SENSOR_RTD_CH_2, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_RTD_2_TEMP, (uint32_t *)&buf);
        }

        /* RTD 3 temperature. */
        if (temp_rtd_read_k(TEMP_SENSOR_RTD_CH_3, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_RTD_3_TEMP, (uint32_t *)&buf);
        }

        /* RTD 4 temperature. */
        if (temp_rtd_read_k(TEMP_SENSOR_RTD_CH_4, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_RTD_4_TEMP, (uint32_t *)&buf);
        }

        /* RTD 5 temperature. */
        if (temp_rtd_read_k(TEMP_SENSOR_RTD_CH_5, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_RTD_5_TEMP, (uint32_t *)&buf);
        }

        /* RTD 6 temperature. */
        if (temp_rtd_read_k(TEMP_SENSOR_RTD_CH_6, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_RTD_6_TEMP, (uint32_t *)&buf);
        }

        vTaskDelay(pdMS_TO_TICKS(5));

        /* Battery monitor voltage.*/
        if (bm_get_voltage(&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_VOLTAGE, (uint32_t *)&buf);
        }

        /* Battery monitor CI temperature.*/
        if (bm_get_temperature_kelvin(&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_MONITOR_TEMP, (uint32_t *)&buf);
        }

        /* Battery monitor current.*/
        if (bm_get_instantaneous_current((int16_t *)&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_CURRENT, (uint32_t *)&buf);
        }

        /* Battery monitor average current.*/
        if (bm_get_average_current((int16_t *)&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_AVERAGE_CURRENT, (uint32_t *)&buf);
        }

        /* Battery monitor status register.*/
        if (bm_get_status_register_data((uint8_t *)&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_MONITOR_STATUS, (uint32_t *)&buf);
        }

        /* Battery monitor protection register.*/
        if (bm_get_protection_register_data((uint8_t *)&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_MONITOR_PROTECT, (uint32_t *)&buf);
        }

        if (bm_get_raac_mah(&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_MONITOR_RAAC, (uint32_t *)&buf);
        }

        if (bm_get_rsac_mah(&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_MONITOR_RSAC, (uint32_t *)&buf);
        }

        if (bm_get_rarc_percent((uint8_t *)&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_MONITOR_RARC, (uint32_t *)&buf);
        }

        if (bm_get_rsrc_percent((uint8_t *)&buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_BAT_MONITOR_RSRC, (uint32_t *)&buf);
        }

        /* Data timestamp */
        uint32_t time_counter = (uint32_t)xTaskGetTickCount();
        eps_buffer_write(EPS2_PARAM_ID_TIME_COUNTER, &time_counter);

        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_READ_SENSORS_PERIOD_MS));
    }
}

/** \} End of read_sensors group */
