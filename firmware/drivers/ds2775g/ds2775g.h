/*
 * ds2775g.h
 * 
 * Copyright (C) 2020, SpaceLab.
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
 * \brief DS2775G+ driver definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 2020/10/23
 * 
 * \defgroup ds2775g DS2775G
 * \ingroup drivers
 * \{
 */

#ifndef DS2775G_H_
#define DS2775G_H_

#include <drivers/onewire/onewire.h>

/**
 * \brief DS2775G+ configuration parameters.
 */
typedef struct
{
    onewire_port_t onewire_port;        /**< OneWire port. */
} ds2775g_config_t;

/**
 * \brief DS2775G+ initialization.
 *
 * \param[in,out] config is a pointer to the DS2775G+ configuration parameters.
 *
 * \return The status/error code.
 */
int ds2775g_init(ds2775g_config_t *config);

#endif /* DS2775G_H_ */

/** \} End of ds2775g group */
