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
 * \version 0.1.7
 * 
 * \date 2021/06/03
 * 
 * \addtogroup onewire
 * \{
 */

#include "onewire.h"
#include <intrinsics.h>

int onewire_init(onewire_port_t port)
{

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
}

int onewire_write_bit(onewire_port_t port, int bit)
{
    int result;

    switch(bit){

    case 1:                                                               //Write bit "1"
        gpio_init(port, (gpio_config_t){.mode=GPIO_MODE_OUTPUT});
        gpio_set_state(port, GPIO_STATE_LOW);                             //drives pin low
        __delay_cycles(clock*0.000006);                                   //delay of 6us, 8,12 MHz*6us= 44

        gpio_init(port, (gpio_config_t){.mode=GPIO_MODE_INPUT});          //releases the bus
        __delay_cycles(clock*0.000064);                                   //delay of 64us, 8,12MHz*64us=517

        result = 0;
        break;

    case 0:                                                                //Write bit "0"
        gpio_init(port, (gpio_config_t){.mode=GPIO_MODE_OUTPUT});
        gpio_set_state(port, GPIO_STATE_LOW);                              //drives pin low
        __delay_cycles(clock*0.000060);                                    //delay of 60us, 8,12MHz*60us=487

        gpio_init(port, (gpio_config_t){.mode=GPIO_MODE_INPUT});           //releases the bus
        __delay_cycles(clock*0.000080);                                    // delay of 10us, 8MHz*10us=80

        result = 0;
        break;

    default:
        result = -1;
        break;
    }

    return result;
}

int onewire_write_byte(onewire_port_t port, uint8_t *data, uint16_t len)
{
    uint16_t i;
    uint8_t loop;

    for(i = 0; i < len; i++){                                           //Loop to write the number of bytes specified in len

    for (loop = 0; loop < 8; loop++)                                    // Loop to write each bit in the byte, LS-bit first
    {
        if(onewire_write_bit(port, data[i] & 0x01) < 0)                 //write a bit and check error occurrence
            return -1;

            data[i] >>= 1;                                              // shift the data byte for the next bit
        }
    }

    return 0;
}

int onewire_read_bit(onewire_port_t port)
{
    int result = 0;

    gpio_init(port, (gpio_config_t){.mode=GPIO_MODE_OUTPUT});
    gpio_set_state(port, GPIO_STATE_LOW);                                 //drives pin low
    __delay_cycles(clock*0.000006);                                       //delay of 6us, 8,12 MHz*6us= 44

    gpio_init(port, (gpio_config_t){.mode=GPIO_MODE_INPUT});              //releases the bus
    __delay_cycles(clock*0.000009);                                       //delay of 9us, 8,12MHz*9us=73

    result = gpio_get_state(port);                                        //sample the bit from slave
    __delay_cycles(clock*0.000055);                                       //delay of 55us, 8,12MHz*55us=446

    return result;

}

int onewire_read_byte(onewire_port_t port, uint8_t *data, uint16_t len)
{
    uint16_t i;
    uint8_t loop, read = 0;

    for(i = 0; i < len; i++)                                              //Loop to read the number of bytes specified in len
    {

    for(loop = 0; loop < 8; loop++)                                       //Loop to read each bit from the byte
    {
        read >>= 1;                                                       //shift the result to get it ready for the next bit

        if (onewire_read_bit(port))                                       //if result is one, then set MS bit
            read |= 0x80;
    }

    if(read < 0)
    return -1;

    data[i] = read;

    }
       return 0;

}

/** \} End of onewire group */
