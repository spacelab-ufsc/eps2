/*
 * mppt_test.c
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
 * \brief Unit test of the MPPT device
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2021/08/10
 *
 * \defgroup mppt_test MPPT
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include <devices/mppt/mppt.h>
#include <drivers/pwm/pwm.h>

/**
 * \brief MPPT algorithm constants.
 */
#define MPPT_DUTY_CYCLE_STEP 	1  	/**< PWM duty cycle step in % for the MPPT algorithm. */
#define MPPT_DUTY_CYCLE_INIT 	50 	/**< PWM initial duty cycle in % for the MPPT algorithm. */
#define MPPT_PERIOD_INIT 	4      	/**< PWM period (1/f) in us for the MPPT algorithm. */
#define MPPT_MIN_DUTY_CYCLE 	0   	/**< Minimum duty cycle allowed. */
#define MPPT_MAX_DUTY_CYCLE 	100 	/**< Maximum duty cycle allowed. */

static void mppt_init_test(void **state)
{
    extern mppt_config_t mppt_config;

    expect_value(__wrap_pwm_init, source, MPPT_CONTROL_LOOP_CH_SOURCE);
    expect_value(__wrap_pwm_init, port, MPPT_CONTROL_LOOP_CH_0);
    will_return(__wrap_pwm_init, 0);

    expect_value(__wrap_pwm_init, source, MPPT_CONTROL_LOOP_CH_SOURCE);
    expect_value(__wrap_pwm_init, port, MPPT_CONTROL_LOOP_CH_1);
    will_return(__wrap_pwm_init, 0);

    expect_value(__wrap_pwm_init, source, MPPT_CONTROL_LOOP_CH_SOURCE);
    expect_value(__wrap_pwm_init, port, MPPT_CONTROL_LOOP_CH_2);
    will_return(__wrap_pwm_init, 0);

    assert_return_code(mppt_init(), 0);

    assert_int_equal(mppt_config.period_us, MPPT_PERIOD_INIT);
    assert_int_equal(mppt_config.duty_cycle, MPPT_DUTY_CYCLE_INIT);
}

static void mppt_algorithm_test(void **state)
{
    extern mppt_config_t mppt_config;
    extern power_measurement_t power_measurement;
    extern duty_cycle_measurement_t duty_cycle_measurement;
    extern previous_values_t previous_values;

    int test_val;

    /*
     * Test case 0:
     * Power increase and duty cycle increased:
     * duty cycle increases
     */

    /* Information for get_duty_cycle() execution */
    previous_values.previous_power_ch_0 = 0;

    test_val = MPPT_DUTY_CYCLE_INIT;
    duty_cycle_measurement.duty_cycle = test_val;
    duty_cycle_measurement.previous_duty_cycle = 0;

    mppt_config.duty_cycle = test_val;

    /* Wrapper function calls needed by get_power() */
    will_return(__wrap_current_sensor_read, 1);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_voltage_sensor_read, 1);
    will_return(__wrap_voltage_sensor_read, 0);

    will_return(__wrap_pwm_update, 0);

    assert_return_code(mppt_algorithm(MPPT_CONTROL_LOOP_CH_0), 0);
    assert_int_equal(mppt_config.duty_cycle, test_val + MPPT_DUTY_CYCLE_STEP);

    /*
     * Test case 1:
     * Power increase and duty cycle decreased:
     * duty cycle decreases
     */

    previous_values.previous_power_ch_0 = 0;

    test_val = MPPT_DUTY_CYCLE_INIT;
    duty_cycle_measurement.duty_cycle = test_val;
    duty_cycle_measurement.previous_duty_cycle = MPPT_DUTY_CYCLE_INIT + 10;

    mppt_config.duty_cycle = test_val;

    /* Wrapper function calls needed by get_power() */
    will_return(__wrap_current_sensor_read, 1);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_voltage_sensor_read, 1);
    will_return(__wrap_voltage_sensor_read, 0);

    will_return(__wrap_pwm_update, 0);

    assert_return_code(mppt_algorithm(MPPT_CONTROL_LOOP_CH_0), 0);
    assert_int_equal(mppt_config.duty_cycle, test_val - MPPT_DUTY_CYCLE_STEP);

    /*
     * Test case 2:
     * Power decrease and duty cycle increased:
     * duty cycle decreases
     */

    previous_values.previous_power_ch_0 = 1;

    test_val = MPPT_DUTY_CYCLE_INIT;
    duty_cycle_measurement.previous_duty_cycle = 0;
    duty_cycle_measurement.duty_cycle = test_val;

    mppt_config.duty_cycle = test_val;

    /* Wrapper function calls needed by get_power() */
    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_voltage_sensor_read, 1);
    will_return(__wrap_voltage_sensor_read, 0);

    will_return(__wrap_pwm_update, 0);

    assert_return_code(mppt_algorithm(MPPT_CONTROL_LOOP_CH_0), 0);
    assert_int_equal(mppt_config.duty_cycle, test_val - MPPT_DUTY_CYCLE_STEP);

    /*
     * Test case 3:
     * Power decrease and duty cycle decreased:
     * duty cycle increases
     */

    previous_values.previous_power_ch_0 = 1;

    test_val = MPPT_DUTY_CYCLE_INIT;
    duty_cycle_measurement.previous_duty_cycle = MPPT_DUTY_CYCLE_INIT + 10;
    duty_cycle_measurement.duty_cycle = test_val;

    mppt_config.duty_cycle = test_val;

    /* Wrapper function calls needed by get_power() */
    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_voltage_sensor_read, 1);
    will_return(__wrap_voltage_sensor_read, 0);

    will_return(__wrap_pwm_update, 0);

    assert_return_code(mppt_algorithm(MPPT_CONTROL_LOOP_CH_0), 0);

    assert_int_equal(mppt_config.duty_cycle, test_val + MPPT_DUTY_CYCLE_STEP);
}

