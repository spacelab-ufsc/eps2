/*
 * bat_manager_test.c
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
 * \brief Unit test of the Battery Manager device
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2022/06/15
 *
 * \defgroup bat_manager_test Battery Manager
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include <devices/bat_manager/bat_manager.h>
#include <drivers/ds2775g/ds2775g.h>
#include <system/sys_log/sys_log.h>

static void bat_manager_init_test(void **state)
{
    will_return(__wrap_ds2775g_init, 0);
    assert_return_code(bat_manager_init(), 0);

    will_return(__wrap_ds2775g_init, -1);
    assert_int_equal(bat_manager_init(), -1);
}

static void get_bat_voltage_test(void **state)
{
    bat_voltage_t bat_volt;

    /* Initializing bat_monitor_config structure */
    bat_monitor_config.protection_reg[0] = skip_address;
    bat_monitor_config.protection_reg[1] = write_data;
    bat_monitor_config.protection_reg[2] = protection_register;
    bat_monitor_config.protection_reg[3] = 0x03;
    bat_monitor_config.protector_threshold_reg[0] = skip_address;
    bat_monitor_config.protector_threshold_reg[1] = write_data;
    bat_monitor_config.protector_threshold_reg[2] = protector_threshold_register;
    bat_monitor_config.protector_threshold_reg[3] = 0x61;
    bat_monitor_config.status_reg[0] = skip_address;
    bat_monitor_config.status_reg[1] = write_data;
    bat_monitor_config.status_reg[2] = status_register;
    bat_monitor_config.status_reg[3] = 0x0;
    bat_monitor_config.control_reg[0] = skip_address;
    bat_monitor_config.control_reg[1] = write_data;
    bat_monitor_config.control_reg[2] = control_register;
    bat_monitor_config.control_reg[3] = 0x0C;
    bat_monitor_config.overcurrent_thresholds_reg[0] = skip_address;
    bat_monitor_config.overcurrent_thresholds_reg[1] = write_data;
    bat_monitor_config.overcurrent_thresholds_reg[2] = overcurrent_thresholds_register;
    bat_monitor_config.overcurrent_thresholds_reg[3] = 0x24;
    bat_monitor_config.current_gain_LSB_reg[0] = skip_address;
    bat_monitor_config.current_gain_LSB_reg[1] = write_data;
    bat_monitor_config.current_gain_LSB_reg[2] = current_gain_LSB_register;
    bat_monitor_config.current_gain_LSB_reg[3] = 0x00;

    bat_monitor_config.onewire_port = GPIO_PIN_69;
}

static void get_bat_current_test(void **state)
{
}

static void get_bat_charge_test(void **state)
{
}

static void get_bat_data_test(void **state)
{
}

int main(void)
{
    const struct CMUnitTest bat_manager_tests[] = {
        cmocka_unit_test(bat_manager_init_test),
        cmocka_unit_test(get_bat_voltage_test),
        cmocka_unit_test(get_bat_current_test),
        cmocka_unit_test(get_bat_charge_test),
        cmocka_unit_test(get_bat_data_test)};

    return cmocka_run_group_tests(bat_manager_tests, NULL, NULL);
}
