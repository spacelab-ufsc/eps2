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

#define VOLTAGE_SENSOR_ADC_MIN_VAL 0
#define VOLTAGE_SENSOR_ADC_MAX_VAL 0xFFF /* 12-bit precision = 0xFFF */
#define VOLTAGE_SENSOR_MIN_VAL_MV 0
#define VOLTAGE_SENSOR_MAX_VAL_MV_DIV1 (uint16_t)(1000.0 * VOLTAGE_SENSOR_ADC_MAX_VAL * ADC_VREF_MV * VOLTAGE_SENSOR_DIV_1 / ADC_RANGE)
#define VOLTAGE_SENSOR_MAX_VAL_MV_DIV2 (uint16_t)(1000.0 * VOLTAGE_SENSOR_ADC_MAX_VAL * ADC_VREF_MV * VOLTAGE_SENSOR_DIV_2 / ADC_RANGE)

static void voltage_sensor_init_test(void **state)
{
    expect_value(__wrap_adc_init, port, (adc_port_t){0});
    will_return(__wrap_adc_init, 1);
    assert_int_equal(voltage_sensor_init(), -1);

    expect_value(__wrap_adc_init, port, (adc_port_t){0});
    will_return(__wrap_adc_init, 0);
    assert_return_code(voltage_sensor_init(), 0);
}

static void voltage_sensor_raw_to_mv_test(void **state)
{
    for (uint16_t i = VOLTAGE_SENSOR_ADC_MIN_VAL; i <= VOLTAGE_SENSOR_ADC_MAX_VAL; ++i)
    {
        // port = TOTAL_SOLAR_PANNELS_VOLTAGE_SENSOR_ADC_PORT
        uint16_t result = voltage_sensor_raw_to_mv(TOTAL_SOLAR_PANNELS_VOLTAGE_SENSOR_ADC_PORT, i);
        assert_in_range(result, VOLTAGE_SENSOR_MIN_VAL_MV, VOLTAGE_SENSOR_MAX_VAL_MV_DIV1);
        // port = MAIN_POWER_BUS_VOLTAGE_SENSOR_ADC_PORT
        uint16_t result_1 = voltage_sensor_raw_to_mv(MAIN_POWER_BUS_VOLTAGE_SENSOR_ADC_PORT, i);
        assert_in_range(result_1, VOLTAGE_SENSOR_MIN_VAL_MV, VOLTAGE_SENSOR_MAX_VAL_MV_DIV1);

        // else
        uint16_t result_2 = voltage_sensor_raw_to_mv(ADC_PORT_11, i);
        assert_in_range(result_2, VOLTAGE_SENSOR_MIN_VAL_MV, VOLTAGE_SENSOR_MAX_VAL_MV_DIV2);
    }
}

static void voltage_sensor_read_test(void **state)
{
    // [in,out] uint16_t *volt
    uint16_t volt_fail = 0;
    uint16_t volt_1 = 0;
    uint16_t volt_2 = 0;

    int min = VOLTAGE_SENSOR_MIN_VAL_MV;
    int max = VOLTAGE_SENSOR_MAX_VAL_MV_DIV1 / 10; // small sample

    expect_value(__wrap_adc_read, port, TOTAL_SOLAR_PANNELS_VOLTAGE_SENSOR_ADC_PORT);
    will_return(__wrap_adc_read, 1024);
    will_return(__wrap_adc_read, 1);
    assert_int_equal(voltage_sensor_read(TOTAL_SOLAR_PANNELS_VOLTAGE_SENSOR_ADC_PORT, &volt_fail), -1);

    // div 1 test
    for (uint16_t i = min; i <= max; ++i)
    {
        expect_value(__wrap_adc_read, port, TOTAL_SOLAR_PANNELS_VOLTAGE_SENSOR_ADC_PORT);
        will_return(__wrap_adc_read, 1024);
        will_return(__wrap_adc_read, 0);
        int result = voltage_sensor_read(TOTAL_SOLAR_PANNELS_VOLTAGE_SENSOR_ADC_PORT, &volt_1);
        assert_return_code(result, 0);
        assert_in_range(volt_1, min, max);
    }

    // div 2 test
    for (uint16_t i = min; i <= max; ++i)
    {
        expect_value(__wrap_adc_read, port, ADC_PORT_11);
        will_return(__wrap_adc_read, 1024);
        will_return(__wrap_adc_read, 0);
        int result = voltage_sensor_read(ADC_PORT_11, &volt_2);
        assert_return_code(result, 0);
        assert_in_range(volt_2, VOLTAGE_SENSOR_MIN_VAL_MV, VOLTAGE_SENSOR_MAX_VAL_MV_DIV2);
    }
}

int main(void)
{
    const struct CMUnitTest voltage_sensor_tests[] = {
        cmocka_unit_test(voltage_sensor_init_test),
        cmocka_unit_test(voltage_sensor_raw_to_mv_test),
        cmocka_unit_test(voltage_sensor_read_test)};

    return cmocka_run_group_tests(voltage_sensor_tests, NULL, NULL);
}

/** \} End of voltage_sensor_unit_test group */
