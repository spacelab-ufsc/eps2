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
#include <devices/heater/heater_on_off.h>
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

static void expect_heater_pwm_init(heater_channel_t channel)
{
    expect_value(__wrap_pwm_init, source, HEATER_CONTROL_LOOP_CH_SOURCE);
    expect_value(__wrap_pwm_init, port, channel == HEATER_CONTROL_LOOP_CH_0 ? HEATER_ACTUATOR_CH_0 : HEATER_ACTUATOR_CH_1);
    will_return(__wrap_pwm_init, 0);
}

static void assert_float_near(float actual, float expected, float tolerance)
{
    assert_true(actual >= (expected - tolerance));
    assert_true(actual <= (expected + tolerance));
}

/* =========================================================
 * Initialization tests
 * ========================================================= */

static void
heater_init_test(void **state)
{
    /* Expect success */
    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    assert_return_code(heater_init(HEATER_CONTROL_LOOP_CH_0), 0);

    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_1);
    assert_return_code(heater_init(HEATER_CONTROL_LOOP_CH_1), 0);
}

static void heater_init_resets_integral_test(void **state)
{
    extern heater_pi_t heater_controller[];

    /* Initialize CH0 */
    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    heater_init(HEATER_CONTROL_LOOP_CH_0);

    /* Accumulate some integral by calling algorithm with positive error */
    heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 300.0f, 290.0f);
    heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 300.0f, 290.0f);

    assert_true(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral > 0.0f);

    /* Re-initialize and verify integral is reset */
    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    heater_init(HEATER_CONTROL_LOOP_CH_0);

    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral, 0.0f, 0.001f);
}

/* =========================================================
 * Proportional response tests
 * ========================================================= */

static void heater_algorithm_below_setpoint_test(void **state)
{
    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    heater_init(HEATER_CONTROL_LOOP_CH_0);

    /* error = 300 - 290 = 10, P = 1.0 * 10 = 10.0 */
    /* First call: integral starts at 0, provisional = 10 + 0 = 10 */
    /* Integration allowed: integral += 10 * 2.0 = 20.0 */
    /* output = 10 + 0.1 * 20 = 12.0 */
    float result = heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 300.0f, 290.0f);
    assert_float_near(result, 12.0f, 0.001f);
}

static void heater_algorithm_at_setpoint_test(void **state)
{
    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    heater_init(HEATER_CONTROL_LOOP_CH_0);

    /* error = 0, P = 0, integral unchanged at 0, output = 0 */
    assert_float_near(heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 300.0f, 300.0f), 0.0f, 0.001f);
}

static void heater_algorithm_above_setpoint_test(void **state)
{
    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    heater_init(HEATER_CONTROL_LOOP_CH_0);

    /* error = 300 - 310 = -10, P = -10 */
    /* provisional = -10 + 0 = -10, which is <= 0 AND error < 0 => do NOT integrate */
    /* output = -10 + 0 = -10, clamped to 0.0 */
    assert_float_near(heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 300.0f, 310.0f), 0.0f, 0.001f);
}

/* =========================================================
 * Output clamping tests
 * ========================================================= */

static void heater_algorithm_large_positive_error_clamps_to_max_test(void **state)
{
    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    heater_init(HEATER_CONTROL_LOOP_CH_0);

    /* error = 500, P = 500, provisional = 500 >= 100 AND error > 0 => no integration */
    /* output = 500 + 0 = 500, clamped to 100.0 */
    assert_float_near(heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 500.0f, 0.0f), 100.0f, 0.001f);
}

static void heater_algorithm_large_negative_error_clamps_to_min_test(void **state)
{
    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    heater_init(HEATER_CONTROL_LOOP_CH_0);

    /* error = -500, P = -500, provisional = -500 <= 0 AND error < 0 => no integration */
    /* output = -500 + 0 = -500, clamped to 0.0 */
    assert_float_near(heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 0.0f, 500.0f), 0.0f, 0.001f);
}

/* =========================================================
 * Integral accumulation tests
 * ========================================================= */

static void heater_algorithm_integral_accumulation_test(void **state)
{
    extern heater_pi_t heater_controller[];

    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    heater_init(HEATER_CONTROL_LOOP_CH_0);

    /* error = 5.0, Ts = 2.0 => each call adds 10.0 to integral */
    /* Call 1: integral = 0 + 5*2 = 10, output = 5 + 0.1*10 = 6.0 */
    float result1 = heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 300.0f, 295.0f);
    assert_float_near(result1, 6.0f, 0.001f);
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral, 10.0f, 0.001f);

    /* Call 2: integral = 10 + 5*2 = 20, output = 5 + 0.1*20 = 7.0 */
    float result2 = heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 300.0f, 295.0f);
    assert_float_near(result2, 7.0f, 0.001f);
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral, 20.0f, 0.001f);

    /* Call 3: integral = 20 + 5*2 = 30, output = 5 + 0.1*30 = 8.0 */
    float result3 = heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 300.0f, 295.0f);
    assert_float_near(result3, 8.0f, 0.001f);
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral, 30.0f, 0.001f);
}

