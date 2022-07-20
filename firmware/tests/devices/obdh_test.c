/*
 * obdh_test.c
 *
 * Copyright The EPS 2.0 Contributors.
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
 * \brief Unit test of the OBDH device.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.2.41
 *
 * \date 2021/09/15
 *
 * \defgroup obdh_unit_test OBDH
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include <devices/obdh/obdh.h>
#include <drivers/tca4311a/tca4311a.h>
#include <drivers/i2c_slave/i2c_slave.h>
#include <drivers/i2c/i2c.h>

static void obdh_init_test(void **state)
{
    /* Success case */
    expect_value(__wrap_tca4311a_init, en, true);
    will_return(__wrap_tca4311a_init, TCA4311A_READY);

    expect_value(__wrap_i2c_slave_init, port, I2C_PORT_2);
    expect_value(__wrap_i2c_slave_init, adr, EPS_SLAVE_ADDRESS);
    will_return(__wrap_i2c_slave_init, 0);

    will_return(__wrap_i2c_slave_enable, 0);

    assert_return_code(obdh_init(), 0);

    /* Fail 1 case */
    expect_value(__wrap_tca4311a_init, en, true);
    will_return(__wrap_tca4311a_init, 1);

    assert_int_equal(obdh_init(), -1);

    /* Fail 2 Case */
    expect_value(__wrap_tca4311a_init, en, true);
    will_return(__wrap_tca4311a_init, TCA4311A_READY);

    expect_value(__wrap_i2c_slave_init, port, I2C_PORT_2);
    expect_value(__wrap_i2c_slave_init, adr, EPS_SLAVE_ADDRESS);
    will_return(__wrap_i2c_slave_init, -1);

    assert_int_equal(obdh_init(), -1);

    /* Fail 3 Case */
    expect_value(__wrap_tca4311a_init, en, true);
    will_return(__wrap_tca4311a_init, TCA4311A_READY);

    expect_value(__wrap_i2c_slave_init, port, I2C_PORT_2);
    expect_value(__wrap_i2c_slave_init, adr, EPS_SLAVE_ADDRESS);
    will_return(__wrap_i2c_slave_init, 0);

    will_return(__wrap_i2c_slave_enable, 1);

    assert_int_equal(obdh_init(), -1);
}

static void obdh_decode_test(void **state)
{
    uint8_t adr;
    uint32_t val;
    uint8_t cmd = -2;

    uint8_t buf[I2C_RX_BUFFER_MAX_SIZE] = {0};
    buf[0] = 155;
    buf[1] = 11;
    buf[2] = 12;
    buf[3] = 13;
    buf[4] = 14;

    // case OBDH_COMMAND_WRITE_SIZE
    will_return(__wrap_i2c_slave_read, buf);
    will_return(__wrap_i2c_slave_read, 6);
    will_return(__wrap_i2c_slave_read, 0);

    int result = obdh_decode(&adr, &val, &cmd);
}

static void obdh_write_output_buffer_test(void **state)
{
    uint8_t adr = 10;
    uint32_t val = 10;

    will_return(__wrap_i2c_slave_write, 0);

    assert_return_code(obdh_write_output_buffer(adr, val), 0);
}

int main(void)
{
    const struct CMUnitTest obdh_tests[] = {
        cmocka_unit_test(obdh_init_test),
        cmocka_unit_test(obdh_decode_test),
        cmocka_unit_test(obdh_write_output_buffer_test),

    };

    return cmocka_run_group_tests(obdh_tests, NULL, NULL);
}

/** \} End of obdh_test group */
