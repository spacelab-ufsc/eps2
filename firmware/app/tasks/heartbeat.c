/*
 * heartbeat.c
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
 * \brief Heartbeat task implementation.
 *
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 *
 * \version 0.1.6
 *
 * \date 26/05/2021
 *
 * \addtogroup heartbeat
 * \{
 */

#include <devices/leds/leds.h>

#include "heartbeat.h"
#include "startup.h"

xTaskHandle xTaskHeartbeatHandle;

void vTaskHeartbeat(void *pvParameters)
{
    /* Wait startup task to finish */
    xEventGroupWaitBits(task_startup_status, TASK_STARTUP_DONE, pdFALSE, pdTRUE, pdMS_TO_TICKS(TASK_HEARTBEAT_INIT_TIMEOUT_MS));

    while(1)
    {
        TickType_t last_cycle = xTaskGetTickCount();

        led_toggle(LED_SYSTEM);

        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_HEARTBEAT_PERIOD_MS));
    }
}

/** \} End of heartbeat group */
