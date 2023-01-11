/*
 * mppt_algorithm.h
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
 * \brief MPPT algorithm task definition.
 *
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 *
 * \version 0.2.10
 *
 * \date 2021/08/02
 *
 * \defgroup mppt_algorithm MPPT Algorithm
 * \ingroup tasks
 * \{
 */

#ifndef MPPT_ALGORITHM_H_
#define MPPT_ALGORITHM_H_

#include <FreeRTOS.h>
#include <task.h>

#define TASK_MPPT_ALGORITHM_NAME                 "MPPT Algorithm"   /**< Task name. */
#define TASK_MPPT_ALGORITHM_STACK_SIZE           160             	/**< Memory stack size in bytes. */
#define TASK_MPPT_ALGORITHM_PRIORITY             3               	/**< Priority. */
#define TASK_MPPT_ALGORITHM_PERIOD_MS            300UL             	/**< Period in milliseconds. */
#define TASK_MPPT_ALGORITHM_INIT_TIMEOUT_MS      2000UL            	/**< Wait time to initialize the task in milliseconds. */

#define MPPT_AUTOMATIC_MODE		0x00
#define MPPT_MANUAL_MODE 		0x01

/**
 * \brief Heartbeat task handle.
 */
extern xTaskHandle xTaskMPPTAlgorithmHandle;

/**
 * \brief Maximum Power Point Tracking algorithm task.
 *
 * \param[in] pvParameters is a value that will passed as the task's parameter.
 *
 * \return None.
 */
void vTaskMPPTAlgorithm(void *pvParameters);


#endif /* MPPT_ALGORITHM_H_ */

/** \} End of mppt_algorithm group */
