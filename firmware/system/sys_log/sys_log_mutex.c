/*
 * sys_log_mutes.h
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with EPS 2.0. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief System log mutex implementation.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 2020/10/22
 *
 * \defgroup sys_log_mutex Mutex
 * \ingroup sys_log
 * \{
 */

#include "sys_log.h"
#include "sys_log_config.h"

SemaphoreHandle_t xSysLogSemaphore = NULL;

bool sys_log_mutex_create()
{
    /* Create a mutex type semaphore */
    xSysLogSemaphore = xSemaphoreCreateMutex();

    if (xSysLogSemaphore == NULL)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, SYS_LOG_DEVICE_NAME, "Error creating a mutex!");
        sys_log_new_line();

        return false;
    }

    return true;
}

bool sys_log_mutex_take()
{
    if (xSysLogSemaphore != NULL)
    {
        /* See if we can obtain the semaphore. If the semaphore is not */
        /* available wait SYS_LOG_MUTEX_WAIT_TIME_MS ms to see if it becomes free */
        if (xSemaphoreTake(xSysLogSemaphore, pdMS_TO_TICKS(SYS_LOG_MUTEX_WAIT_TIME_MS)) == pdTRUE)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool sys_log_mutex_give()
{
    if (xSysLogSemaphore != NULL)
    {
        xSemaphoreGive(xSysLogSemaphore);

        return true;
    }
    else
    {
        return false;
    }
}

/** \} End of sys_log_mutex group */
