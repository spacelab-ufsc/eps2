/*
 * eps2_data_test.c
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
 * \brief Unit test of the EPS2 Data structure
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2021/11/09
 *
 * \defgroup eps2_data_test EPS2 Data
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include <app/structs/eps2_data.h>
#include <system/sys_log/sys_log.h>

static void eps_buffer_read_test(void **state) {
    uint32_t value = 0;
    for (uint8_t id = EPS2_PARAM_ID_TIME_COUNTER; id < EPS2_PARAM_ID_DEVICE_ID; ++id) {
        int result = eps_buffer_read(id, &value);
        assert_return_code(result, 0);
        assert_true(value == id);
    }

}

int main(void) {
    const struct CMUnitTest eps_data_tests[] = {
        cmocka_unit_test(eps_buffer_read_test),
    };

    return cmocka_run_group_tests(eps_data_tests, NULL, NULL);
}
