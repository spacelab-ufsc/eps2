/*
 * read_sensors.c
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
 * \brief Read external sensors task implementation.
 * 
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * 
 * \version 0.2.5
 * 
 * \date 2021/04/23
 * 
 * \addtogroup read_sensors
 * \{
 */

#include <devices/current_sensor/current_sensor.h>
#include <devices/voltage_sensor/voltage_sensor.h>
#include <devices/temp_sensor/temp_sensor.h>

#include <structs/eps2_data.h>

#include "read_sensors.h"
#include "startup.h"

xTaskHandle xTaskReadSensorsHandle;

void vTaskReadSensors(void *pvParameters)
{
    /* Wait startup task to finish */
    xEventGroupWaitBits(task_startup_status, TASK_STARTUP_DONE, pdFALSE, pdTRUE, pdMS_TO_TICKS(TASK_READ_SENSORS_INIT_TIMEOUT_MS));

    while(1)
    {
        TickType_t last_cycle = xTaskGetTickCount();

        uint16_t buf = 0;

        /* -Y Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_MINUS_Y_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MY_CURRENT, &buf);
        }

        /* +X Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_PLUS_X_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_PX_CURRENT, &buf);
        }

        /* -X Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_MINUS_X_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MX_CURRENT, &buf);
        }
        
        /* +Z Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_PLUS_Z_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_PZ_CURRENT, &buf);
        }

        /* -Z Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_MINUS_Z_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MZ_CURRENT, &buf);
        }

        /* +Y Solar Panel current in mA.*/
        if (current_sensor_read(PANNEL_PLUS_Y_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_PY_CURRENT, &buf);
        }
        
        /* -Y and +X Solar Panels voltage in mV.*/
        if (voltage_sensor_read(PANNELS_MINUS_Y_PLUS_X_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MY_PX_VOLTAGE, &buf);
        }
        
        /* -Z and +Y Solar Panels voltage in mV.*/
        if (voltage_sensor_read(PANNELS_MINUS_X_PLUS_Z_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MX_PZ_VOLTAGE, &buf);
        }

        /* -Y and +X Solar Panels voltage in mV.*/
        if (voltage_sensor_read(PANNELS_MINUS_Z_PLUS_Y_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_MZ_PY_VOLTAGE, &buf);
        }

        /* Total solar panels output voltage after MPPT in mV.*/
        if (voltage_sensor_read(TOTAL_SOLAR_PANNELS_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_SP_VOLTAGE_MPPT, &buf);
        }
        
        /* Main power bus voltage in mV.*/
        if (voltage_sensor_read(MAIN_POWER_BUS_VOLTAGE_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_MAIN_POWER_BUS_VOLTAGE, &buf);
        }

        /* EPS and TTC circuitry current in mA.*/
        if (current_sensor_read(EPS_BEACON_CURRENT_SENSOR_ADC_PORT, &buf) == 0)
        {
            eps_buffer_write(EPS2_PARAM_ID_EPS_CURRENT, &buf);
        }

        /* Data timestamp */
        eps_buffer_write(EPS2_PARAM_ID_TIME_COUNTER, (uint32_t)xTaskGetTickCount());

        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_READ_SENSORS_PERIOD_MS));
    }
}

/** \} End of read_sensors group */