/* =========================================================
 * Integral clamping tests
 * ========================================================= */

static void heater_algorithm_integral_clamping_test(void **state)
{
    extern heater_pi_t heater_controller[];

    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    heater_init(HEATER_CONTROL_LOOP_CH_0);

    /* Max integral is HEATER_OUTPUT_MAXIMUM / HEATER_PI_KI = 100.0 / 0.1 = 1000.0 */
    heater_controller[HEATER_CONTROL_LOOP_CH_0].integral = 2000.0f;
    
    /* Call algorithm with 0 error so P=0, no integration, just clamping */
    heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 300.0f, 300.0f);
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral, 1000.0f, 0.001f);

    /* Min integral is 0.0 (heat-only actuator, no negative integral) */
    heater_controller[HEATER_CONTROL_LOOP_CH_0].integral = -2000.0f;

    heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 300.0f, 300.0f);
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral, 0.0f, 0.001f);
}

/* =========================================================
 * Anti-windup tests
 * ========================================================= */

static void heater_algorithm_upper_anti_windup_test(void **state)
{
    extern heater_pi_t heater_controller[];

    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    heater_init(HEATER_CONTROL_LOOP_CH_0);

    /* Large positive error: error = 200, P = 200 */
    /* provisional = 200 + 0 = 200 >= 100 AND error > 0 => no integration */
    /* integral stays 0, output = 200 clamped to 100 */
    float result = heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 500.0f, 300.0f);
    assert_float_near(result, 100.0f, 0.001f);
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral, 0.0f, 0.001f);

    /* Call again: still saturated, integral must remain 0 */
    result = heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 500.0f, 300.0f);
    assert_float_near(result, 100.0f, 0.001f);
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral, 0.0f, 0.001f);
}

static void heater_algorithm_lower_anti_windup_test(void **state)
{
    extern heater_pi_t heater_controller[];

    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    heater_init(HEATER_CONTROL_LOOP_CH_0);

    /* Large negative error: error = -200, P = -200 */
    /* provisional = -200 + 0 = -200 <= 0 AND error < 0 => no integration */
    /* integral stays 0, output = -200 clamped to 0 */
    float result = heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 100.0f, 300.0f);
    assert_float_near(result, 0.0f, 0.001f);
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral, 0.0f, 0.001f);

    /* Call again: still saturated, integral must remain 0 */
    result = heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 100.0f, 300.0f);
    assert_float_near(result, 0.0f, 0.001f);
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral, 0.0f, 0.001f);
}

static void heater_algorithm_recovery_after_upper_saturation_test(void **state)
{
    extern heater_pi_t heater_controller[];

    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    heater_init(HEATER_CONTROL_LOOP_CH_0);

    /* Saturate high: error = 200, P = 200 >= 100 AND error > 0 => no integration */
    heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 500.0f, 300.0f);
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral, 0.0f, 0.001f);

    /* Now reverse: error = -5, P = -5 */
    /* provisional = -5 + 0 = -5 <= 0 AND error < 0 => do NOT integrate */
    /* output = -5 clamped to 0 */
    float result = heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 295.0f, 300.0f);
    assert_float_near(result, 0.0f, 0.001f);

    /* Now small positive error: error = 5, P = 5 */
    /* provisional = 5 + 0 = 5, not saturated => integrate: integral += 5*2 = 10 */
    /* output = 5 + 0.1*10 = 6.0 */
    result = heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 305.0f, 300.0f);
    assert_float_near(result, 6.0f, 0.001f);
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral, 10.0f, 0.001f);
}

/* =========================================================
 * Channel independence tests
 * ========================================================= */

static void heater_algorithm_independent_channels_test(void **state)
{
    extern heater_pi_t heater_controller[];

    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    heater_init(HEATER_CONTROL_LOOP_CH_0);

    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_1);
    heater_init(HEATER_CONTROL_LOOP_CH_1);

    /* Accumulate integral on CH0 only */
    heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 300.0f, 295.0f);
    heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 300.0f, 295.0f);

    /* CH0 integral should be 20.0 (5*2 + 5*2) */
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral, 20.0f, 0.001f);

    /* CH1 integral should still be 0.0 */
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_1].integral, 0.0f, 0.001f);

    /* Now operate CH1 */
    heater_algorithm(HEATER_CONTROL_LOOP_CH_1, 300.0f, 290.0f);

    /* CH1 integral = 10*2 = 20.0 */
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_1].integral, 20.0f, 0.001f);

    /* CH0 integral must remain at 20.0 (unchanged) */
    assert_float_near(heater_controller[HEATER_CONTROL_LOOP_CH_0].integral, 20.0f, 0.001f);
}

/* =========================================================
 * Repeated execution test
 * ========================================================= */

