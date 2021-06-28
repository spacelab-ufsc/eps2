/*
 * drivers.h
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
 * \brief Drivers layer definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 2020/10/21
 * 
 * \defgroup drivers Drivers
 * \{
 */

#ifndef DRIVERS_H_
#define DRIVERS_H_

#include "adc/adc.h"
#include "ads1248/ads1248.h"
#include "ds2775g/ds2775g.h"
#include "flash/flash.h"
#include "gpio/gpio.h"
#include "i2c/i2c.h"
#include "max9934/max9934.h"
#include "onewire/onewire.h"
#include "spi/spi.h"
#include "tca4311a/tca4311a.h"
#include "tps54540/tps54540.h"
#include "uart/uart.h"
#include "wdt/wdt.h"

#endif /* DRIVERS_H_ */

/** \} End of drivers group */
