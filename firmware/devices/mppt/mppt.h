/*
 * mppt.h
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
 * \brief MPPT device definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.3
 * 
 * \date 2021/02/10
 * 
 * \defgroup mppt MPPT
 * \ingroup devices
 * \{
 */

#ifndef MPPT_H_
#define MPPT_H_

#define MPPT_MODULE_NAME        "MPPT"

/**
 * \brief Initialization routine of the MPPT.
 *
 * \return The status/error code.
 */
int mppt_init();

#endif /* MPPT_H_ */

/** \} End of mppt group */
