/*
 * tca4311a_wrap.h
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
 * \brief tca4311a_wrap driver wrap definition.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2021/08/23
 *
 * \defgroup tca4311a_wrap tca4311a_wrap Wrap
 * \ingroup tests
 * \{
 */

#ifndef TCA4311A_WRAP_H
#define TCA4311A_WRAP_H

#include <drivers/i2c_slave/i2c_slave.h>
#include <drivers/gpio/gpio.h>
#include <drivers/tca4311a/tca4311a.h>

#include <stdint.h>
#include <stdbool.h>

int __wrap_tca4311a_init(tca4311a_config_t config, bool en);

int __wrap_tca4311a_enable(tca4311a_config_t config);

int __wrap_tca4311a_disable(tca4311a_config_t config);

int __wrap_tca4311a_is_ready(tca4311a_config_t config);

int __wrap_tca4311a_write(tca4311a_config_t config, i2c_slave_adr_t adr, uint8_t *data, uint16_t len);

int __wrap_tca4311a_read(tca4311a_config_t config, i2c_slave_adr_t adr, uint8_t *data, uint16_t len);

int __wrap_tca4311a_write_byte(tca4311a_config_t config, i2c_slave_adr_t adr, uint8_t byte);

int __wrap_tca4311a_read_byte(tca4311a_config_t config, i2c_slave_adr_t adr, uint8_t *byte);

#endif /* TCA4311A_WRAP_H */

/** \} End of tca4311a_wrap group */