static void get_power_test(void **state)
{
    mppt_channel_t channel_0 = MPPT_CONTROL_LOOP_CH_0;
    mppt_channel_t channel_1 = MPPT_CONTROL_LOOP_CH_1;
    mppt_channel_t channel_2 = MPPT_CONTROL_LOOP_CH_2;

    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_voltage_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_voltage_sensor_read, 0);

    assert_return_code(get_power(channel_0), 0);

    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_voltage_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_voltage_sensor_read, 0);

    assert_return_code(get_power(channel_1), 0);

    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_voltage_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_voltage_sensor_read, 0);

    assert_return_code(get_power(channel_2), 0);
}

static void get_duty_cycle_test(void **state)
{
    mppt_channel_t channel_0 = MPPT_CONTROL_LOOP_CH_0;
    mppt_channel_t channel_1 = MPPT_CONTROL_LOOP_CH_1;
    mppt_channel_t channel_2 = MPPT_CONTROL_LOOP_CH_2;

    extern duty_cycle_measurement_t duty_cycle_measurement;
    extern mppt_config_t mppt_config;
    extern previous_values_t previous_values;

    // mppt_config.duty_cycle = 1;
    previous_values.previous_duty_cycle_ch_0 = 0;

    get_duty_cycle(channel_0);

    assert_int_equal(duty_cycle_measurement.duty_cycle, mppt_config.duty_cycle);
    assert_int_equal(duty_cycle_measurement.previous_duty_cycle, previous_values.previous_duty_cycle_ch_0);
}

static void increase_duty_cycle_test(void **state)
{
    mppt_channel_t channel_0 = MPPT_CONTROL_LOOP_CH_0;
    mppt_channel_t channel_1 = MPPT_CONTROL_LOOP_CH_1;
    mppt_channel_t channel_2 = MPPT_CONTROL_LOOP_CH_2;

    extern mppt_config_t mppt_config;

    int test_val = MPPT_MAX_DUTY_CYCLE + 10;
    mppt_config.duty_cycle = test_val;

    will_return(__wrap_pwm_update, 0);

    assert_return_code(increase_duty_cycle(channel_0), 0);
    assert_int_equal(mppt_config.duty_cycle, MPPT_MAX_DUTY_CYCLE);

    test_val = 50;
    mppt_config.duty_cycle = test_val;

    will_return(__wrap_pwm_update, 0);

    assert_return_code(increase_duty_cycle(channel_0), 0);

    assert_int_equal(mppt_config.duty_cycle, test_val + MPPT_DUTY_CYCLE_STEP);
}

static void decrease_duty_cycle_test(void **state)
{
    mppt_channel_t channel_0 = MPPT_CONTROL_LOOP_CH_0;
    mppt_channel_t channel_1 = MPPT_CONTROL_LOOP_CH_1;
    mppt_channel_t channel_2 = MPPT_CONTROL_LOOP_CH_2;

    extern mppt_config_t mppt_config;

    int test_val = MPPT_MIN_DUTY_CYCLE;
    mppt_config.duty_cycle = test_val;

    will_return(__wrap_pwm_update, 0);

    assert_return_code(decrease_duty_cycle(channel_0), 0);
    assert_int_equal(mppt_config.duty_cycle, MPPT_MIN_DUTY_CYCLE);

    test_val = 50;
    mppt_config.duty_cycle = test_val;

    will_return(__wrap_pwm_update, 0);

    assert_return_code(decrease_duty_cycle(channel_0), 0);

    assert_int_equal(mppt_config.duty_cycle, test_val - MPPT_DUTY_CYCLE_STEP);
}

int main(void)
{
    const struct CMUnitTest mppt_tests[] = {
        cmocka_unit_test(mppt_init_test),
        cmocka_unit_test(mppt_algorithm_test),
        cmocka_unit_test(get_power_test),
        cmocka_unit_test(get_duty_cycle_test),
        cmocka_unit_test(increase_duty_cycle_test),
        cmocka_unit_test(decrease_duty_cycle_test)};

    return cmocka_run_group_tests(mppt_tests, NULL, NULL);
}
/** \} End of mppt_test group */
