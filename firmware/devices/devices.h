/*
 * devices.h
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
 * \brief Devices layer.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.8
 * 
 * \date 2021/06/03
 * 
 * \defgroup devices Devices
 * \{
 */

#ifndef DEVICES_H_
#define DEVICES_H_

#include <devices/leds/leds.h>
#include <devices/watchdog/watchdog.h>
#include <devices/current_sensor/current_sensor.h>
#include <devices/voltage_sensor/voltage_sensor.h>
#include <devices/media/media.h>
#include <devices/mppt/mppt.h>
#include <devices/bat_manager/bat_manager.h>
#include <devices/temp_sensor/temp_sensor.h>
#include <devices/obdh/obdh.h>
#include <devices/ttc/ttc.h>

#endif /* DEVICES_H_ */

/** \} End of devices group */
