/*
 * tps54x0.h
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
 * \brief TPS54X0 driver definition.
 * 
 * \authors Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * 
 * \version 0.1.3
 * 
 * \date 2021/01/18
 * 
 * \defgroup tps54x0 TPS54X0
 * \ingroup drivers
 * \{
 */

#ifndef TPS54X0_H_
#define TPS54X0_H_

#include <drivers/gpio/gpio.h>

#define TPS54X0_MODULE_NAME "TPS54X0"

/**
 * \brief TPS54X0 configuration parameters.
 */
typedef struct
{
    gpio_pin_t enable_pin; /**< Enable pin. */
} tps54x0_config_t;

/**
 * \brief TPS54X0 related enable pin initialization on MCU.
 *
 * \param[in,out] config is a pointer to the TPS54540 configuration parameters.
 *
 * \return The status/error code.
 */
int tps54x0_init(tps54x0_config_t config);

/**
 * \brief Enables a given TPS54X0 device.
 *
 * This funcition sets the Enable pin of the given TPS54540 device.
 *
 * \param[in,out] config is a pointer to the TPS54x0 configuration parameters.
 *
 * \return The status/error code.
 */
int tps54x0_enable(tps54x0_config_t config);

/**
 * \brief Disables a given TPS54X0 device.
 *
 * This funcition clears the Enable pin of the given TPS54X0 device.
 *
 * \param[in,out] config is a pointer to the TPS54X0 configuration parameters.
 *
 * \return The status/error code.
 */
int tps54x0_disable(tps54x0_config_t config);

#endif /* TPS54X0_H_ */

/** \} End of tps54x0 group */
