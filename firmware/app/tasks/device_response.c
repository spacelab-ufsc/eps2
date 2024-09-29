/*
 * device_response.c
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
 * \brief Device response task implementation.
 *
 * \author João Cláudio Elsen Barcellos <joaoclaudiobarcellos@gmail.com>
 * \author Ramon de Araujo Borba <ramonborba97@gmail.com>
 *
 * \version 0.4.0
 *
 * \date 26/05/2021
 *
 * \addtogroup device_response
 * \{
 */

#include <system/sys_log/sys_log.h>
#include <structs/eps2_data.h>

#include <devices/ttc/ttc.h>

#include "device_response.h"
#include "startup.h"

xTaskHandle xTaskDeviceResponseHandle;

void vTaskDeviceResponse(void *pvParameters)
{
    /* Wait startup task to finish */
    xEventGroupWaitBits(task_startup_status, TASK_STARTUP_DONE, pdFALSE, pdTRUE, pdMS_TO_TICKS(TASK_DEVICE_RESPONSE_INIT_TIMEOUT_MS));

    /* Delay before the first cycle */
    vTaskDelay(pdMS_TO_TICKS(TASK_DEVICE_RESPONSE_INITIAL_DELAY_MS));

    uint8_t beacon_param_list[] = {
        BEACON_PARAM_ID_LIST,
    };
    const uint8_t BEACON_PARAM_LIST_SIZE = sizeof(beacon_param_list) / sizeof(*beacon_param_list);

    const uint8_t DEVICE_RESPONSE_BUFFER_SIZE = 9 + 4 * BEACON_PARAM_LIST_SIZE;
    uint8_t buf[DEVICE_RESPONSE_BUFFER_SIZE] = {0};
    uint32_t val = 0;
    uint8_t beacon_flag = 0;
    
    while(1)
    {
        TickType_t last_cycle = xTaskGetTickCount();

        buf[0] = DEVICE_COMMAND_WRITE;
        buf[1] = CONFIG_PKT_ID_BEACON;
        memcpy(&buf[2], CONFIG_SATELLITE_CALLSIGN, 7);
        
        eps_buffer_read(EPS2_PARAM_ID_BEACON_ENABLE, &beacon_flag);
        if(beacon_flag > 0)
        {
            for(uint8_t i = 0, j = 9; i < BEACON_PARAM_LIST_SIZE; i++, j+=4)
            {
                eps_buffer_read(beacon_param_list[i], &val);
                buf[ j ] = (val >> 24) & 0xFF;
                buf[j+1] = (val >> 16) & 0xFF;
                buf[j+2] = (val >> 8)  & 0xFF;
                buf[j+3] = (val >> 0)  & 0xFF;
            }
            ttc_answer_long(buf, DEVICE_RESPONSE_BUFFER_SIZE);
        }
        else
        {
            sys_log_print_event_from_module(SYS_LOG_INFO, TASK_DEVICE_RESPONSE_NAME, "The beacon is not enabled");
            sys_log_new_line();
        }

        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_DEVICE_RESPONSE_PERIOD_MS));
    }
}

/** \} End of device_response group */
