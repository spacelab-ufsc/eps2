/*
 * i2c_slave_wrap.h
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
 * \brief i2c_slave driver wrap definition.
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
#ifndef I2C_SLAVE_WRAP_H
#define I2C_SLAVE_WRAP_H

#include <stdint.h>

#include <drivers/i2c_slave/i2c_slave.h>
#include <drivers/i2c/i2c.h>

int __wrap_i2c_slave_init(i2c_slave_port_t port, i2c_slave_address_t adr);

int __wrap_i2c_slave_enable(void);

int __wrap_i2c_slave_disable(void);

int __wrap_i2c_slave_read(uint8_t *data, uint16_t *len);

int __wrap_i2c_slave_write(uint8_t *data, uint16_t len);

#endif /* I2C_SLAVE_WRAP_H */

/** \} End of i2c_slave_wrap group */
