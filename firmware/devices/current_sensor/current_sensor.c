/*
 * current_sensor.c
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
 * \brief Current sensor device implementation.
 *
 * \author Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 2021/01/31
 *
 * \addtogroup current_sensor
 * \{
 */

#include <drivers/adc/adc.h>

#include <system/sys_log/sys_log.h>

#include "current_sensor.h"

int current_sensor_init()
{
    return -1;
}

int current_sensor_read_raw(uint16_t *val)
{
    return -1;
}

int current_sensor_read(float *cur)
{
    return -1;
}

/** \} End of current_sensor group */
