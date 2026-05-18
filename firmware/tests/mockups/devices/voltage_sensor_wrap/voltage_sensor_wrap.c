/*
 * voltage_sensor_wrap.c
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
 * \brief Voltage Sensor device wrap definition.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2022/08/15
 *
 * \defgroup voltage_sensor_wrap Voltage Sensor Wrap
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include "voltage_sensor_wrap.h"

int __wrap_voltage_sensor_init(void)
{
    return mock_type(int);
}

uint16_t __wrap_voltage_sensor_raw_to_mv(adc_port_t port, uint16_t raw)
{
    return mock_type(uint16_t);
}

int __wrap_voltage_sensor_read(adc_port_t port, uint16_t *volt)
{
    *volt = mock_type(uint16_t);
    return mock_type(int);
}

/** \} End of voltage_sensor_wrap group */
