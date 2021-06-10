/*
 * power_conv.h
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
 * \brief Power converters device definition.
 *
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 *
 * \version 0.1.12
 *
 * \date 2021/06/10
 *
 * \defgroup power_conv Power Converters
 * \ingroup devices
 * \{
 */

#ifndef POWER_CONVERTERS_H_
#define POWER_CONVERTERS_H_

#include <stdint.h>

#include <drivers/gpio/gpio.h>
#include "drivers/tps54x0/tps54x0.h"

#define POWER_CONV_MODULE_NAME		"Power Converters"

#define EN_3V3_OBDH_PIN GPIO_PIN_36
#define EN_PAYLOAD_PIN GPIO_PIN_37

/**
 * \brief Initialization of the Power Converters device.
 *
 * \return The status/error code.
 */
int power_conv_init();

/**
 * \brief Emable power for OBDH.
 *
 * \return The status/error code.
 */
int enable_obdh_power();

/**
 * \brief Disables power for OBDH.
 *
 * \return The status/error code.
 */
int disable_obdh_power();

/**
 * \brief Enables power for payloads.
 *
 * \return The status/error code.
 */
int enable_payload_power();

/**
 * \brief Disables power for payloads.
 *
 * \return The status/error code.
 */
int disable_payload_power();


#endif /* POWER_CONVERTERS_H_ */

/** \} End of power_conv group */
