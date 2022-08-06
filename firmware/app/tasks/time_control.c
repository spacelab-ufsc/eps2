/*
 * time_control.h
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
 * \brief Time control task implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.37
 * 
 * \date 2020/08/09
 * 
 * \addtogroup time_control
 * \{
 */

#include <system/system.h>
#include <system/sys_log/sys_log.h>
/* #include <devices/media/media.h> */
#include <config/config.h>

#include "time_control.h"
#include "startup.h"

#define TIME_CONTROL_MEDIA              MEDIA_NOR
#define TIME_CONTROL_SAVE_PERIOD_SEC    60
#define TIME_CONTROL_MEM_ID             0x12U
#define TIME_CONTROL_CRC8_INITIAL_VAL   0x00U       /* CRC8-CCITT initial value. */
#define TIME_CONTROL_CRC8_POLYNOMIAL    0x07U       /* CRC8-CCITT polynomial. */

xTaskHandle xTaskTimeControlHandle;

/**
 * \brief Loads the last saved system time from the non-volatile memory.
 *
 * \param[in,out] tm is a pointer to load the read system time from the memory.
 *
 * \return The status/error code.
 */
static int time_control_load_sys_time(sys_time_t *tm);

/**
 * \brief Saves a given system time to the non-volatile memory.
 *
 * \param[in] tm is the system time value to save.
 *
 * \return The status/error code.
 */
static int time_control_save_sys_time(sys_time_t tm);

/**
 * \brief Computes the CRC-8 of a sequence of bytes.
 *
 * \param[in] data is an array of data to compute the CRC-8.
 *
 * \param[in] len is the number of bytes of the given array.
 *
 * \return The computed CRC-8 value of the given data.
 */
static uint8_t time_control_crc8(uint8_t *data, uint8_t len);

void vTaskTimeControl(void)
{
    /* Wait startup task to finish */
    xEventGroupWaitBits(task_startup_status, TASK_STARTUP_DONE, pdFALSE, pdTRUE, pdMS_TO_TICKS(TASK_TIME_CONTROL_INIT_TIMEOUT_MS));

    /* Load the last saved system time */
    sys_time_t last_sys_time = 0;

    if (time_control_load_sys_time(&last_sys_time) == 0)
    {
        sys_log_print_event_from_module(SYS_LOG_INFO, TASK_TIME_CONTROL_NAME, "Last saved system time (epoch): ");
        sys_log_print_uint(last_sys_time);
        sys_log_print_msg(" sec");
        sys_log_new_line();
    }
    else
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_TIME_CONTROL_NAME, "The last saved system time is not available!");
        sys_log_new_line();
    }

    system_set_time(last_sys_time);

    vTaskDelay(pdMS_TO_TICKS(1000));

    while(1)
    {
        TickType_t last_cycle = xTaskGetTickCount();

        system_increment_time();

        /* Read the current system time */
        sys_time_t sys_tm = system_get_time();

        if ((sys_tm % TIME_CONTROL_SAVE_PERIOD_SEC) == 0)
        {
            /* Save the current system time */
            if (time_control_save_sys_time(sys_tm) != 0)
            {
                sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_TIME_CONTROL_NAME, "Error saving the system time!");
                sys_log_new_line();
            }
        }

        vTaskDelayUntil(&last_cycle, pdMS_TO_TICKS(TASK_TIME_CONTROL_PERIOD_MS));
    }
}

static int time_control_load_sys_time(sys_time_t *tm)
{
    int err = -1;

    uint8_t buf[6] = {0};
/*
    if (media_read(TIME_CONTROL_MEDIA, CONFIG_MEM_ADR_SYS_TIME, buf, 6U) == 0)
    {
        if ((buf[0] == TIME_CONTROL_MEM_ID) && (time_control_crc8(buf, 5U) == buf[5]))
        {
            *tm = ((sys_time_t)buf[1] << 24) |
                  ((sys_time_t)buf[2] << 16) |
                  ((sys_time_t)buf[3] << 8) |
                  (sys_time_t)buf[4];

            err = 0;
        }
        else
        {
            sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_TIME_CONTROL_NAME, "Error reading the system time from the non-volatile memory!");
            sys_log_new_line();
        }
    }
    else
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_TIME_CONTROL_NAME, "Error reading the system time from the non-volatile memory!");
        sys_log_new_line();
    }
*/
    return err;
}

static int time_control_save_sys_time(sys_time_t tm)
{
    int err = 0;

    uint8_t buf[6] = {0};

    buf[0] = TIME_CONTROL_MEM_ID;
    buf[1] = ((uint32_t)tm >> 24) & 0xFFU;
    buf[2] = ((uint32_t)tm >> 16) & 0xFFU;
    buf[3] = ((uint32_t)tm >> 8) & 0xFFU;
    buf[4] = (uint32_t)tm & 0xFFU;
    buf[5] = time_control_crc8(buf, 5U);
/*
    if (media_write(TIME_CONTROL_MEDIA, CONFIG_MEM_ADR_SYS_TIME, buf, 6U) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, TASK_TIME_CONTROL_NAME, "Error writing the system time to the non-volatile memory!");
        sys_log_new_line();

        err = -1;
    }
*/
    return err;
}

static uint8_t time_control_crc8(uint8_t *data, uint8_t len)
{
    uint8_t crc = TIME_CONTROL_CRC8_INITIAL_VAL;

    uint8_t i = 0U;
    for(i = 0; i < len; i++)
    {
        crc ^= data[i];

        uint8_t j = 0U;
        for (j = 0U; j < 8U; j++)
        {
            crc = (crc << 1) ^ ((crc & 0x80U) ? TIME_CONTROL_CRC8_POLYNOMIAL : 0U);
        }

        crc &= 0xFFU;
    }

    return crc;
}

/** \} End of time_control group */
