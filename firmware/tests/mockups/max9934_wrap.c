/*
 * max9934_wrap.h
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
 * \brief MAX9934 driver wrap implementation.
 *
 * \author Lucas Zacchi de Medeiros <lzacchi@pm.me>
 *
 * \version 0.1.0
 *
 * \date 2021/08/24
 *
 * \defgroup max9934_wrap MAX9934 Wrap
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include "max9934_wrap.h"

int __wrap_max9934_init(max9934_config_t config) {
    return 0;
}

int __wrap_max9934_read(max9934_config_t config, uint16_t *raw_val) {
    return 0;
}
