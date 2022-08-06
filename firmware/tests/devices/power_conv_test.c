/*
 * power_conv_test.c
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
 * \brief Unit test of the Power Converter device
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2021/08/23
 *
 * \defgroup power_conv_test Power Converter
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include <devices/power_conv/power_conv.h>

static void power_conv_init_test(void **state)
{
    will_return(__wrap_tps54x0_init, 0);
    will_return(__wrap_tps54x0_init, 0);

    assert_return_code(power_conv_init(), 0);
}

static void enable_obdh_power_test(void **state)
{
    will_return(__wrap_tps54x0_enable, 0);
    assert_return_code(enable_obdh_power(), 0);
}

static void disable_obdh_power_test(void **state)
{
    will_return(__wrap_tps54x0_disable, 0);
    assert_return_code(disable_obdh_power(), 0);
}

static void enable_payload_power_test(void **state)
{
    will_return(__wrap_tps54x0_enable, 0);
    assert_return_code(enable_payload_power(), 0);
}

static void disable_payload_power_test(void **state)
{
    will_return(__wrap_tps54x0_disable, 0);
    assert_return_code(disable_payload_power(), 0);
}

int main(void)
{
    const struct CMUnitTest power_conv_tests[] = {
        cmocka_unit_test(power_conv_init_test),
        cmocka_unit_test(enable_obdh_power_test),
        cmocka_unit_test(disable_obdh_power_test),
        cmocka_unit_test(enable_payload_power_test),
        cmocka_unit_test(disable_payload_power_test)};

    return cmocka_run_group_tests(power_conv_tests, NULL, NULL);
}

/** \} End of power_conv_test group */
