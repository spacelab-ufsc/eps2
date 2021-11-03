/*
 * i2c_wrap.h
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
 * \brief i2c driver wrap definition.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2021/09/28
 *
 * \defgroup i2c_wrap I2C Wrap
 * \ingroup tests
 * \{
 */

#ifndef I2C_WRAP_H
#define I2C_WRAP_H

#include <drivers/i2c/i2c.h>

int __wrap_i2c_master_init(i2c_port_t port, i2c_config_t config);

int __wrap_i2c_write(i2c_port_t port, i2c_slave_adr_t adr, uint8_t *data, uint16_t len);

int __wrap_i2c_read(i2c_port_t port, i2c_slave_adr_t adr, uint8_t *data, uint16_t len);

#endif /* I2C_WRAP_H */
/** \} End of i2c_wrap group */
