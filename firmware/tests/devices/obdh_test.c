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

static void obdh_init_test(void** state) {

}

static void obdh_decode_test(void **state) {

}

static void obdh_write_output_buffer_test(void** state) {

}

int main(void) {
    const struct CMUnitTest obdh_tests[] = {
        cmocka_unit_test(obdh_init_test),
        cmocka_unit_test(obdh_decode_test),
        cmocka_unit_test(obdh_write_output_buffer_test),

    };

    return cmocka_run_group_tests(obdh_tests, NULL, NULL);
}

/** \} End of obdh_test group */
