/*
 * voltage_sensor_test.c
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
 * \brief Unit test of the Voltage Sensor device.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2021/09/06
 *
 * \defgroup voltage_sensor_unit_test Voltage Sensor
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

#include <devices/voltage_sensor/voltage_sensor.h>
#include <drivers/adc/adc.h>

static void voltage_sensor_init_test(void **state) {

}

static void voltage_sensor_raw_to_mv_test(void **state) {

}

static void voltage_sensor_read_test(void **state) {

}

int main(void) {
    const struct CMUnitTest voltage_sensor_tests[] = {
        cmocka_unit_test(voltage_sensor_init_test),
        cmocka_unit_test(voltage_sensor_raw_to_mv_test),
        cmocka_unit_test(voltage_sensor_read_test)
    };

    return cmocka_run_group_tests(voltage_sensor_tests, NULL, NULL);
}

/** \} End of voltage_sensor_unit_test group */
