/*
 * bat_manager.c
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
 * \brief Battery Manager device implementation.
 *
 * \author Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 2021/02/01
 *
 * \addtogroup bat_manager
 * \{
 */

#include <stdint.h>

#include "drivers/ds2775g/ds2775g.h"

#include "drivers/onewire/onewire.h"


int bat_manager_init(){

    return -1;

}

int get_bat_voltage(bat_voltage_t *bat_volt){

    return -1;

}

int get_bat_current(uint32_t *bat_cur){

    return -1;

}

int get_bat_charge(uint32_t *charge){

    return -1;

}

int get_bat_data(bat_manager_data_t *data){

    return -1;

}
