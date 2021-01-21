/*
 * ds2775g.c
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
 * \brief DS2775G+ driver implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 * 
 * \version 0.1.2
 * 
 * \date 2021/01/21
 * 
 * \addtogroup ds2775g
 * \{
 */

#include "ds2775g.h"

/**
 * \brief Configures the DS2775 batteries monitor.
 *
 * Configures the DS2775 registers by the following procedure:
 * - Generates a reset on the one-wire line
 * - Sends the 0xCC general address to the line (only one slave is present)
 * - Sends the write command (0x6C)
 * - Sends the register address
 * - Sends the value to be written
 *
 * The registers are configured as follows:
 *
 * <b>Protection Register</b>
 * Enable charge and discharge.
 *
 * <b>Protector Threshold Register</b>
 * 0x61 bias used to the current accumulation.
 *
 * <b>Status Register</b>
 * Clear all flags.
 *
 * <b>Control Register</b>
 * Set the undervoltage threshold to 2.6 V.
 *
 * <b>Overcurrent Threshold Register</b>
 * Set the short-circuit current to 15 A, the discharge overcurrent
 * to 7.5 A and the charge overcurrent to 5A.
 *
 * <b>Current Gain Register</b>
 * Removes gain from the measurements.
 *
 * If the Write Accumulated Current build is being used, the Accumulated
 * Current Register is written with 3 Ah.
 *
 * In Debug mode, the data sent is read back to verify if it was
 * configured properly.
 */

int ds2775g_init(ds2775g_config_t *config)
{

    if(ds2775g_write_data(config->onewire_port, config->protection_reg, 0x4) == -1)              //Protection register configuration

    return -1;

    if(ds2775g_write_data(config->onewire_port, config->protector_threshold_reg, 0x4) == -1)     //Protector threshold register configuration

    return -1;

    if(ds2775g_write_data(config->onewire_port, config->status_reg, 0x4) == -1)                  //Status register configuration

    return -1;

    if(ds2775g_write_data(config->onewire_port, config->control_reg, 0x4) == -1)                 //Control register configuration

    return -1;

    if(ds2775g_write_data(config->onewire_port, config->overcurrent_thresholds_reg, 0x4) == -1)  //Current gain LSB register configuration

    return -1;

    return 0;
}

int ds2775g_write_data(onewire_port_t port, uint8_t *data_write, uint16_t len);
{

    if(onewire_reset(port) == 0)                                            //Master reset

    return -1;

    if(onewire_write_byte(port, &data_write, len) == -1)                    //Write EEPROM address, operation, register address and value to the register

     return -1;

    return 0;

}

int ds2775g_read_data(onewire_port_t port, uint8_t *data_read);
{
    int byte = 0;

    if(onewire_reset(port) == 0)                                            //Master reset

    return -1;

    if(onewire_read_byte(port, &data_read, 0x1) == -1)                      //Read EEPROM address, operation and register address

     return -1;

    return 0;

}

/** \} End of ds2775g group */
