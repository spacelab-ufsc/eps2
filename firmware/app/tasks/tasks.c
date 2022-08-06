/*
 * tasks.c
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
 * \brief Tasks implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.37
 * 
 * \date 2021/04/09
 * 
 * \addtogroup tasks
 * \{
 */

#include <FreeRTOS.h>
#include <task.h>

#include <config/config.h>

#include "tasks.h"
#include "startup.h"
#include "heartbeat.h"
#include "watchdog_reset.h"
#include "system_reset.h"
#include "read_sensors.h"
#include "param_server.h"
#include "mppt_algorithm.h"
#include "heater_controller.h"
#include "time_control.h"

void create_tasks(void)
{
    /* Startup task */
#if CONFIG_TASK_STARTUP_ENABLED == 1
    xTaskCreate(vTaskStartup, TASK_STARTUP_NAME, TASK_STARTUP_STACK_SIZE, NULL, TASK_STARTUP_PRIORITY, &xTaskStartupHandle);

    if (xTaskStartupHandle == NULL)
    {
        /* Error creating the startup task */
    }
#endif /* CONFIG_TASK_STARTUP_ENABLED */

    /* Watchdog reset task */
#if CONFIG_TASK_WATCHDOG_RESET_ENABLED == 1
    xTaskCreate(vTaskWatchdogReset, TASK_WATCHDOG_RESET_NAME, TASK_WATCHDOG_RESET_STACK_SIZE, NULL, TASK_WATCHDOG_RESET_PRIORITY, &xTaskWatchdogResetHandle);

    if (xTaskWatchdogResetHandle == NULL)
    {
        /* Error creating the watchdog reset task */
    }
#endif /* CONFIG_TASK_WATCHDOG_RESET_ENABLED */

    /* Heartbeat task */
#if CONFIG_TASK_HEARTBEAT_ENABLED == 1
    xTaskCreate(vTaskHeartbeat, TASK_HEARTBEAT_NAME, TASK_HEARTBEAT_STACK_SIZE, NULL, TASK_HEARTBEAT_PRIORITY, &xTaskHeartbeatHandle);

    if (xTaskHeartbeatHandle == NULL)
    {
        /* Error creating the heartbeat task */
    }
#endif /* CONFIG_TASK_HEARTBEAT_ENABLED */

#if CONFIG_TASK_SYSTEM_RESET_ENABLED == 1
    xTaskCreate(vTaskSystemReset, TASK_SYSTEM_RESET_NAME, TASK_SYSTEM_RESET_STACK_SIZE, NULL, TASK_SYSTEM_RESET_PRIORITY, &xTaskSystemResetHandle);

    if (xTaskSystemResetHandle == NULL)
    {
        /* Error creating the system reset task */
    }
#endif /* CONFIG_TASK_SYSTEM_RESET_ENABLED */

    /* Read sensors task */
#if CONFIG_TASK_READ_SENSORS_ENABLED == 1
    xTaskCreate(vTaskReadSensors, TASK_READ_SENSORS_NAME, TASK_READ_SENSORS_STACK_SIZE, NULL, TASK_READ_SENSORS_PRIORITY, &xTaskReadSensorsHandle);

    if (xTaskReadSensorsHandle == NULL)
    {
        /* Error creating the read sensors task */
    }
#endif /* CONFIG_TASK_READ_SENSORS_ENABLED */

#if CONFIG_TASK_PARAM_SERVER_ENABLED == 1
    xTaskCreate(vTaskParamServer, TASK_PARAM_SERVER_NAME, TASK_PARAM_SERVER_STACK_SIZE, NULL, TASK_PARAM_SERVER_PRIORITY, &xTaskParamServerHandle);

    if (xTaskParamServerHandle == NULL)
    {
        /* Error creating the parameter server task */
    }
#endif /* CONFIG_TASK_PARAM_SERVER_ENABLED */

#if CONFIG_TASK_MPPT_ALGORITHM_ENABLED == 1
    xTaskCreate(vTaskMPPTAlgorithm, TASK_MPPT_ALGORITHM_NAME, TASK_MPPT_ALGORITHM_STACK_SIZE, NULL, TASK_MPPT_ALGORITHM_PRIORITY, &xTaskMPPTAlgorithmHandle);

    if (xTaskMPPTAlgorithmHandle == NULL)
    {
        /* Error creating the parameter server task */
    }
#endif /* CONFIG_TASK_MPPT_ALGORITHM_ENABLED */

#if CONFIG_TASK_HEATER_CONTROLLER_ENABLED == 1
    xTaskCreate(vTaskHeaterController, TASK_HEATER_CONTROLLER_NAME, TASK_HEATER_CONTROLLER_STACK_SIZE, NULL, TASK_HEATER_CONTROLLER_PRIORITY, &xTaskHeaterControllerHandle);

    if (xTaskMPPTAlgorithmHandle == NULL)
    {
        /* Error creating the parameter server task */
    }
#endif /* CONFIG_TASK_HEATER_CONTROLLER_ENABLED */

#if defined(CONFIG_TASK_TIME_CONTROL_ENABLED) && (CONFIG_TASK_TIME_CONTROL_ENABLED == 1)
    xTaskCreate(vTaskTimeControl, TASK_TIME_CONTROL_NAME, TASK_TIME_CONTROL_STACK_SIZE, NULL, TASK_TIME_CONTROL_PRIORITY, &xTaskTimeControlHandle);

    if (xTaskTimeControlHandle == NULL)
    {
        /* Error creating the time control task */
    }
#endif /* CONFIG_TASK_TIME_CONTROL_ENABLED */

    create_event_groups();
}

void create_event_groups(void)
{
    task_startup_status = xEventGroupCreate();

    if (task_startup_status == NULL)
    {
        /* Error creating the startup status event group */
    }
}

/** \} End of tasks group */
