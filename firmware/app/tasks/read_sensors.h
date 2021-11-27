/*
 * read_sensors.h
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
 * \brief Read external sensors task definition.
 * 
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.35
 * 
 * \date 2021/04/23
 * 
 * \defgroup read_sensors Read sensors
 * \ingroup tasks
 * \{
 */

#ifndef READ_SENSORS_H_
#define READ_SENSORS_H_

#include <FreeRTOS.h>
#include <task.h>

#define TASK_READ_SENSORS_NAME                  "Read Sensors"      /**< Task name. */
#define TASK_READ_SENSORS_STACK_SIZE            128                 /**< Stack size in bytes. */
#define TASK_READ_SENSORS_PRIORITY              2                   /**< Task priority. */
#define TASK_READ_SENSORS_PERIOD_MS             (60*1000)           /**< Task period in milliseconds. */
#define TASK_READ_SENSORS_INIT_TIMEOUT_MS       2000                /**< Wait time to initialize the task in milliseconds. */

/**
 * \brief Read sensors handle.
 */
extern xTaskHandle xTaskReadSensorsHandle;

/**
 * \brief Read onboard sensors task.
 *
 * \return None.
 */
void vTaskReadSensors(void);

#endif /* READ_SENSORS_H_ */

/** \} End of read_sensors group */
