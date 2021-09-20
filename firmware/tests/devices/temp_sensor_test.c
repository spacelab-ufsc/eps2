/*
 * temp_sensor_test.c
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
 * \brief Unit test of the Temp Sensor device.
 *
 * \author Lucas Zacchi de Medeiros <lzacchi@pm.me>
 *
 * \version 0.1.0
 *
 * \date 2021/09/06
 *
 * \defgroup leds_unit_test LEDs
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include <devices/temp_sensor/temp_sensor.h>
#include <drivers/ads1248/ads1248.h>
// #include <tests/mockups/ads1248_wrap/ads1248_wrap.h>

static void temp_sensor_init_test(void **state) {

}

static void temp_sensor_suspend_test(void **state) {

}

static void temp_mcu_read_raw_test(void **state) {

}

static void temp_mcu_raw_to_c_test(void **state) {

}

static void temp_mcu_raw_to_k_test(void **state) {

}

static void temp_mcu_read_c_test(void **state) {

}

static void temp_mcu_read_k_test(void **state) {

}

static void temp_rtd_read_raw_test(void **state) {

}

static void temp_rtd_raw_to_c_test(void **state) {

}

static void temp_rtd_raw_to_k_test(void **state) {

}

static void temp_rtd_read_c_test(void **state) {

}

static void temp_rtd_read_k_test(void **state) {

}

int main(void) {
    const struct CMUnitTest temp_sensor_tests[] = {
        cmocka_unit_test(temp_sensor_init_test),
        cmocka_unit_test(temp_sensor_suspend_test),
        cmocka_unit_test(temp_mcu_read_raw_test),
        cmocka_unit_test(temp_mcu_raw_to_c_test),
        cmocka_unit_test(temp_mcu_raw_to_k_test),
        cmocka_unit_test(temp_mcu_read_c_test),
        cmocka_unit_test(temp_mcu_read_k_test),
        cmocka_unit_test(temp_rtd_read_raw_test),
        cmocka_unit_test(temp_rtd_raw_to_c_test),
        cmocka_unit_test(temp_rtd_raw_to_k_test),
        cmocka_unit_test(temp_rtd_read_c_test),
        cmocka_unit_test(temp_rtd_read_k_test)
    };

    return cmocka_run_group_tests(temp_sensor_tests, NULL, NULL);
}
