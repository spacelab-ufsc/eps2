/*
 * mppt_algorithm.c
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
 * \brief MPPT algorithm task implementation.
 *
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 *
 * \version 0.2.19
 *
 * \date 2021/08/02
 *
 * \addtogroup mppt_algorithm
 * \{
 */

#include <system/sys_log/sys_log.h>
#include <structs/eps2_data.h>

#include <devices/mppt/mppt.h>

#include "mppt_algorithm.h"
#include "startup.h"

xTaskHandle xTaskMPPTAlgorithmHandle;

void vTaskMPPTAlgorithm(void *pvParameters)
{
	uint32_t mppt_mode = 0;
	uint32_t mppt_duty_cyle = 0;

	/* Wait startup task to finish */
    xEventGroupWaitBits(task_startup_status, TASK_STARTUP_DONE, pdFALSE, pdTRUE, pdMS_TO_TICKS(TASK_MPPT_ALGORITHM_INIT_TIMEOUT_MS));
	
	while(1)
	{
		TickType_t last_cycle = xTaskGetTickCount();
		
		eps_buffer_read(EPS2_PARAM_ID_MPPT_1_MODE, &mppt_mode);
		switch(mppt_mode) 
		{
			case MPPT_AUTOMATIC_MODE:
				if(mppt_algorithm(MPPT_CONTROL_LOOP_CH_0) != 0) 
				{
					sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_MPPT_ALGORITHM_NAME, "MPPT channel 0 failed!");
	        		sys_log_new_line();
				}
				break;
			case MPPT_MANUAL_MODE:
				eps_buffer_read(EPS2_PARAM_ID_MPPT_1_DUTY_CYCLE, &mppt_duty_cyle);
				/* TODO: Implement manual mode */
				break;
			default:
				sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_MPPT_ALGORITHM_NAME, "Invalid mode!");
        		sys_log_new_line();
				break;
		}

		eps_buffer_read(EPS2_PARAM_ID_MPPT_2_MODE, &mppt_mode);
		switch(mppt_mode) 
		{
			case MPPT_AUTOMATIC_MODE:
				if(mppt_algorithm(MPPT_CONTROL_LOOP_CH_1) != 0) 
				{
					sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_MPPT_ALGORITHM_NAME, "MPPT channel 1 failed!");
	        		sys_log_new_line();
				}
				break;
			case MPPT_MANUAL_MODE:
				eps_buffer_read(EPS2_PARAM_ID_MPPT_2_DUTY_CYCLE, &mppt_duty_cyle);
				/* TODO: Implement manual mode */
				break;
			default:
				sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_MPPT_ALGORITHM_NAME, "Invalid mode!");
        		sys_log_new_line();
				break;
		}

		eps_buffer_read(EPS2_PARAM_ID_MPPT_3_MODE, &mppt_mode);
		switch(mppt_mode) 
		{
			case MPPT_AUTOMATIC_MODE:
				if(mppt_algorithm(MPPT_CONTROL_LOOP_CH_2) != 0) 
				{
					sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_MPPT_ALGORITHM_NAME, "MPPT channel 2 failed!");
	        		sys_log_new_line();
				}
				break;
			case MPPT_MANUAL_MODE:
				eps_buffer_read(EPS2_PARAM_ID_MPPT_3_DUTY_CYCLE, &mppt_duty_cyle);
				/* TODO: Implement manual mode */
				break;
			default:
				sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_MPPT_ALGORITHM_NAME, "Invalid mode!");
        		sys_log_new_line();
				break;
		}

        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_MPPT_ALGORITHM_PERIOD_MS));
	}
}

/** \} End of mppt_algorithm group */
