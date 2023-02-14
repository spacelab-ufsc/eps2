/*
 * heater_controller.c
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
 * \brief Heater controller task implementation.
 *
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.2.36
 *
 * \date 2021/08/04
 *
 * \addtogroup heater_controller
 * \{
 */

#include <system/sys_log/sys_log.h>
#include <structs/eps2_data.h>

#include <devices/heater/heater.h>
#include <devices/heater/heater_on_off.h>

#include "heater_controller.h"
#include "startup.h"

xTaskHandle xTaskHeaterControllerHandle;

/**
 * \brief Heater control routine.
 *
 * \param[in] channel is the heater channel to controle. It can be:
 * \parblock
 *      - HEATER_CONTROL_LOOP_CH_0
 *      - HEATER_CONTROL_LOOP_CH_1
 *      .
 * \endparblock
 *
 * \param[in] mode is the heater mode. It can be:
 * \parblock
 *      - HEATER_AUTOMATIC_MODE
 *      - HEATER_MANUAL_MODE
 *      .
 * \endparblock
 *
 * \param[in] duty_cycle is the heater pwm duty cycle. It can be:
 * \parblock
 *      - 1 to 100 (duty cycle percentage)
 *      .
 * \endparblock
 *
 * \return None.
 */
void heater_control(int channel, uint32_t mode, uint32_t duty_cycle);

void vTaskHeaterController(void)
{
    uint32_t heater_mode = 0;
    uint32_t heater_dt_cycle = 0;

    /* Wait startup task to finish */
    xEventGroupWaitBits(task_startup_status, TASK_STARTUP_DONE, pdFALSE, pdTRUE, pdMS_TO_TICKS(TASK_HEATER_CONTROLLER_INIT_TIMEOUT_MS));

    while(1)
    {
        TickType_t last_cycle = xTaskGetTickCount();

        /* Heater 1 */
        eps_buffer_read(EPS2_PARAM_ID_BAT_HEATER_1_MODE, &heater_mode);
        eps_buffer_read(EPS2_PARAM_ID_BAT_HEATER_1_DUTY_CYCLE, &heater_dt_cycle);

        heater_control(HEATER_CONTROL_LOOP_CH_0, heater_mode, heater_dt_cycle);

        /* Heater 2 */
        eps_buffer_read(EPS2_PARAM_ID_BAT_HEATER_2_MODE, &heater_mode);
        eps_buffer_read(EPS2_PARAM_ID_BAT_HEATER_2_DUTY_CYCLE, &heater_dt_cycle);

        heater_control(HEATER_CONTROL_LOOP_CH_1, heater_mode, heater_dt_cycle);

        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_HEATER_CONTROLLER_PERIOD_MS));
    }
}

void heater_control(int channel, uint32_t mode, uint32_t duty_cycle)
{

    static uint32_t last_mode[2] = { HEATER_AUTOMATIC_MODE };

    switch(mode)
    {
        case HEATER_AUTOMATIC_MODE:
        {
            temperature_t temp = 0;
            
            if (last_mode[channel] != HEATER_AUTOMATIC_MODE)
            {
                if (heater_on_off_init(channel))
                {
                    sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_HEATER_CONTROLLER_NAME, "Heater channel ");
                    sys_log_print_uint(channel);
                    sys_log_print_msg(" failed on/off initialization!");
                    sys_log_new_line();
                }
                last_mode[channel] = HEATER_AUTOMATIC_MODE;
            }
            

            if (heater_on_off_get_sensor(channel, &temp) == 0)
            {
                sys_log_print_event_from_module(SYS_LOG_INFO, TASK_HEATER_CONTROLLER_NAME, "Temp Reading [K]: ");
                sys_log_print_int(temp);
                sys_log_new_line();
                if (heater_on_off_set_actuator(channel, heater_on_off_algorithm(channel, temp)) != 0)
                {
                    sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_HEATER_CONTROLLER_NAME, "Heater channel ");
                    sys_log_print_uint(channel);
                    sys_log_print_msg(" failed! (set_actuator)");
                    sys_log_new_line();
                }
            }
            else
            {
                sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_HEATER_CONTROLLER_NAME, "Heater channel ");
                sys_log_print_uint(channel);
                sys_log_print_msg(" failed! (get_sensor)");
                sys_log_new_line();
            }

            break;
        }
        case HEATER_MANUAL_MODE:
        {
            if (last_mode[channel] != HEATER_MANUAL_MODE)
            {
                if (heater_init(channel))
                {
                    sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_HEATER_CONTROLLER_NAME, "Heater channel ");
                    sys_log_print_uint(channel);
                    sys_log_print_msg(" failed manual mode initialization!");
                    sys_log_new_line();
                }
                last_mode[channel] = HEATER_MANUAL_MODE;
            }
            if (heater_set_actuator(channel, (float)duty_cycle) != 0)
            {
                sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_HEATER_CONTROLLER_NAME, "Heater channel ");
                sys_log_print_uint(channel);
                sys_log_print_msg(" failed! (set_actuator)");
                sys_log_new_line();
            }

            break;
        }
        default:
            sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_HEATER_CONTROLLER_NAME, "Invalid mode!");
            sys_log_new_line();

            break;
    }
}

/** \} End of heater_controller group */