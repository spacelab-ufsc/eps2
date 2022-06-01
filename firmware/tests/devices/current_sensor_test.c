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
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
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
#include <system/sys_log/sys_log.h>
#include <drivers/adc/adc.h>
#include <drivers/max9934/max9934.h>

#include <stdio.h>

#define PANNEL_MINUS_Y_CURRENT_SENSOR_ADC_PORT ADC_PORT_1
#define PANNEL_PLUS_X_CURRENT_SENSOR_ADC_PORT ADC_PORT_2
#define PANNEL_MINUS_X_CURRENT_SENSOR_ADC_PORT ADC_PORT_3
#define PANNEL_PLUS_Z_CURRENT_SENSOR_ADC_PORT ADC_PORT_4
#define PANNEL_MINUS_Z_CURRENT_SENSOR_ADC_PORT ADC_PORT_5
#define PANNEL_PLUS_Y_CURRENT_SENSOR_ADC_PORT ADC_PORT_6
#define EPS_BEACON_CURRENT_SENSOR_ADC_PORT ADC_PORT_7

#define CURRENT_SENSOR_RAW_READING_MIN 0
#define CURRENT_SENSOR_RAW_READING_MAX 100

static void current_sensor_init_test(void **state)
{
    will_return(__wrap_max9934_init, 0);
    assert_return_code(current_sensor_init(), 0);

    will_return(__wrap_max9934_init, 1);
    assert_int_equal(current_sensor_init(), 1);
}

static void current_sensor_raw_to_ma_test(void **state)
{
    adc_port_t port = PANNEL_MINUS_Y_CURRENT_SENSOR_ADC_PORT;
    for (uint16_t i = CURRENT_SENSOR_RAW_READING_MIN; i <= CURRENT_SENSOR_RAW_READING_MAX; ++i)
    {
        int ma_value = current_sensor_raw_to_ma(port, i);
        int expected_value = (uint16_t)(1000UL * (uint32_t)i * (ADC_VREF_MV / (ADC_RANGE * SP_CURRENT_SENSOR_RL_VALUE_KOHM * SP_CURRENT_SENSOR_GAIN * SP_CURRENT_SENSOR_RSENSE_VALUE_MOHM)));
        assert_int_equal(ma_value, expected_value);
    }
    /* EPS current sensor test */
    adc_port_t eps_port = EPS_BEACON_CURRENT_SENSOR_ADC_PORT;
    for (uint16_t i = CURRENT_SENSOR_RAW_READING_MIN; i <= CURRENT_SENSOR_RAW_READING_MAX; ++i)
    {
        int ma_value = current_sensor_raw_to_ma(eps_port, i);
        int expected_value = (uint16_t)(1000UL * (uint32_t)i * (ADC_VREF_MV / (ADC_RANGE * EPS_CURRENT_SENSOR_RL_VALUE_KOHM * EPS_CURRENT_SENSOR_GAIN * EPS_CURRENT_SENSOR_RSENSE_VALUE_MOHM)));
        assert_int_equal(ma_value, expected_value);
    }
}

static void current_sensor_read_test(void **state)
{
    uint16_t curr = 0;
    uint16_t raw_curr = 0;
    adc_port_t port = EPS_BEACON_CURRENT_SENSOR_ADC_PORT;

    will_return(__wrap_max9934_read, 1);
    will_return(__wrap_max9934_read, 1);

    assert_int_equal(current_sensor_read(port, &curr), -1);

    will_return(__wrap_max9934_read, 0);
    will_return(__wrap_max9934_read, 0);

    assert_return_code(current_sensor_read(port, &curr), 0);
}

int main(void)
{
    const struct CMUnitTest current_sensor_tests[] = {
        cmocka_unit_test(current_sensor_init_test),
        cmocka_unit_test(current_sensor_raw_to_ma_test),
        cmocka_unit_test(current_sensor_read_test),

    };

    return cmocka_run_group_tests(current_sensor_tests, NULL, NULL);
}

/** \} End of current_sensor_test group */
