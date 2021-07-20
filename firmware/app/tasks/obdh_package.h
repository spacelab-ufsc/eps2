/*
 * obdh_package.h
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
 * \brief OBDH package task definition.
 *
 * \author Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 20/07/2021
 *
 * \defgroup obdh_package OBDH package
 * \ingroup tasks
 * \{
 */

#ifndef OBDH_PACKAGE_H_
#define OBDH_PACKAGE_H_

#include <FreeRTOS.h>
#include <task.h>

#define TASK_OBDH_PACKAGE_NAME                "OBDH_Package"    /**< Task name. */
#define TASK_OBDH_PACKAGE_STACK_SIZE          1024            /**< Memory stack size in bytes. */ // >> TDB <<
#define TASK_OBDH_PACKAGE_PRIORITY            5               /**< Priority. */
#define TASK_OBDH_PACKAGE_PERIOD_MS           10             /**< Period in milliseconds. */ // >> Unblocked by I2C_Slave ISR <<
#define TASK_OBDH_PACKAGE_INIT_TIMEOUT_MS     4500            /**< Wait time to initialize the task in milliseconds. */

/**
 * \brief OBDH package task handle.
 */
extern xTaskHandle xTaskOBDHPackageHandle;

/**
 * \brief OBDH package task.
 *
 * \param[in] pvParameters is a value that will passed as the task's parameter.
 *
 * \return None.
 */
void vTaskOBDHPackage(void *pvParameters);

#endif /* OBDH_PACKAGE_H_ */

/** \} End of obdh_package group */
