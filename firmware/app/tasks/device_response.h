/*
 * device_response.h
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
 * \defgroup device_response DeviceResponse
 * \ingroup tasks
 * \{
 */

#ifndef DEVICE_RESPONSE_H_
#define DEVICE_RESPONSE_H_

#include <FreeRTOS.h>
#include <task.h>

#define TASK_DEVICE_RESPONSE_NAME                 "DeviceResponse"     /**< Task name. */
#define TASK_DEVICE_RESPONSE_STACK_SIZE           160             /**< Memory stack size in bytes. */
#define TASK_DEVICE_RESPONSE_PRIORITY             2               /**< Priority. */
#define TASK_DEVICE_RESPONSE_PERIOD_MS            60000UL           /**< Period in milliseconds. */
#define TASK_DEVICE_RESPONSE_INIT_TIMEOUT_MS      10000UL          /**< Wait time to initialize the task in milliseconds. */
#define TASK_DEVICE_RESPONSE_INITIAL_DELAY_MS     10000UL           /**< Delay, in milliseconds, before the first execution. */

#define EPS_DATA_STRUCTURE_SIZE                   49
#define DEVICE_RESPONSE_BUFFER_SIZE               (1 + 4 * EPS_DATA_STRUCTURE_SIZE)   /* 1 + (49 * 4) bytes --- CMD + EPS_DATA_STRUCTURE_SIZE in bytes */
#define DEVICE_COMMAND_WRITE                      0x03

/**
 * \brief DeviceResponse task handle.
 */
extern xTaskHandle xTaskDeviceResponseHandle;

/**
 * \brief Device response task.
 *
 * \param[in] pvParameters is a value that will passed as the task's parameter.
 *
 * \return None.
 */
void vTaskDeviceResponse(void *pvParameters);

#endif /* DEVICE_RESPONSE_H_ */

/** \} End of device_response group */
