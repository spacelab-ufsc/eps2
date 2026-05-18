/*
 * current_sensor_wrap.h
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
 * \brief Current Sensor device wrap definition.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2022/08/15
 *
 * \defgroup current_sensor_wrap Current Sensor Wrap
 * \ingroup tests
 * \{
 */

#ifndef CURRENT_SENSOR_WRAP_H
#define CURRENT_SENSOR_WRAP_H

#include <stdint.h>

#include <devices/current_sensor/current_sensor.h>

int __wrap_current_sensor_init();

uint16_t __wrap_current_sensor_raw_to_ma(adc_port_t port, uint16_t raw);

int __wrap_current_sensor_read(adc_port_t port, uint16_t *cur);

#endif /* CURRENT_SENSOR_WRAP_H */

/** \} End of current_sensor_wrap group */
