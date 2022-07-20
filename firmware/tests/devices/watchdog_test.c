/*
 * watchdog_test.c
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
 * \brief Unit test of the Watchdog device.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2022/07/12
 *
 * \defgroup watchdog_unit_test Watchdog
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include <devices/watchdog/watchdog.h>
#include <drivers/wdt/wdt.h>

static void watchdog_init_test(void **state)
{
    will_return(__wrap_wdt_init, 0);
    assert_return_code(watchdog_init(), 0);
}

static void watchdog_reset_test()
{
    expect_function_call(__wrap_wdt_reset);
    watchdog_reset();
}

int main(void)
{
    const struct CMUnitTest watchdog_tests[] = {
        cmocka_unit_test(watchdog_init_test),
        cmocka_unit_test(watchdog_reset_test),
    };

    return cmocka_run_group_tests(watchdog_tests, NULL, NULL);
}

/** \} End of watchdog_test group */
