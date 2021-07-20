/*
 * obdh_package.c
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
 * \brief OBDH package task implementation.
 *
 * \author Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 20/07/2021
 *
 * \addtogroup obdh_package
 * \{
 */

#include "obdh_package.h"
#include "startup.h"

xTaskHandle xTaskOBDHPackageHandle;

void vTaskOBDHPackage(void *pvParameters)
{
    /* Wait startup task to finish */
    xEventGroupWaitBits(task_startup_status, TASK_STARTUP_DONE, pdFALSE, pdTRUE, pdMS_TO_TICKS(TASK_OBDH_PACKAGE_INIT_TIMEOUT_MS));

    while(1)
    {
        /* TO DO. */

        vTaskDelay(pdMS_TO_TICKS(TASK_OBDH_PACKAGE_PERIOD_MS));
    }
}

/** \} End of obdh_package group */
