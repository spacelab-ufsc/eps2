/*
 * obdh.c
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
 * \brief OBDH device implementation.
 *
 * \author Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 * \author Andre M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 *
 * \version 0.2.1
 *
 * \date 05/07/2021
 *
 * \addtogroup obdh
 * \{
 */

#include <stdbool.h>

#include <drivers/sl_obdh2/sl_obdh2.h>

#include <system/sys_log/sys_log.h>

#include "obdh.h"

bool obdh_is_open = false;

sl_obdh2_config_t obdh_config = {0};

int obdh_init()
{
    if (obdh_is_open)
        {
            return 0;   /* EPS device already initialized */
        }

        sys_log_print_event_from_module(SYS_LOG_INFO, OBDH_MODULE_NAME, "Initializing OBDH device...");
        sys_log_new_line();

        obdh_config.i2c_port     = I2C_PORT_1;
        obdh_config.i2c_config   = (i2c_config_t){.speed_hz=100000};
        obdh_config.en_pin       = GPIO_PIN_17;
        obdh_config.ready_pin    = GPIO_PIN_20;

        int err = sl_obdh2_init(obdh_config);
        if (err != 0)
        {
            sys_log_print_event_from_module(SYS_LOG_ERROR, OBDH_MODULE_NAME, "Error during the initialization! (error ");
            sys_log_print_int(err);
            sys_log_print_msg(")");
            sys_log_new_line();
        }
    return -1;
}

int obdh_decode(void) {
	// call crc package
	// return action to be performed from a list
	return -1;
}

int obdh_answer(void) {
	// select answer action
	// populate TX buffer
	return -1;
}

/** \} End of obdh group */




