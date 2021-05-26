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
 * \date 2021/02/10
 * 
 * \addtogroup ds2775g
 * \{
 */

#include <stdio.h>
#include "ds2775g.h"
#include "config/config.h"
#include "uart/uart.h"
#include "gpio/gpio.h"

#define ACCUMULATED_CURRENT_MSB (uint8_t)(BAT_MONITOR_CHARGE_VALUE>>8)
#define ACCUMULATED_CURRENT_LSB (uint8_t)BAT_MONITOR_CHARGE_VALUE

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

#if RESET_BATTERY_ACCUMULATED_CURRENT == 1

    write_accumulated_current_max_value(config->onewire_port);

#endif //RESET_BATTERY_ACCUMULATED_CURRENT

#if CONFIG_DRIVERS_DEBUG_ENABLED == 1

    uart_port_t UART_port = UART_PORT_0;        //Declaring UART port;

    uint8_t ds2775g_data_sent_back[8] = {0};

    ds2775g_read_register(OW_port, protection_register, &ds2775g_data_sent_back[0]);
    ds2775g_read_register(OW_port, protector_threshold_register, &ds2775g_data_sent_back[1]);
    ds2775g_read_register(OW_port, status_register, &ds2775g_data_sent_back[2]);
    ds2775g_data_sent_back[2] &= 0xf0;
    ds2775g_read_register(OW_port, control_register, &ds2775g_data_sent_back[3]);
    ds2775g_read_register(OW_port, overcurrent_thresholds_register, &ds2775g_data_sent_back[4]);
    ds2775g_read_register(OW_port, current_gain_LSB_register, &ds2775g_data_sent_back[5]);
    ds2775g_read_register(OW_port, accumulated_current_MSB_register, &ds2775g_data_sent_back[6]);
    ds2775g_read_register(OW_port, accumulated_current_LSB_register, &ds2775g_data_sent_back[7]);

    uint8_t i = 0;
    uint8_t string[4];

    if(uart_avaliable(UART_port)){

        for(i = 0; i < 8; i++){
              sprintf(string, "%#04x", one_wire_data_sent_back[i]);
              uart_write(UART_port, string, 0x4);
              if(i != 7){
                  string = {','};
                  uart_write(UART_port, string, 0x1);
              }
              else{
                  string = {'\r\n'};
                  uart_write(UART_port, string, 0x4);
              }
          }

    }
    else{
        sys_log_print_event_from_module(SYS_LOG_ERROR, UART_MODULE_NAME, "UART bus is not avaliable!");
    }

#endif //End debug routine

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

int ds2775g_read_register(onewire_port_t port, uint8_t register_address, uint8_t *data_read)
{

    uint8_t read_command[3] = {ds2775g_commands.skip_address, ds2775g_commands.read_data, register_address};

    if(ds2775g_write_data(port, read_command, 0x3); == -1)                               //Generate reset, sends the general address (0xCC) and the read command (0x69)

    return -1;

    if(onewire_read_byte(port, data_read, 0x1) == -1)                                    //Read data

     return -1;

    return 0;

}

int write_accumulated_current_max_value(onewire_port_t port){         // write 3Ah to battery accumulated current

    uint8_t acc_write_msb[4] = {ds2775g_commands.skip_address, ds2775g_commands.write_data, ds2775g_reg.accumulated_current_MSB_register, ACCUMULATED_CURRENT_MSB};
    uint8_t acc_copy_msb[3] = {ds2775g_commands.skip_address, ds2775g_commands.copy_data, ds2775g_reg.accumulated_current_MSB_register};
    uint8_t acc_write_lsb[4] = {ds2775g_commands.skip_address, ds2775g_commands.write_data, ds2775g_reg.accumulated_current_LSB_register, ACCUMULATED_CURRENT_LSB};
    uint8_t acc_copy_lsb[3] = {ds2775g_commands.skip_address, ds2775g_commands.copy_data, ds2775g_reg.accumulated_current_LSB_register};

    if (ds2775g_write_data(port, acc_write_msb, 0x4) == -1)        //Write ACCUMULATED_CURRENT_MSB to the accumulated current MSB register

    return -1;

    if (ds2775g_write_data(port, acc_copy_msb, 0x3) == -1)        //Copy the data from EEPROM shadow RAM  to EEPROM

    return -1;

    if (ds2775g_write_data(port, acc_write_lsb, 0x4) == -1)        //Write ACCUMULATED_CURRENT_LSB to the accumulated current LSB register

    return -1;

    if (ds2775g_write_data(port, acc_copy_lsb, 0x3) == -1)        //Copy the data from EEPROM shadow RAM  to EEPROM

    return -1;

    return 0;
}

/** \} End of ds2775g group */