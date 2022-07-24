/*
 * pwm_wrap.c
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
 * \brief pwm driver wrap implementation.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2022/05/09
 *
 * \defgroup pwm_wrap PWM Wrap
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include "pwm_wrap.h"

int __wrap_pwm_init(pwm_source_t source, pwm_port_t port, pwm_config_t config)
{
    check_expected(source);
    check_expected(port);

    return mock_type(int);
}

int __wrap_pwm_update(pwm_source_t source, pwm_port_t port, pwm_config_t config)
{
    check_expected(source);
    check_expected(port);

    return mock_type(int);
}

int __wrap_pwm_stop(pwm_source_t source, pwm_port_t port, pwm_config_t config)
{
    check_expected(source);
    check_expected(port);

    return mock_type(int);
}

int __wrap_pwm_disable(pwm_source_t source)
{
    check_expected(source);

    return mock_type(int);
}

/** \} End of pwm_wrap group */
