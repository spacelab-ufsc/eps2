/*
 * ds2775g.h
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
 * \brief DS2775G+ driver definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 * 
 * \version 0.1.2
 * 
 * \date 2021/02/07
 * 
 * \defgroup ds2775g DS2775G
 * \ingroup drivers
 * \{
 */

#ifndef DS2775G_H_
#define DS2775G_H_

#include <drivers/onewire/onewire.h>
#include "gpio/gpio.h"

/**
 * \brief declaring DS2775G+ units.
 */

#define rsense          0.01
#define voltage_unit    0.004883
#define current_unit    0.0000015625/rsense
#define accumulated_current_unit    6.25*0.000001/rsense

/**
 * \brief declaring DS2775G+ OneWire port.
 */

onewire_port_t onewire_port = GPIO_PIN_69;       //Declaring one wire port as P9.1;

/**
 * \brief DS2775G+ register address.
 */
struct
{
uint8_t protection_register = 0x00;
uint8_t protector_threshold_register = 0x7F;
uint8_t status_register = 0x01;
uint8_t control_register = 0x60;
uint8_t accumulated_current_MSB_register = 0x10;
uint8_t accumulated_current_LSB_register = 0x11;
uint8_t temperature_MSB_register = 0x0A;
uint8_t temperature_LSB_register = 0x0B;
uint8_t average_current_MSB_register = 0x08;
uint8_t average_current_LSB_register = 0x09;
uint8_t overcurrent_thresholds_register = 0x78;
uint8_t current_gain_LSB_register = 0x79;
uint8_t current_MSB_register = 0x0E;
uint8_t current_LSB_register = 0x0F;
uint8_t voltage_MSB1_register = 0x0C;
uint8_t voltage_LSB1_register = 0x0D;
uint8_t voltage_MSB2_register = 0x1C;
uint8_t voltage_LSB2_register = 0x1D;

}ds2775g_reg;

/**
 * \brief DS2775G+ commands.
 */

struct
{
uint8_t skip_address = 0xCC;    //Address that access any onewire device (used when there's only one device at the onewire bus)
uint8_t write_data = 0x6C;      //Command to write a data in the DS2775G+ memory
uint8_t read_data = 0x69;       //Command to read a data from DS2775G+ memory
uint8_t copy_data = 0x48;       //Command to copy data of the DS2775G+ EEPROM shadow RAM to EEPROM cells

} ds2775g_commands;

/**
 * \brief DS2775G+ configuration parameters.
 *
 * The register configuration arrays contain the 4 bytes sequence wich need to be send in the OneWire bus to configure each register
 *
 * The configuration is: [device address, command, reg address, data to be written]
 *
 */
typedef struct
{
    onewire_port_t onewire_port           = GPIO_PIN_69;        /**< OneWire port. */
    uint8_t protection_reg[4]             = {ds2775g_commands.skip_address, ds2775g_commands.write_data, ds2775g_reg.protection_register, 0x03};
    uint8_t protector_threshold_reg[4]    = {ds2775g_commands.skip_address, ds2775g_commands.write_data, ds2775g_reg.protector_threshold_register, 0x61};
    uint8_t status_reg[4]                 = {ds2775g_commands.skip_address, ds2775g_commands.write_data, ds2775g_reg.status_register, 0x0};
    uint8_t control_reg[4]                = {ds2775g_commands.skip_address, ds2775g_commands.write_data, ds2775g_reg.control_register, 0x0C};
    uint8_t overcurrent_thresholds_reg[4] = {ds2775g_commands.skip_address, ds2775g_commands.write_data, ds2775g_reg.overcurrent_thresholds_register, 0x24};
    uint8_t current_gain_LSB_reg[4]       = {ds2775g_commands.skip_address, ds2775g_commands.write_data, ds2775g_reg.current_gain_LSB_register, 0x00};

} ds2775g_config_t;

/**
 * \brief DS2775G+ initialization.
 *
 * \param[in,out] config is a pointer to the DS2775G+ configuration parameters.
 *
 * \return The status/error code.
 */
int ds2775g_init(ds2775g_config_t *config);

/**
 * \brief write data to an DS2775G+ register.
 *
 * \param[in] port is the OneWire port to write.
 *
 * \param[in] data_write is the data to write to the DS2775G+ register.
 *
 * \param[in] len is the number of bytes to write.
 *
 * \return The status/error code.
 */
int ds2775g_write_data(onewire_port_t port, uint8_t *data_write, uint16_t len);

/**
 * \brief read data from DS2775G+ registers.
 *
 * \param[in] port is the OneWire port to read.
 *
 * \param[in] register_address is the address of the register that will be read.
 *
 * \param[out] data_read is the data read from the DS2775G+ register.
 *
 * \return The status/error code.
 */
int ds2775g_read_register(onewire_port_t port, uint8_t register_address, uint8_t *data_read);

/**
 * \brief writes accumulated current maximum value (3 Ah) to DS2775G+ appropriated register
 *
 * \param[in] port is the OneWire port to write.
 *
 * \return The status/error code.
 */
int write_accumulated_current_max_value(onewire_port_t port);

#endif /* DS2775G_H_ */

/** \} End of ds2775g group */
