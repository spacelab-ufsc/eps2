/*
 * obdh.h
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
 * \brief OBDH device definition.
 *
 * \author Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 22/04/2020
 *
 * \defgroup obdh OBDH
 * \ingroup devices
 * \{
 */

#ifndef OBDH_H_
#define OBDH_H_

#include <stdint.h>

#define OBDH_MODULE_NAME         "OBDH"

/**
 * \brief Initialization routine of the OBDH device.
 *
 * \return The status/error code.
 */
int obdh_init();

#endif /* OBDH_H_ */

/** \} End of obdh group */
