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
 *
 * \version 0.1.6
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

    uint8_t buf[DEVICE_RESPONSE_BUFFER_SIZE] = {0};
    uint32_t val = 0;

    uint8_t pos;
    uint8_t pos2;

    /* Wait startup task to finish */
    xEventGroupWaitBits(task_startup_status, TASK_STARTUP_DONE, pdFALSE, pdTRUE, pdMS_TO_TICKS(TASK_DEVICE_RESPONSE_INIT_TIMEOUT_MS));

    /* Delay before the first cycle */
    vTaskDelay(pdMS_TO_TICKS(TASK_DEVICE_RESPONSE_INITIAL_DELAY_MS));

    while(1)
    {
        pos = 0;

        TickType_t last_cycle = xTaskGetTickCount();

        buf[0] = DEVICE_COMMAND_WRITE;

        /*

        for(int i = 0; i < EPS_DATA_STRUCTURE_SIZE; i++)
        {
            eps_buffer_read(i, &val);
            buf[i+1] = val;
        }*/

        for(int i = 0; i < EPS_DATA_STRUCTURE_SIZE; i++)
        {
            eps_buffer_read(i, &val);

            if (i == 0){

                buf[++pos] = (val>>24) & 0xFFFF;
                buf[++pos] = (val>>16) & 0xFFFF;
                buf[++pos] = (val>>8) & 0xFFFF;
                buf[++pos] = val & 0xFFFF;
            }

            if (i >= 1 && i <= 21){

                buf[++pos] = (val>>8) & 0xFFFF;
                buf[++pos] = val & 0xFFFF;
            }

            if (i >=22 && i <= 33){

                buf[++pos] = val;
            }
        }
        sys_log_new_line();

        sys_log_print_event_from_module(SYS_LOG_INFO, "EPS BUFFER", "HEX:");
        sys_log_new_line();

        for (int j = 0; j<pos; j++){
            sys_log_print_hex(buf[j]);
            sys_log_print_msg(", ");

        }
        sys_log_new_line();

        sys_log_print_event_from_module(SYS_LOG_INFO, "EPS BUFFER", "DADOS COMPLETOS:");
        sys_log_new_line();


        pos2 = 1;


        for(int i = 0; i < EPS_DATA_STRUCTURE_SIZE; i++)
                {

            eps_buffer_print(i);
            sys_log_print_msg(": ");

                    if ( i == 0){

                        uint32_t teste32 = ((uint32_t)buf[pos2] << 24) | ((uint32_t)buf[(pos2+1)] << 16) | ((uint32_t)buf[(pos2+2)] << 8) | ((uint32_t)buf[(pos2+3)]);
                        sys_log_print_uint(teste32);
                        sys_log_new_line();
                        pos2 = pos2 + 4;

                    }

                    if (i >= 1 && i <= 21){

                        if (i == 16 || i == 17){
                            int16_t teste16 = ((int16_t)buf[pos2] << 8) | (int16_t)buf[(pos2+1)];
                            sys_log_print_int(teste16);
                            sys_log_new_line();

                        }
                        else{
                            uint16_t teste16 = ((uint16_t)buf[pos2] << 8) | (uint16_t)buf[(pos2+1)];
                            sys_log_print_uint(teste16);
                            sys_log_new_line();

                        }

                        pos2 = pos2 + 2;



                    }

                    if (i >=22 && i <= 33){

                        uint8_t teste8 = buf[pos2];
                        sys_log_print_uint(teste8);
                        sys_log_new_line();
                        pos2 = pos2 + 1;
                    }
                }
                sys_log_new_line();
                /*
        uint16_t voltageteste = ((uint16_t)buf[65] << 8) | (uint16_t)buf[66];

        uint32_t tcountgeteste = ((uint32_t)buf[1] << 24) | ((uint32_t)buf[2] << 16) | ((uint32_t)buf[3] << 8) | (uint32_t)buf[4];

        sys_log_print_event_from_module(SYS_LOG_INFO, "VOLTAGEMS", " ");
        sys_log_print_uint(voltageteste);
        sys_log_new_line();

        sys_log_print_event_from_module(SYS_LOG_INFO, "TIMER COUNT", " ");
        sys_log_print_uint(tcountgeteste);
        sys_log_new_line();*/

        ttc_answer_long(buf, DEVICE_RESPONSE_BUFFER_SIZE);

        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_DEVICE_RESPONSE_PERIOD_MS));
    }
}

/** \} End of device_response group */
