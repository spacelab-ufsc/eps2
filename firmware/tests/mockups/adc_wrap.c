/*
 * adc_wrap.c
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
 * \brief ADC driver wrap definition.
 *
 * \author Lucas Zacchi de Medeiros <lzacchi@pm.me>
 *
 * \version 0.1.0
 *
 * \date 2021/08/23
 *
 * \defgroup adc_wrap ADC Wrap
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include "adc_wrap.h"

int __wrap_adc_init(adc_port_t port, adc_config_t config) {
    check_expected(port);

    return mock_type(int);
}

int __wrap_adc_read(adc_port_t port, uint16_t *val) {
    check_expected(port);

    uint16_t adc_val = mock_type(uint16_t);

    if (val != NULL) {
        *val = adc_val;
    }

    return mock_type(int);
}

float __wrap_adc_temp_get_mref(void) {
    return mock_type(float);
}

float __wrap_adc_temp_get_nref(void) {
    return mock_type(float);
}

bool __wrap_adc_mutex_create(void) {
    return true;
}

bool __wrap_adc_mutex_take(void) {
    return true;
}

bool __wrap_adc_mutex_give(void) {
    return true;
}


/** \} End of adc_wrap group */
