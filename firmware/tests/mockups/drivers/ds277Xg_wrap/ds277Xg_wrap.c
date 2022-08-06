/*
 * ds277xg_wrap.c
 *
 * Copyright (C) 2022, SpaceLab.
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
 * \brief DS277Xg driver wrap implementation.
 *
 * \author Lucas Zacchi <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2022/07/12
 *
 * \addtogroup ds277xg_wrap
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include "ds277Xg_wrap.h"

int __wrap_ds277Xg_init(ds277Xg_config_t *config)
{
    return mock_type(int);
}

int __wrap_ds277Xg_set_battery_to_initial_state(ds277Xg_config_t *config)
{
    return mock_type(int);
}

int __wrap_ds277Xg_enable_charge(ds277Xg_config_t *config)
{
    return mock_type(int);
}

int __wrap_ds277Xg_enable_discharge(ds277Xg_config_t *config)
{
    return mock_type(int);
}

int __wrap_ds277Xg_disable_charge(ds277Xg_config_t *config)
{
    return mock_type(int);
}

int __wrap_ds277Xg_disable_discharge(ds277Xg_config_t *config)
{
    return mock_type(int);
}

int __wrap_ds277Xg_read_voltage_raw(ds277Xg_config_t *config, int16_t *voltage_raw, uint8_t battery_select)
{
    return mock_type(int);
}

int16_t __wrap_ds277Xg_voltage_raw_to_mv(int16_t raw)
{
    return mock_type(int);
}

int __wrap_ds277Xg_read_voltage_mv(ds277Xg_config_t *config, int16_t *voltage_mv, uint8_t battery_select)
{
    *voltage_mv = mock_type(int16_t);
    check_expected(battery_select);
    return mock_type(int);
}

int __wrap_ds277Xg_read_temperature_raw(ds277Xg_config_t *config, int16_t *temp_raw)
{
    return mock_type(int);
}

uint16_t __wrap_ds277Xg_temperature_raw_to_kelvin(int16_t raw)
{
    return mock_type(int);
}

int __wrap_ds277Xg_read_temperature_kelvin(ds277Xg_config_t *config, uint16_t *temp_kelvin)
{
    *temp_kelvin = mock_type(uint16_t);
    return mock_type(int);
}

int __wrap_ds277Xg_read_current_raw(ds277Xg_config_t *config, int16_t *current_raw, bool read_average)
{
    return mock_type(int);
}

int16_t __wrap_ds277Xg_current_raw_to_ma(int16_t raw)
{
    return mock_type(int);
}

int __wrap_ds277Xg_read_current_ma(ds277Xg_config_t *config, int16_t *current_ma, bool read_average)
{
    check_expected(read_average);
    *current_ma = mock_type(int16_t);
    return mock_type(int);
}

int __wrap_ds277Xg_write_accumulated_current_raw(ds277Xg_config_t *config, uint16_t acc_current_raw)
{
    return mock_type(int);
}

uint16_t __wrap_ds277Xg_accumulated_current_mah_to_raw(uint16_t mah)
{
    return mock_type(int);
}

int __wrap_ds277Xg_write_accumulated_current_mah(ds277Xg_config_t *config, uint16_t acc_current_mah)
{
    return mock_type(int);
}

int __wrap_ds277Xg_write_accumulated_current_max_value(ds277Xg_config_t *config)
{
    return mock_type(int);
}

int __wrap_ds277Xg_read_accumulated_current_raw(ds277Xg_config_t *config, uint16_t *acc_current_raw)
{
    return mock_type(int);
}

uint16_t __wrap_ds277Xg_accumulated_current_raw_to_mah(uint16_t raw)
{
    return mock_type(int);
}

int __wrap_ds277Xg_read_accumulated_current_mah(ds277Xg_config_t *config, uint16_t *acc_current_mah)
{
    return mock_type(int);
}

int __wrap_ds277Xg_write_cycle_counter(ds277Xg_config_t *config, uint16_t cycles)
{
    return mock_type(int);
}

int __wrap_ds277Xg_read_cycle_counter(ds277Xg_config_t *config, uint16_t *cycles)
{
    return mock_type(int);
}

int __wrap_ds277Xg_write_data(ds277Xg_config_t *config, uint8_t *data, uint16_t len)
{
    return mock_type(int);
}

int __wrap_ds277Xg_read_data(ds277Xg_config_t *config, uint8_t target_reg, uint8_t *data, uint16_t len)
{
    return mock_type(int);
}

/** \} End of ds277xg_wrap group */
