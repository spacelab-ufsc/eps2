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
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
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
#include <drivers/adc/adc.h>
#include <drivers/ads1248/ads1248.h>

#define ADS1248_POWER_DOWN_PIN 0
#define ADS1248_POWER_DOWN_CMD 1

#define GPIO_PORT_P8 8

#define TEMP_SENSOR_REF_VOLTAGE 3.3
#define TEMP_SENSOR_ADC_PORT ADC_PORT_0

#define TEMP_SENSOR_ADC_MIN_VAL 0
#define TEMP_SENSOR_ADC_MAX_VAL 0xFFF /* 12-bit precision = 0xFFF */
#define TEMP_SENSOR_ADC_MREF_VAL 6.5999999
#define TEMP_SENSOR_ADC_NREF_VAL 1949.0
#define TEMP_SENSOR_MIN_VAL_C (-273)
#define TEMP_SENSOR_MAX_VAL_C 358
#define TEMP_SENSOR_MIN_VAL_K 0
#define TEMP_SENSOR_MAX_VAL_K (TEMP_SENSOR_MAX_VAL_C + 273)

static void temp_sensor_init_test(void **state)
{
    // ads1248_init
    // will_return(__wrap_ads1248_init, 1);

    expect_value(__wrap_adc_init, port, TEMP_SENSOR_ADC_PORT);
    will_return(__wrap_adc_init, 1);
    assert_int_equal(temp_sensor_init(), -1);

    /* Calls to temp_mcu_read_c mock function */
    expect_value(__wrap_adc_read, port, TEMP_SENSOR_ADC_PORT);
    will_return(__wrap_adc_read, 0);
    will_return(__wrap_adc_read, 0);
    will_return(__wrap_adc_temp_get_mref, TEMP_SENSOR_ADC_MREF_VAL);
    will_return(__wrap_adc_temp_get_nref, TEMP_SENSOR_ADC_NREF_VAL);
    /* --- */

    expect_value(__wrap_adc_init, port, TEMP_SENSOR_ADC_PORT);
    will_return(__wrap_adc_init, 0);
    will_return(__wrap_ads1248_init, 1);
    assert_int_equal(temp_sensor_init(), -1);

    /* Calls to temp_mcu_read_c mock function */
    expect_value(__wrap_adc_read, port, TEMP_SENSOR_ADC_PORT);
    will_return(__wrap_adc_read, 0);
    will_return(__wrap_adc_read, 0);
    will_return(__wrap_adc_temp_get_mref, TEMP_SENSOR_ADC_MREF_VAL);
    will_return(__wrap_adc_temp_get_nref, TEMP_SENSOR_ADC_NREF_VAL);
    /* --- */

    expect_value(__wrap_adc_init, port, TEMP_SENSOR_ADC_PORT);
    will_return(__wrap_adc_init, 0);
    will_return(__wrap_ads1248_init, 0);
    assert_return_code(temp_sensor_init(), 0);
}

static void temp_sensor_suspend_test(void **state)
{
    /* Initializing config parameters */
    temp_sensor_t config;
    config.spi_port = TEMP_SENSOR_SPI_PORT;
    config.spi_config.mode = TEMP_SENSOR_SPI_MODE;
    config.spi_config.speed_hz = TEMP_SENSOR_SPI_SPEED_HZ;
    config.start_pin = TEMP_SENSOR_START_PIN;
    config.spi_cs = TEMP_SENSOR_SPI_CS;
    config.reset_pin = TEMP_SENSOR_RESET_PIN;

    temp_sensor_power_down_t mode_pin = ADS1248_POWER_DOWN_PIN; // expands to 0
    temp_sensor_power_down_t mode_cmd = ADS1248_POWER_DOWN_CMD; // expands to 1

    /* mode = 0 */
    expect_value(__wrap_ads1248_set_powerdown_mode, mode, mode_pin);

    will_return(__wrap_ads1248_set_powerdown_mode, -1);           // spi_port
    will_return(__wrap_ads1248_set_powerdown_mode, GPIO_PORT_P8); // start_pin invalidated
    will_return(__wrap_ads1248_set_powerdown_mode, 0);            // return code

    assert_return_code(temp_sensor_suspend(&config, mode_pin), 0);
    assert_int_equal(config.start_pin, GPIO_PORT_P8);

    /* If mode != 0: power-down by command */
    expect_value(__wrap_ads1248_set_powerdown_mode, mode, mode_cmd);

    will_return(__wrap_ads1248_set_powerdown_mode, GPIO_PORT_P8); // spi_port
    will_return(__wrap_ads1248_set_powerdown_mode, -1);           // start_pin invalidated
    will_return(__wrap_ads1248_set_powerdown_mode, 0);            // return code

    assert_return_code(temp_sensor_suspend(&config, mode_cmd), 0);
    assert_int_equal(config.spi_port, GPIO_PORT_P8);
}

