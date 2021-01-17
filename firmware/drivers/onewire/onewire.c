/*
 * onewire.c
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
 * \brief OneWire driver implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 * 
 * \version 0.1.2
 * 
 * \date 2021/01/17
 * 
 * \addtogroup onewire
 * \{
 */

#include "onewire.h"
#include "intrinsics.h"

#define clock 8000000

int onewire_init(onewire_port_t port)
{
    //return int gpio_init(gpio_pin_t pin, gpio_config_t config);
    return -1;
}

int onewire_reset(onewire_port_t port)
{
    int result = 0;

    //gpio_set_state(port, GPIO_STATE_HIGH);                            //drives pin to high
    gpio_init(port, (gpio_config_t){.mode=GPIO_MODE_INPUT});            //releases the bus: pull-up drives pin to high
    __delay_cycles(0);                                                  // delay of 0
    gpio_init(port, (gpio_config_t){.mode=GPIO_MODE_OUTPUT});
    gpio_set_state(port, GPIO_STATE_LOW);                               //drives pin low
    __delay_cycles(clock*0.000480);                                     //delay of 480us, 8,12MHz* 480us=3897

    //gpio_set_state(port, GPIO_STATE_HIGH);                            //releases the bus
    gpio_init(port, (gpio_config_t){.mode=GPIO_MODE_INPUT});            //releases the bus
    result = gpio_get_state(port);                                      //prepares the result of present detection to be returned
    __delay_cycles(clock*0.000070);                                     //delay of 70us, 8,12MHz*70us=568

    //gpio_set_state(port, GPIO_STATE_HIGH);
    gpio_init(port, (gpio_config_t){.mode=GPIO_MODE_INPUT});            //release the bus
    __delay_cycles(clock*0.000410);                                     //delay of 410us, 8,12MHz*410us=3329

    return result;                                                      //returns the presence detection result
    //return -1;
}

int onewire_write(onewire_port_t port, onewire_adr_t adr, uint8_t *data, uint16_t len)
{
    return -1;
}

int onewire_read(onewire_port_t port, onewire_adr_t adr, uint8_t *data, uint16_t len)
{
    return -1;
}

/** \} End of onewire group */
