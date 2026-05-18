/*
 * adc_mutex.h
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
 * \brief ADC mutex implementation.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 *
 * \version 0.2.20
 *
 * \date 2021/08/11
 *
 * \defgroup adc_mutex Mutex
 * \ingroup adc
 * \{
 */

#include <FreeRTOS.h>
#include <semphr.h>

#include <system/sys_log/sys_log.h>

#include "adc.h"

#define ADC_MUTEX_WAIT_TIME_MS      100

SemaphoreHandle_t xADCSemaphore = NULL;

bool adc_mutex_create(void)
{
    /* Create a mutex type semaphore */
    xADCSemaphore = xSemaphoreCreateMutex();

    if (xADCSemaphore == NULL)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, ADC_MODULE_NAME, "Error creating a mutex!");
        sys_log_new_line();

        return false;
    }

    return true;
}

bool adc_mutex_take(void)
{
    if (xADCSemaphore != NULL)
    {
        /* See if we can obtain the semaphore. If the semaphore is not */
        /* available wait ADC_MUTEX_WAIT_TIME_MS ms to see if it becomes free */
        if (xSemaphoreTake(xADCSemaphore, pdMS_TO_TICKS(ADC_MUTEX_WAIT_TIME_MS)) == pdTRUE)
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

bool adc_mutex_give(void)
{
    if (xADCSemaphore != NULL)
    {
        xSemaphoreGive(xADCSemaphore);

        return true;
    }
    else
    {
        return false;
    }
}

/** \} End of sys_log_mutex group */
