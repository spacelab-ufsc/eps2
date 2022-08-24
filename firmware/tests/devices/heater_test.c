/*
 * heater_test.c
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
 * \brief Unit test of the Heater device
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2022/05/09
 *
 * \defgroup heater_test Heater
 * \ingroup tests
 * \{
 */

#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include <devices/heater/heater.h>
#include <devices/temp_sensor/temp_sensor.h>
#include <system/sys_log/sys_log.h>

#define HEATER_SETPOINT 15.0
#define HEATER_MESUREMENT 150.0

#define HEATER_TEMPERATURE_MIN 0
#define HEATER_TEMPERATURE_MAX 500

#define HEATER_CONTROL_LOOP_CH_SOURCE TIMER_A1 /**< MPPT control loop channels source. */
#define HEATER_CONTROL_LOOP_CH_0 0             /**< MPPT control loop channel 0. */
#define HEATER_CONTROL_LOOP_CH_1 1             /**< MPPT voltage sensor for channel 0. */
#define HEATER_ACTUATOR_CH_0 PWM_PORT_1
#define HEATER_ACTUATOR_CH_1 PWM_PORT_2
#define HEATER_SENSOR_CH_0 TEMP_SENSOR_RTD_CH_6
#define HEATER_SENSOR_CH_1 TEMP_SENSOR_RTD_CH_2
#define HEATER_SENSOR_BOARD TEMP_SENSOR_RTD_CH_3

static void
heater_init_test(void **state)
{
    /* Expect success */
    expect_value(__wrap_pwm_init, source, HEATER_CONTROL_LOOP_CH_SOURCE);
    expect_value(__wrap_pwm_init, port, HEATER_ACTUATOR_CH_0);

    will_return(__wrap_pwm_init, 0);

    expect_value(__wrap_pwm_init, source, HEATER_CONTROL_LOOP_CH_SOURCE);
    expect_value(__wrap_pwm_init, port, HEATER_ACTUATOR_CH_1);

    will_return(__wrap_pwm_init, 0);

    assert_return_code(heater_init(), 0);
}

static void heater_algorithm_test(void **state)
{
    expect_value(__wrap_pwm_init, source, HEATER_CONTROL_LOOP_CH_SOURCE);
    expect_value(__wrap_pwm_init, port, HEATER_ACTUATOR_CH_0);

    will_return(__wrap_pwm_init, 0);

    expect_value(__wrap_pwm_init, source, HEATER_CONTROL_LOOP_CH_SOURCE);
    expect_value(__wrap_pwm_init, port, HEATER_ACTUATOR_CH_1);

    will_return(__wrap_pwm_init, 0);

    heater_init();

    for (int i = 0; i < 10; ++i)
    {
        assert_in_range(heater_algorithm(HEATER_SETPOINT, HEATER_MESUREMENT), -1000.0, 1000.0);
    }
}

static void heater_get_sensor_test(void **state)
{
    heater_channel_t ch_0 = HEATER_CONTROL_LOOP_CH_0;
    heater_channel_t ch_1 = HEATER_CONTROL_LOOP_CH_1;

    for (temperature_t i = HEATER_TEMPERATURE_MIN; i <= HEATER_TEMPERATURE_MAX; ++i)
    {
        will_return(__wrap_temp_rtd_read_k, 0);
        assert_return_code(heater_get_sensor(ch_0, &i), 0);

        will_return(__wrap_temp_rtd_read_k, 0);
        assert_return_code(heater_get_sensor(ch_1, &i), 0);
    }
}

static void heater_set_actuator_test(void **state)
{
    heater_channel_t ch_0 = HEATER_CONTROL_LOOP_CH_0;
    heater_channel_t ch_1 = HEATER_CONTROL_LOOP_CH_1;

    expect_value(__wrap_pwm_stop, source, HEATER_CONTROL_LOOP_CH_SOURCE);
    expect_value(__wrap_pwm_stop, port, HEATER_ACTUATOR_CH_0);

    will_return(__wrap_pwm_stop, 0);
    assert_return_code(heater_set_actuator(ch_0, 0), 0);

    will_return(__wrap_pwm_update, 0);
    assert_return_code(heater_set_actuator(ch_0, 3.14), 0);

    expect_value(__wrap_pwm_stop, source, HEATER_CONTROL_LOOP_CH_SOURCE);
    expect_value(__wrap_pwm_stop, port, HEATER_ACTUATOR_CH_1);

    will_return(__wrap_pwm_stop, 0);

    assert_return_code(heater_set_actuator(ch_1, 0), 0);

    will_return(__wrap_pwm_update, 0);

    assert_return_code(heater_set_actuator(ch_1, 3.14), 0);
}

int main(void)
{
    const struct CMUnitTest heater_tests[] = {
        cmocka_unit_test(heater_init_test),
        cmocka_unit_test(heater_algorithm_test),
        cmocka_unit_test(heater_get_sensor_test),
        cmocka_unit_test(heater_set_actuator_test),
    };

    return cmocka_run_group_tests(heater_tests, NULL, NULL);
}
/** \} End of heater_test group */
