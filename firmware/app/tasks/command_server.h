/*
 * command_server.h
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
 * \brief Command server task definition.
 *
 * \author Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 20/07/2021
 *
 * \defgroup command_server Command server
 * \ingroup tasks
 * \{
 */

#ifndef COMMAND_SERVER_H_
#define COMMAND_SERVER_H_

#include <FreeRTOS.h>
#include <task.h>

#define TASK_COMMAND_SERVER_NAME                "Command_Server"    /**< Task name. */
#define TASK_COMMAND_SERVER_STACK_SIZE          1024            /**< Memory stack size in bytes. */ // >> TDB <<
#define TASK_COMMAND_SERVER_PRIORITY            5               /**< Priority. */
#define TASK_COMMAND_SERVER_PERIOD_MS           10             /**< Period in milliseconds. */ // >> Unblocked by I2C_Slave ISR <<
#define TASK_COMMAND_SERVER_INIT_TIMEOUT_MS     4500            /**< Wait time to initialize the task in milliseconds. */

/**
 * \brief Command server task handle.
 */
extern xTaskHandle xTaskCommandServerHandle;

/**
 * \brief Command server task.
 *
 * \param[in] pvParameters is a value that will passed as the task's parameter.
 *
 * \return None.
 */
void vTaskCommandServer(void *pvParameters);

#endif /* COMMAND_SERVER_H_ */

/** \} End of command_server group */
