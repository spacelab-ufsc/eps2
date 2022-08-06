/*
 * media_test.c
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
 * \brief Unit test of the Media Sensor device
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2021/08/23
 *
 * \defgroup media_test Media Sensor
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include <devices/media/media.h>
#include <drivers/flash/flash.h>

static void media_init_test(void **state)
{
    will_return(__wrap_flash_init, 0);
    assert_return_code(media_init(), 0);
}

static void media_write_test(void **state)
{
    uint32_t adr = 0;
    uint32_t data[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    uint16_t len = 4;

    for (uint16_t i = 0; i < len; i += 4)
    {
        expect_value(__wrap_flash_write_long, data, data[i]);
    }

    assert_return_code(media_write(adr, data, len), 0);
}

static void media_read_test(void **state)
{
    uint32_t adr = 0;
    uint32_t data[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    uint32_t *data_ptr = data;
    uint16_t len = 4;

    for (uint16_t i = 0; i < len; i += 4)
    {
        will_return(__wrap_flash_read_long, adr - FLASH_SEG_A_ADR);
    }

    assert_return_code(media_read(adr, data_ptr, len), 0);
}

static void media_erase_test(void **state)
{
    uint32_t address = 0;

    expect_value(__wrap_flash_write_single, data, 0xFF);

    assert_return_code(media_erase(address), 0);
}

int main(void)
{
    const struct CMUnitTest media_tests[] = {
        cmocka_unit_test(media_init_test),
        cmocka_unit_test(media_write_test),
        cmocka_unit_test(media_read_test),
        cmocka_unit_test(media_erase_test)};

    return cmocka_run_group_tests(media_tests, NULL, NULL);
}
