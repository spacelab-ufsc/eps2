/*
 * media_test.c
 * 
 * Copyright (C) 2021, SpaceLab.
 * 
 * This file is part of TTC 2.0.
 * 
 * TTC 2.0 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * TTC 2.0 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with TTC 2.0. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief Unit test of the media device.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.3
 * 
 * \date 2021/08/07
 * 
 * \defgroup media_unit_test Media
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
}

static void media_write_test(void **state)
{
}

static void media_read_test(void **state)
{
}

static void media_erase_test(void **state)
{
}

static void media_get_info_test(void **state)
{
}

int main(void)
{
    const struct CMUnitTest media_tests[] = {
        cmocka_unit_test(media_init_test),
        cmocka_unit_test(media_write_test),
        cmocka_unit_test(media_read_test),
        cmocka_unit_test(media_erase_test),
        cmocka_unit_test(media_get_info_test),
    };

    return cmocka_run_group_tests(media_tests, NULL, NULL);
}

/** \} End of media_test group */
