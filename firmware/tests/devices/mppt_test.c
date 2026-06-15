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
 * \author Ramon de Araujo Borba <ramonborba97@gmail.com>
 *
 * \version 0.4.0
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

#define MPPT_DUTY_CYCLE_INIT 50

static void mppt_init_test(void **state)
{

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

}

static void mppt_algorithm_channel_test(mppt_paramemters_t* channel)
{
    /*
     * Test case 0:
     * Power increase and previous step = INCREASE_STEP:
     * Next step = INCREASE_STEP
     */

    channel->pwr_meas.power = 10;
    channel->config.duty_cycle = MPPT_DUTY_CYCLE_INIT;
    channel->prev_step = INCREASE_STEP;

    /* Wrapper function calls needed by read_ch_power() */
    will_return(__wrap_current_sensor_read, 20);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_voltage_sensor_read, 1);
    will_return(__wrap_voltage_sensor_read, 0);

    will_return(__wrap_pwm_update, 0);

    assert_return_code(mppt_algorithm(channel->channel), 0);
    assert_int_equal(channel->pwr_meas.power, 20);
    assert_int_equal(channel->step, INCREASE_STEP);
    assert_int_equal(channel->config.duty_cycle, MPPT_DUTY_CYCLE_INIT + MPPT_DUTY_CYCLE_STEP);

    /*
     * Test case 1:
     * Power increase and previous step = DECREASE_STEP:
     * Next step = DECREASE_STEP
     */

    channel->pwr_meas.power = 10;
    channel->config.duty_cycle = MPPT_DUTY_CYCLE_INIT;
    channel->prev_step = DECREASE_STEP;

    /* Wrapper function calls needed by read_ch_power() */
    will_return(__wrap_current_sensor_read, 20);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_voltage_sensor_read, 1);
    will_return(__wrap_voltage_sensor_read, 0);

    will_return(__wrap_pwm_update, 0);

    assert_return_code(mppt_algorithm(channel->channel), 0);
    assert_int_equal(channel->pwr_meas.power, 20);
    assert_int_equal(channel->step, DECREASE_STEP);
    assert_int_equal(channel->config.duty_cycle, MPPT_DUTY_CYCLE_INIT - MPPT_DUTY_CYCLE_STEP);

    /*
     * Test case 2:
     * Power decrease and previous step = INCREASE_STEP:
     * Next step = DECREASE_STEP
     */

    channel->pwr_meas.power = 20;
    channel->config.duty_cycle = MPPT_DUTY_CYCLE_INIT;
    channel->prev_step = INCREASE_STEP;

    /* Wrapper function calls needed by read_ch_power() */
    will_return(__wrap_current_sensor_read, 10);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_voltage_sensor_read, 1);
    will_return(__wrap_voltage_sensor_read, 0);

    will_return(__wrap_pwm_update, 0);

    assert_return_code(mppt_algorithm(channel->channel), 0);
    assert_int_equal(channel->pwr_meas.power, 10);
    assert_int_equal(channel->step, DECREASE_STEP);
    assert_int_equal(channel->config.duty_cycle, MPPT_DUTY_CYCLE_INIT - MPPT_DUTY_CYCLE_STEP);

    /*
     * Test case 3:
     * Power decrease and previous step = DECREASE_STEP:
     * Next step = INCREASE_STEP
     */

    channel->pwr_meas.power = 20;
    channel->config.duty_cycle = MPPT_DUTY_CYCLE_INIT;
    channel->prev_step = DECREASE_STEP;

    /* Wrapper function calls needed by read_ch_power() */
    will_return(__wrap_current_sensor_read, 10);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_voltage_sensor_read, 1);
    will_return(__wrap_voltage_sensor_read, 0);

    will_return(__wrap_pwm_update, 0);

    assert_return_code(mppt_algorithm(channel->channel), 0);
    assert_int_equal(channel->pwr_meas.power, 10);
    assert_int_equal(channel->step, INCREASE_STEP);
    assert_int_equal(channel->config.duty_cycle, MPPT_DUTY_CYCLE_INIT + MPPT_DUTY_CYCLE_STEP);

    /*
     * Test case 4:
     * Power equals zero:
     * Next step = DECREASE_STEP
     */

    channel->pwr_meas.power = 20;
    channel->config.duty_cycle = MPPT_DUTY_CYCLE_INIT;
    channel->prev_step = INCREASE_STEP;
    channel->step = INCREASE_STEP;

    /* Wrapper function calls needed by read_ch_power() */
    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_voltage_sensor_read, 1);
    will_return(__wrap_voltage_sensor_read, 0);

    will_return(__wrap_pwm_update, 0);

    assert_return_code(mppt_algorithm(channel->channel), 0);
    assert_int_equal(channel->pwr_meas.power, 0);
    assert_int_equal(channel->step, DECREASE_STEP);
    assert_int_equal(channel->config.duty_cycle, MPPT_DUTY_CYCLE_INIT - MPPT_DUTY_CYCLE_STEP);

    /*
     * Test case 5:
     * Step = INCREASE_STEP and duty cycle at max value:
     * duty cycle = max value
     */

    channel->pwr_meas.power = 10;
    channel->config.duty_cycle = MPPT_MAX_DUTY_CYCLE;
    channel->prev_step = INCREASE_STEP;
    channel->step = INCREASE_STEP;

    /* Wrapper function calls needed by read_ch_power() */
    will_return(__wrap_current_sensor_read, 20);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_voltage_sensor_read, 1);
    will_return(__wrap_voltage_sensor_read, 0);

    will_return(__wrap_pwm_update, 0);

    assert_return_code(mppt_algorithm(channel->channel), 0);
    assert_int_equal(channel->pwr_meas.power, 20);
    assert_int_equal(channel->step, INCREASE_STEP);
    assert_int_equal(channel->config.duty_cycle, MPPT_MAX_DUTY_CYCLE);

    /*
     * Test case 6:
     * Step = DECREASE_STEP and duty cycle at min value:
     * duty cycle = min value
     */

    channel->pwr_meas.power = 10;
    channel->config.duty_cycle = MPPT_MIN_DUTY_CYCLE;
    channel->prev_step = DECREASE_STEP;
    channel->step = DECREASE_STEP;

    /* Wrapper function calls needed by read_ch_power() */
    will_return(__wrap_current_sensor_read, 20);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_current_sensor_read, 0);
    will_return(__wrap_current_sensor_read, 0);

    will_return(__wrap_voltage_sensor_read, 1);
    will_return(__wrap_voltage_sensor_read, 0);

    will_return(__wrap_pwm_update, 0);

    assert_return_code(mppt_algorithm(channel->channel), 0);
    assert_int_equal(channel->pwr_meas.power, 20);
    assert_int_equal(channel->step, DECREASE_STEP);
    assert_int_equal(channel->config.duty_cycle, MPPT_MIN_DUTY_CYCLE);
}

