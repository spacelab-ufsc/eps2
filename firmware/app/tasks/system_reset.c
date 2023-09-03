/*
 * system_reset.c
 * 
 * Copyright (C) 2020, SpaceLab.
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
 * \brief Periodic system reset task implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * \author Ramon de Araujo Borba <ramonborba97@gmail.com>
 * 
 * \version 0.4.0
 * 
 * \date 14/06/2021
 * 
 * \addtogroup system_reset
 * \{
 */

#include <system/system.h>
#include <system/sys_log/sys_log.h>

#include "system_reset.h"

#define pdMS_TO_TICKS_LONG( xTimeInMs ) ( ( TickType_t ) ( ( ( uint64_t ) ( xTimeInMs ) * ( uint64_t ) configTICK_RATE_HZ ) / ( TickType_t ) 1000 ) )

xTaskHandle xTaskSystemResetHandle;

void vTaskSystemReset(void *pvParameters)
{
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS_LONG(TASK_SYSTEM_RESET_PERIOD_MS));

        sys_log_print_event_from_module(SYS_LOG_INFO, TASK_SYSTEM_RESET_NAME, "Restarting the system...");
        sys_log_new_line();

        system_reset();
    }
}

/** \} End of system_reset group */
