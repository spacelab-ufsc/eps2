/*
 * tps54540.h
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
 * \brief TPS54540 driver definition.
 * 
 * \authors Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 2021/01/18
 * 
 * \defgroup tps54540 TPS54540
 * \ingroup drivers
 * \{
 */

#ifndef TPS54540_H_
#define TPS54540_H_

#include <drivers/gpio/gpio.h>

#define TPS54540_MODULE_NAME "TPS54540"

/**
 * \brief TPS54540 configuration parameters.
 */
typedef struct
{
    gpio_pin_t enable_pin; /**< Enable pin. */
} tps54540_config_t;

/**
 * \brief TPS54540 related enable pin initialization on MCU.
 *
 * \param[in,out] config is a pointer to the TPS54540 configuration parameters.
 *
 * \return The status/error code.
 */
int tps54540_init(tps54540_config_t *config);

/**
 * \brief Enables a given TPS54540 device.
 *
 * This funcition sets the Enable pin of the given TPS54540 device.
 *
 * \param[in,out] config is a pointer to the TPS54540 configuration parameters.
 *
 * \return The status/error code.
 */
int tps54540_enable(tps54540_config_t *config);

/**
 * \brief Disables a given TPS54540 device.
 *
 * This funcition clears the Enable pin of the given TPS54540 device.
 *
 * \param[in,out] config is a pointer to the TPS54540 configuration parameters.
 *
 * \return The status/error code.
 */
int tps54540_disable(tps54540_config_t *config);

#endif /* TPS54540_H_ */

/** \} End of tps54540 group */