static void heater_algorithm_repeated_execution_test(void **state)
{
    expect_heater_pwm_init(HEATER_CONTROL_LOOP_CH_0);
    heater_init(HEATER_CONTROL_LOOP_CH_0);

    /* Repeatedly call with same small positive error */
    float result;
    for (int i = 0; i < 20; ++i)
    {
        result = heater_algorithm(HEATER_CONTROL_LOOP_CH_0, 300.0f, 295.0f);
        /* Output must always be in valid range */
        assert_true(result >= HEATER_OUTPUT_MINIMUM);
        assert_true(result <= HEATER_OUTPUT_MAXIMUM);
    }
}

/* =========================================================
 * Heater on/off tests (unchanged)
 * ========================================================= */

static void heater_on_off_lower_threshold_turns_on_test(void **state)
{
    assert_true(heater_on_off_algorithm(HEATER_CONTROL_LOOP_CH_0, TEMP_LIMIT_MINIMUM));
}

static void heater_on_off_upper_threshold_turns_off_test(void **state)
{
    assert_false(heater_on_off_algorithm(HEATER_CONTROL_LOOP_CH_0, TEMP_LIMIT_MAXIMUM));
}

static void heater_on_off_between_thresholds_remains_on_test(void **state)
{
    assert_true(heater_on_off_algorithm(HEATER_CONTROL_LOOP_CH_0, TEMP_LIMIT_MINIMUM));
    assert_true(heater_on_off_algorithm(HEATER_CONTROL_LOOP_CH_0, (TEMP_LIMIT_MINIMUM + TEMP_LIMIT_MAXIMUM) / 2));
}

static void heater_on_off_between_thresholds_remains_off_test(void **state)
{
    assert_false(heater_on_off_algorithm(HEATER_CONTROL_LOOP_CH_0, TEMP_LIMIT_MAXIMUM));
    assert_false(heater_on_off_algorithm(HEATER_CONTROL_LOOP_CH_0, (TEMP_LIMIT_MINIMUM + TEMP_LIMIT_MAXIMUM) / 2));
}

static void heater_on_off_channels_keep_independent_state_test(void **state)
{
    assert_true(heater_on_off_algorithm(HEATER_CONTROL_LOOP_CH_0, TEMP_LIMIT_MINIMUM));
    assert_false(heater_on_off_algorithm(HEATER_CONTROL_LOOP_CH_1, TEMP_LIMIT_MAXIMUM));

    assert_true(heater_on_off_algorithm(HEATER_CONTROL_LOOP_CH_0, (TEMP_LIMIT_MINIMUM + TEMP_LIMIT_MAXIMUM) / 2));
    assert_false(heater_on_off_algorithm(HEATER_CONTROL_LOOP_CH_1, (TEMP_LIMIT_MINIMUM + TEMP_LIMIT_MAXIMUM) / 2));
}

/* =========================================================
 * Sensor and actuator tests (unchanged)
 * ========================================================= */

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
        /* Initialization */
        cmocka_unit_test(heater_init_test),
        cmocka_unit_test(heater_init_resets_integral_test),
        /* Proportional response */
        cmocka_unit_test(heater_algorithm_below_setpoint_test),
        cmocka_unit_test(heater_algorithm_at_setpoint_test),
        cmocka_unit_test(heater_algorithm_above_setpoint_test),
        /* Output clamping */
        cmocka_unit_test(heater_algorithm_large_positive_error_clamps_to_max_test),
        cmocka_unit_test(heater_algorithm_large_negative_error_clamps_to_min_test),
        /* Integral accumulation */
        cmocka_unit_test(heater_algorithm_integral_accumulation_test),
        cmocka_unit_test(heater_algorithm_integral_clamping_test),
        /* Anti-windup */
        cmocka_unit_test(heater_algorithm_upper_anti_windup_test),
        cmocka_unit_test(heater_algorithm_lower_anti_windup_test),
        cmocka_unit_test(heater_algorithm_recovery_after_upper_saturation_test),
        /* Channel independence */
        cmocka_unit_test(heater_algorithm_independent_channels_test),
        /* Repeated execution */
        cmocka_unit_test(heater_algorithm_repeated_execution_test),
        /* On/off controller (unchanged) */
        cmocka_unit_test(heater_on_off_lower_threshold_turns_on_test),
        cmocka_unit_test(heater_on_off_upper_threshold_turns_off_test),
        cmocka_unit_test(heater_on_off_between_thresholds_remains_on_test),
        cmocka_unit_test(heater_on_off_between_thresholds_remains_off_test),
        cmocka_unit_test(heater_on_off_channels_keep_independent_state_test),
        /* Sensor and actuator */
        cmocka_unit_test(heater_get_sensor_test),
        cmocka_unit_test(heater_set_actuator_test),
    };

    return cmocka_run_group_tests(heater_tests, NULL, NULL);
}
/** \} End of heater_test group */
