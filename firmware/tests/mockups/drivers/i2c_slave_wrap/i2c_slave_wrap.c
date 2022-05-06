/*
 * i2c_slave_wrap.c
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
 * \brief i2c_slave driver wrap implementation.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.2.41
 *
 * \date 2021/09/28
 *
 * \defgroup i2c_slave_wrap I2C SLAVE Wrap
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include <drivers/i2c_slave/i2c_slave.h>

int __wrap_i2c_slave_init(i2c_slave_port_t port, i2c_slave_address_t adr)
{
    check_expected(port);
    check_expected(adr);

    return mock_type(int);
}

int __wrap_i2c_slave_enable(void)
{
    return mock_type(int);
}

int __wrap_i2c_slave_disable(void)
{
    return 0;
}

int __wrap_i2c_slave_read(uint8_t *data, uint16_t *len)
{
    return mock_type(int);
}

int __wrap_i2c_slave_write(uint8_t *data, uint16_t len)
{
    return mock_type(int);
}

/** \} End of i2c_slave_wrap group */
