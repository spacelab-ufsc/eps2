/*
 * ds2775g_wrap.h
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
 * \brief ds2775g driver wrap definition.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.2.43
 *
 * \date 2022/06/15
 *
 * \defgroup ds2775g_wrap DS2775G Wrap
 * \ingroup tests
 * \{
 */

#ifndef DS2775G_WRAP_H
#define DS2775G_WRAP_H

#include <drivers/ds2775g/ds2775g.h>

int __wrap_ds2775g_init(ds2775g_config_t *config);

int __wrap_ds2775g_write_data(onewire_port_t port, uint8_t *data, uint16_t len);

int __wrap_ds2775g_read_register(onewire_port_t port, uint8_t register_address, uint8_t *data_read);

int __wrap_write_accumulated_current_max_value(onewire_port_t port);

#endif /* DS2775G_WRAP_H */
       /** \} End of ds2775g_wrap group */
