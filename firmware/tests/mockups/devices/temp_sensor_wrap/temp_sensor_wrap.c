/*
 * temp_sensor_wrap.c
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
 * \brief Temp Sensor device wrap definition.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2022/05/17
 *
 * \defgroup temp_sensor_wrap Temp Sensor Wrap
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include "temp_sensor_wrap.h"

int __wrap_temp_sensor_init(void)
{
    return mock();
}

int __wrap_temp_sensor_suspend(temp_sensor_t *config, temp_sensor_power_down_t mode)
{
    return mock();
}

int __wrap_temp_mcu_read_raw(uint16_t *val)
{
    check_expected(*val);

    return mock_type(int);
}

int16_t __wrap_temp_mcu_raw_to_c(uint16_t raw)
{
    check_expected(raw);
    return mock_type(int16_t);
}

uint16_t __wrap_temp_mcu_raw_to_k(uint16_t raw)
{
    check_expected(raw);
    return mock_type(uint16_t);
}

int __wrap_temp_mcu_read_c(int16_t *temp)
{
    check_expected(*temp);
    return mock_type(int);
}

int __wrap_temp_mcu_read_k(uint16_t *temp)
{
    check_expected(*temp);
    return mock_type(int);
}

int __wrap_temp_rtd_read_raw(uint8_t positive_channel, uint32_t *val)
{
    check_expected(positive_channel);
    check_expected(*val);

    return mock_type(int);
}

int16_t __wrap_temp_rtd_raw_to_c(uint32_t raw)
{
    check_expected(raw);
    return mock_type(int16_t);
}

uint16_t __wrap_temp_rtd_raw_to_k(uint32_t raw)
{
    check_expected(raw);
    return mock_type(uint16_t);
}

int __wrap_temp_rtd_read_c(uint8_t channel, uint16_t *temp)
{
    check_expected(channel);
    check_expected(temp);

    return mock_type(int);
}

int __wrap_temp_rtd_read_k(uint8_t channel, uint16_t *temp)
{
    // check_expected(channel);
    // check_expected(temp);
    return mock_type(int);
}

/** \} End of temp_sensor_wrap group */
