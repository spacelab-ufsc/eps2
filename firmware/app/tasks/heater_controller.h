/*
 * heater_controller.h
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
 * \brief Heater controller task definition.
 *
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 *
 * \version 0.2.12
 *
 * \date 2021/08/04
 *
 * \defgroup heater_controller Heater Controller
 * \ingroup tasks
 * \{
 */

#ifndef HEATER_CONTROLLER_H_
#define HEATER_CONTROLLER_H_

#include <FreeRTOS.h>
#include <task.h>

#define TASK_HEATER_CONTROLLER_NAME             "Heater Controller" /**< Task name. */
#define TASK_HEATER_CONTROLLER_STACK_SIZE       160             	/**< Memory stack size in bytes. */
#define TASK_HEATER_CONTROLLER_PRIORITY         3               	/**< Priority. */
#define TASK_HEATER_CONTROLLER_PERIOD_MS        500             	/**< Period in milliseconds. */
#define TASK_HEATER_CONTROLLER_INIT_TIMEOUT_MS  2000            	/**< Wait time to initialize the task in milliseconds. */

#define HEATER_AUTOMATIC_MODE		0x00
#define HEATER_MANUAL_MODE 			0x01

/**
 * \brief Heater controller task handle.
 */
extern xTaskHandle xTaskHeaterControllerHandle;

/**
 * \brief Heater controller task.
 *
 * \param[in] pvParameters is a value that will passed as the task's parameter.
 *
 * \return None.
 */
void vTaskHeaterController(void *pvParameters);

#endif /* HEATER_CONTROLLER_H_ */

/** \} End of heater_controller group */
