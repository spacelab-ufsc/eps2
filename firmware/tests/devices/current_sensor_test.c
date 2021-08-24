/*
 * current_sensor_test.c
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
 * \brief Unit test of the Current Sensor device
 *
 * \author Lucas Zacchi de Medeiros <lzacchi@pm.me>
 *
 * \version 0.1.0
 *
 * \date 2021/08/23
 *
 * \defgroup current_sensor_test Current Sensor
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include <devices/current_sensor/current_sensor.h>
#include <tests/mockups/sys_log_wrap.h>
#include <tests/mockups/adc_wrap.h>
#include <tests/mockups/max9934_wrap.h>

static void current_sensor_init_test(void **state) {

}

static void current_sensor_raw_read_test(void **state) {

}

int main(void) {
    const struct CMUnitTest current_sensor_tests[] = {
        cmocka_unit_test(current_sensor_init_test),
        cmocka_unit_test(current_sensor_raw_read_test),
    };

    return cmocka_run_group_tests(current_sensor_tests, NULL, NULL);
}


/** \} End of current_sensor_test group */
