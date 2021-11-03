/*
 * tca4311a_wrap.c
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
 * \brief tca4311a_wrap driver wrap implementation.
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


#include "tca4311a_wrap.h"
#include <stdint.h>
#include <stdbool.h>

int __wrap_tca4311a_init(tca4311a_config_t config, bool en) {
    return 0;
}

int __wrap_tca4311a_enable(tca4311a_config_t config) {
    return 0;
}

int __wrap_tca4311a_disable(tca4311a_config_t config) {
    return 0;
}

int __tca4311a_is_ready(tca4311a_config_t config) {
    return 0;
}


/** \} End of tca4311a_wrap group */
