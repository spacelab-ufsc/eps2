/*
 * battery_monitor_test.c
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
 * \brief Unit test of the Battery Monitor device
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 * \author Ramon de Araujo Borba <ramonborba07@gmail.com>
 *
 * \version 0.4.0
 *
 * \date 2022/07/12
 *
 * \defgroup battery_monitor_test Battery Monitor
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include <devices/battery_monitor/battery_monitor.h>
#include <drivers/ds277Xg/ds277Xg.h>

#define CELL_VOLTAGE_MIN -300
#define CELL_VOLTAGE_MAX 300
#define BATTERY_VOLTAGE_MIN 0

#define BATTERY_TEMP_KELVIN_MIN 0
#define BATTERY_TEMP_KELVIN_MAX 500

static void battery_monitor_init_test(void **state)
{
    will_return(__wrap_ds277Xg_init, 0);
    assert_return_code(battery_monitor_init(), 0);
}

static void bm_get_voltage_test(void **state)
{
    uint16_t voltage = 0;

    for (int16_t i = BATTERY_VOLTAGE_MIN; i <= CELL_VOLTAGE_MAX; ++i)
    {
        // Cell 1
        expect_value(__wrap_ds277Xg_read_voltage_mv, battery_select, 1);
        will_return(__wrap_ds277Xg_read_voltage_mv, i);
        will_return(__wrap_ds277Xg_read_voltage_mv, 0);

        // Cell 2
        expect_value(__wrap_ds277Xg_read_voltage_mv, battery_select, 2);
        will_return(__wrap_ds277Xg_read_voltage_mv, i);
        will_return(__wrap_ds277Xg_read_voltage_mv, 0);

        assert_return_code(bm_get_voltage(&voltage), 0);
        assert_int_equal(voltage, 2 * i);
    }
}

static void bm_get_temperature_kelvin_test(void **state)
{
    uint16_t temp = 0;

    for (uint16_t i = 0; i <= BATTERY_TEMP_KELVIN_MAX; ++i)
    {
        will_return(__wrap_ds277Xg_read_temperature_kelvin, i);
        will_return(__wrap_ds277Xg_read_temperature_kelvin, 0);
        assert_return_code(bm_get_temperature_kelvin(&temp), 0);
        assert_int_equal(temp, i);
    }
}

static void bm_get_instantaneous_current_test(void **state)
{
    int16_t current = 0;
    expect_value(__wrap_ds277Xg_read_current_ma, read_average, false);
    will_return(__wrap_ds277Xg_read_current_ma, 0);
    will_return(__wrap_ds277Xg_read_current_ma, 0);
    assert_return_code(bm_get_instantaneous_current(&current), 0);
    assert_int_equal(current, 0);
}

static void bm_get_average_current_test(void **state)
{
    int16_t current = 0;
    expect_value(__wrap_ds277Xg_read_current_ma, read_average, true);
    will_return(__wrap_ds277Xg_read_current_ma, 0);
    will_return(__wrap_ds277Xg_read_current_ma, 0);
    assert_return_code(bm_get_average_current(&current), 0);
    assert_int_equal(current, 0);
}

static void bm_get_status_register_data_test(void **state)
{
    uint8_t data = 0;
    will_return(__wrap_ds277Xg_read_data, 0);
    assert_return_code(bm_get_status_register_data(&data), 0);
}

static void bm_get_protection_register_data_test(void **state)
{
    uint8_t data = 0;
    will_return(__wrap_ds277Xg_read_data, 0);
    assert_return_code(bm_get_protection_register_data(&data), 0);
}

static void bm_get_raac_mah_test(void **state)
{
    uint16_t data = 0;
    will_return(__wrap_ds277Xg_read_data, 0);

    assert_return_code(bm_get_raac_mah(&data), 0);
}

static void bm_get_rsac_mah_test(void **state)
{
    uint16_t data = 0;
    will_return(__wrap_ds277Xg_read_data, 0);
    assert_return_code(bm_get_rsac_mah(&data), 0);
}

static void bm_get_rarc_percent_test(void **state)
{
    uint8_t data = 0;
    will_return(__wrap_ds277Xg_read_data, 0);
    assert_return_code(bm_get_rarc_percent(&data), 0);
}

static void bm_get_rsrc_percent_test(void **state)
{
    uint8_t data = 0;
    will_return(__wrap_ds277Xg_read_data, 0);
    assert_return_code(bm_get_rsrc_percent(&data), 0);
}

static void bm_get_acc_current_mah_test(void **state)
{
    uint16_t data = 0;
    will_return(__wrap_ds277Xg_read_accumulated_current_mah, 0);
    assert_return_code(bm_get_acc_current_mah(&data), 0);
}

static void bm_get_full_capacity_ppm_test(void **state)
{
    uint32_t data = 0;
    will_return(__wrap_ds277Xg_read_data, 0);
    assert_return_code(bm_get_full_capacity_ppm(&data), 0);
}

static void bm_get_active_empty_capacity_ppm_test(void **state)
{
    uint32_t data = 0;
    will_return(__wrap_ds277Xg_read_data, 0);
    assert_return_code(bm_get_active_empty_capacity_ppm(&data), 0);
}

static void bm_get_standby_empty_capacity_ppm_test(void **state)
{
    uint32_t data = 0;
    will_return(__wrap_ds277Xg_read_data, 0);
    assert_return_code(bm_get_standby_empty_capacity_ppm(&data), 0);
}

int main(void)
{
    const struct CMUnitTest battery_monitor_tests[] = {
        cmocka_unit_test(battery_monitor_init_test),
        cmocka_unit_test(bm_get_voltage_test),
        cmocka_unit_test(bm_get_temperature_kelvin_test),
        cmocka_unit_test(bm_get_instantaneous_current_test),
        cmocka_unit_test(bm_get_average_current_test),
        cmocka_unit_test(bm_get_status_register_data_test),
        cmocka_unit_test(bm_get_protection_register_data_test),
        cmocka_unit_test(bm_get_raac_mah_test),
        cmocka_unit_test(bm_get_rsac_mah_test),
        cmocka_unit_test(bm_get_rarc_percent_test),
        cmocka_unit_test(bm_get_rsrc_percent_test),
        cmocka_unit_test(bm_get_acc_current_mah_test),
        cmocka_unit_test(bm_get_full_capacity_ppm_test),
        cmocka_unit_test(bm_get_active_empty_capacity_ppm_test),
        cmocka_unit_test(bm_get_standby_empty_capacity_ppm_test),
    };

    return cmocka_run_group_tests(battery_monitor_tests, NULL, NULL);
}

/** \} End of current_sensor_test group */