static void mppt_algorithm_ch0_test(void **state)
{

    extern mppt_paramemters_t mppt_channel_params[];

    mppt_paramemters_t* channel = &mppt_channel_params[MPPT_CONTROL_LOOP_CH_0 - 1];

    assert_int_equal(channel->channel, MPPT_CONTROL_LOOP_CH_0);

    mppt_algorithm_channel_test(channel);

}

static void mppt_algorithm_ch1_test(void **state)
{

    extern mppt_paramemters_t mppt_channel_params[];

    mppt_paramemters_t* channel = &mppt_channel_params[MPPT_CONTROL_LOOP_CH_1 - 1];

    assert_int_equal(channel->channel, MPPT_CONTROL_LOOP_CH_1);

    mppt_algorithm_channel_test(channel);

}

static void mppt_algorithm_ch2_test(void **state)
{

    extern mppt_paramemters_t mppt_channel_params[];

    mppt_paramemters_t* channel = &mppt_channel_params[MPPT_CONTROL_LOOP_CH_2 - 1];

    assert_int_equal(channel->channel, MPPT_CONTROL_LOOP_CH_2);

    mppt_algorithm_channel_test(channel);

}

int main(void)
{
    const struct CMUnitTest mppt_tests[] = {
        cmocka_unit_test(mppt_init_test),
        cmocka_unit_test(mppt_algorithm_ch0_test),
        cmocka_unit_test(mppt_algorithm_ch1_test),
        cmocka_unit_test(mppt_algorithm_ch2_test)};

    return cmocka_run_group_tests(mppt_tests, NULL, NULL);
}
/** \} End of mppt_test group */
