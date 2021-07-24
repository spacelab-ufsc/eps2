/*
 * param_server.h
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
 * \brief Parameter server task implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.2
 * 
 * \date 2021/07/24
 * 
 * \addtogroup param_server
 * \{
 */

#include <system/sys_log/sys_log.h>
#include <structs/eps2_data.h>

#include "param_server.h"

xTaskHandle xTaskParamServerHandle;

void vTaskParamServer(void *pvParameters)
{
    const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 500 ); /*< Use portMAX_DELAY instead to block indefinitely. */
    BaseType_t xResult;
    uint32_t ulNotifiedValue;
    
    /* Delay before the first cycle */
    vTaskDelay(pdMS_TO_TICKS(TASK_PARAM_SERVER_INITIAL_DELAY_MS));

    while(1)
    {
        xResult = xTaskNotifyWait(0UL, 0xFFFFFFFFUL, &ulNotifiedValue, xMaxBlockTime);

        if (xResult == pdPASS)
        {
            if ( (ulNotifiedValue & NOTIFICATION_VALUE_FROM_I2C_SLAVE_ISR) != 0)
            {
                /* TO DO. */
                /* Process interrupt from i2c_slave ISR. */
            }
            if ( (ulNotifiedValue & NOTIFICATION_VALUE_FROM_UART) != 0)
            {
                /* TO DO. */
            }
        }
        else
        {
            /* xTaskNotifyWait timed out. */
        }

        // TickType_t last_cycle = xTaskGetTickCount();

        // eps2_param_id_t req_id = UINT8_MAX;

        // switch(req_id)
        // {
        //     case EPS2_PARAM_ID_TIME_COUNTER:
        //         break;
        //     case EPS2_PARAM_ID_MCU_TEMP:
        //         break;
        //     case EPS2_PARAM_ID_EPS_CURRENT:
        //         break;
        //     case EPS2_PARAM_ID_LAST_RESET_CAUSE:
        //         break;
        //     case EPS2_PARAM_ID_RESET_COUNTER:
        //         break;
        //     case EPS2_PARAM_ID_SP_MY_PX_VOLTAGE:
        //         break;
        //     case EPS2_PARAM_ID_SP_MX_PZ_VOLTAGE:
        //         break;
        //     case EPS2_PARAM_ID_SP_MZ_PY_VOLTAGE:
        //         break;
        //     case EPS2_PARAM_ID_SP_MY_CURRENT:
        //         break;
        //     case EPS2_PARAM_ID_SP_PY_CURRENT:
        //         break;
        //     case EPS2_PARAM_ID_SP_MX_CURRENT:
        //         break;
        //     case EPS2_PARAM_ID_SP_PX_CURRENT:
        //         break;
        //     case EPS2_PARAM_ID_SP_MZ_CURRENT:
        //         break;
        //     case EPS2_PARAM_ID_SP_PZ_CURRENT:
        //         break;
        //     case EPS2_PARAM_ID_MPPT_1_DUTY_CYCLE:
        //         break;
        //     case EPS2_PARAM_ID_MPPT_2_DUTY_CYCLE:
        //         break;
        //     case EPS2_PARAM_ID_MPPT_3_DUTY_CYCLE:
        //         break;
        //     case EPS2_PARAM_ID_SP_VOLTAGE_MPPT:
        //         break;
        //     case EPS2_PARAM_ID_MAIN_POWER_BUS_VOLTAGE:
        //         break;
        //     case EPS2_PARAM_ID_RTD_0_TEMP:
        //         break;
        //     case EPS2_PARAM_ID_RTD_1_TEMP:
        //         break;
        //     case EPS2_PARAM_ID_RTD_2_TEMP:
        //         break;
        //     case EPS2_PARAM_ID_RTD_3_TEMP:
        //         break;
        //     case EPS2_PARAM_ID_RTD_4_TEMP:
        //         break;
        //     case EPS2_PARAM_ID_RTD_5_TEMP:
        //         break;
        //     case EPS2_PARAM_ID_RTD_6_TEMP:
        //         break;
        //     case EPS2_PARAM_ID_BAT_VOLTAGE:
        //         break;
        //     case EPS2_PARAM_ID_BAT_CURRENT:
        //         break;
        //     case EPS2_PARAM_ID_BAT_AVERAGE_CURRENT:
        //         break;
        //     case EPS2_PARAM_ID_BAT_ACC_CURRENT:
        //         break;
        //     case EPS2_PARAM_ID_BAT_CHARGE:
        //         break;
        //     case EPS2_PARAM_ID_BAT_MONITOR_TEMP:
        //         break;
        //     case EPS2_PARAM_ID_BAT_MONITOR_STATUS:
        //         break;
        //     case EPS2_PARAM_ID_BAT_MONITOR_PROTECT:
        //         break;
        //     case EPS2_PARAM_ID_BAT_MONITOR_CYCLE_COUNTER:
        //         break;
        //     case EPS2_PARAM_ID_BAT_MONITOR_RAAC:
        //         break;
        //     case EPS2_PARAM_ID_BAT_MONITOR_RSAC:
        //         break;
        //     case EPS2_PARAM_ID_BAT_MONITOR_RARC:
        //         break;
        //     case EPS2_PARAM_ID_BAT_MONITOR_RSRC:
        //         break;
        //     case EPS2_PARAM_ID_BAT_HEATER_1_DUTY_CYCLE:
        //         break;
        //     case EPS2_PARAM_ID_BAT_HEATER_2_DUTY_CYCLE:
        //         break;
        //     case EPS2_PARAM_ID_HW_VERSION:
        //         break;
        //     case EPS2_PARAM_ID_FW_VERSION:
        //         break;
        //     case EPS2_PARAM_ID_MPPT_1_MODE:
        //         break;
        //     case EPS2_PARAM_ID_MPPT_2_MODE:
        //         break;
        //     case EPS2_PARAM_ID_MPPT_3_MODE:
        //         break;
        //     case EPS2_PARAM_ID_BAT_HEATER_1_MODE:
        //         break;
        //     case EPS2_PARAM_ID_BAT_HEATER_2_MODE:
        //         break;
        //     case EPS2_PARAM_ID_DEVICE_ID:
        //         break;
        //     default:
        //         sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_PARAM_SERVER_NAME, "Unknown parameter ID!");
        //         sys_log_new_line();
        // }

        // vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_PARAM_SERVER_PERIOD_MS));
    }
}

/** \} End of param_server group */