static void temp_mcu_read_raw_test(void **state)
{
    uint16_t i = 0;

    for (i = TEMP_SENSOR_ADC_MIN_VAL; i <= TEMP_SENSOR_ADC_MAX_VAL; ++i)
    {
        expect_value(__wrap_adc_read, port, TEMP_SENSOR_ADC_PORT);

        will_return(__wrap_adc_read, i);
        will_return(__wrap_adc_read, 0);

        uint16_t raw_temp = UINT16_MAX;

        int result = temp_mcu_read_raw(&raw_temp);

        assert_return_code(result, 0);
        assert_int_equal(raw_temp, i);
    }
}

static void temp_mcu_raw_to_c_test(void **state)
{
    uint16_t i = 0;

    for (i = TEMP_SENSOR_ADC_MIN_VAL; i <= TEMP_SENSOR_ADC_MAX_VAL; ++i)
    {
        will_return(__wrap_adc_temp_get_mref, TEMP_SENSOR_ADC_MREF_VAL);
        will_return(__wrap_adc_temp_get_nref, TEMP_SENSOR_ADC_NREF_VAL);

        int16_t temp_c = temp_mcu_raw_to_c(i);

        assert_in_range(temp_c + 300, TEMP_SENSOR_MIN_VAL_C + 300, TEMP_SENSOR_MAX_VAL_C + 300);
    }
}

static void temp_mcu_raw_to_k_test(void **state)
{
    uint16_t i = 0;

    for (i = TEMP_SENSOR_ADC_MIN_VAL; i <= TEMP_SENSOR_ADC_MAX_VAL; ++i)
    {
        will_return(__wrap_adc_temp_get_mref, TEMP_SENSOR_ADC_MREF_VAL);
        will_return(__wrap_adc_temp_get_nref, TEMP_SENSOR_ADC_NREF_VAL);

        assert_in_range(temp_mcu_raw_to_k(i), TEMP_SENSOR_MIN_VAL_K, TEMP_SENSOR_MAX_VAL_K);
    }
}

static void temp_mcu_read_c_test(void **state)
{
    uint16_t i = 0;

    for (i = TEMP_SENSOR_ADC_MIN_VAL; i <= TEMP_SENSOR_ADC_MAX_VAL; ++i)
    {
        expect_value(__wrap_adc_read, port, TEMP_SENSOR_ADC_PORT);

        will_return(__wrap_adc_read, i);
        will_return(__wrap_adc_read, 0);
        will_return(__wrap_adc_temp_get_mref, TEMP_SENSOR_ADC_MREF_VAL);
        will_return(__wrap_adc_temp_get_nref, TEMP_SENSOR_ADC_NREF_VAL);

        int16_t temp_c = INT16_MAX;

        int result = temp_mcu_read_c(&temp_c);

        assert_return_code(result, 0);
        assert_in_range(temp_c + 300, TEMP_SENSOR_MIN_VAL_C + 300, TEMP_SENSOR_MAX_VAL_C + 300);
    }
}

static void temp_mcu_read_k_test(void **state)
{
    uint16_t i = 0;

    for (i = TEMP_SENSOR_ADC_MIN_VAL; i <= TEMP_SENSOR_ADC_MAX_VAL; ++i)
    {
        expect_value(__wrap_adc_read, port, TEMP_SENSOR_ADC_PORT);

        will_return(__wrap_adc_read, i);
        will_return(__wrap_adc_read, 0);
        will_return(__wrap_adc_temp_get_mref, TEMP_SENSOR_ADC_MREF_VAL);
        will_return(__wrap_adc_temp_get_nref, TEMP_SENSOR_ADC_NREF_VAL);

        uint16_t temp_k = UINT16_MAX;

        int result = temp_mcu_read_k(&temp_k);

        assert_return_code(result, 0);
        assert_in_range(temp_k + 200, TEMP_SENSOR_MIN_VAL_K + 200, TEMP_SENSOR_MAX_VAL_K + 200);
    }
}

static void temp_rtd_read_raw_test(void **state)
{
    // TODO
}

static void temp_rtd_raw_to_c_test(void **state)
{
    // TODO: fix magic number TEMP_SENSOR_CONV
}

static void temp_rtd_raw_to_k_test(void **state)
{
    // TODO: fix magic number TEMP_SENSOR_CONV
}

static void temp_rtd_read_c_test(void **state)
{
    // TODO: fix magic number TEMP_SENSOR_CONV
}

static void temp_rtd_read_k_test(void **state)
{
    // TODO: fix magic number TEMP_SENSOR_CONV
}

int main(void)
{
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
        cmocka_unit_test(temp_rtd_read_k_test)};

    return cmocka_run_group_tests(temp_sensor_tests, NULL, NULL);
}
