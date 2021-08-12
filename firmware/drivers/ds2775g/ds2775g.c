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
 * \version 0.2.0
 * 
 * \date 2021/06/11
 * 
 * \addtogroup ds2775g
 * \{
 */

#include <stdio.h>
#include "ds2775g.h"
#include <config/config.h>
#include <drivers/uart/uart.h>
#include <drivers/gpio/gpio.h>

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
    config->protection_reg[0] = skip_address;
    config->protection_reg[1] = write_data;
    config->protection_reg[2] = protection_register;
    config->protection_reg[3] =  0x03;
    config->protector_threshold_reg[0] = skip_address;
    config->protector_threshold_reg[1] = write_data;
    config->protector_threshold_reg[2] = protector_threshold_register;
    config->protector_threshold_reg[3] = 0x61;
    config->status_reg[0] = skip_address;
    config->status_reg[1] = write_data;
    config->status_reg[2] = status_register;
    config->status_reg[3] = 0x0;
    config->control_reg[0] = skip_address;
    config->control_reg[1] = write_data;
    config->control_reg[2] = control_register;
    config->control_reg[3] = 0x0C;
    config->overcurrent_thresholds_reg[0] = skip_address;
    config->overcurrent_thresholds_reg[1] = write_data;
    config->overcurrent_thresholds_reg[2] = overcurrent_thresholds_register;
    config->overcurrent_thresholds_reg[3] = 0x24;
    config->current_gain_LSB_reg[0] = skip_address;
    config->current_gain_LSB_reg[1] = write_data;
    config->current_gain_LSB_reg[2] = current_gain_LSB_register;
    config->current_gain_LSB_reg[3] = 0x00;
    
    /* Declaring 1-wire pin as P9.1 */
    config->onewire_port = GPIO_PIN_69;

    /* Protection register configuration */
    if(ds2775g_write_data(config->onewire_port, config->protection_reg, 0x4) == -1)
    {
        return -1;
    }

    /* Protector threshold register configuration */
    if(ds2775g_write_data(config->onewire_port, config->protector_threshold_reg, 0x4) == -1)
    {
        return -1;
    }

    /* Status register configuration */
    if(ds2775g_write_data(config->onewire_port, config->status_reg, 0x4) == -1)
    {
        return -1;
    }

    /* Control register configuration */
    if(ds2775g_write_data(config->onewire_port, config->control_reg, 0x4) == -1)
    {
        return -1;
    }

    /* Current gain LSB register configuration */
    if(ds2775g_write_data(config->onewire_port, config->overcurrent_thresholds_reg, 0x4) == -1)
    {
        return -1;
    }

#if RESET_BATTERY_ACCUMULATED_CURRENT == 1

    write_accumulated_current_max_value(config->onewire_port);

#endif

#if CONFIG_DRIVERS_DEBUG_ENABLED == 1

    /* TODO: Legacy code, this should not be here */
    //uart_port_t UART_port = UART_PORT_0;

    uint8_t ds2775g_data_sent_back[8] = {0};

    /* TODO: Legacy code, there is no more "OW_port" defined, up to corrent debug routine */
    //ds2775g_read_register(OW_port, protection_register, &ds2775g_data_sent_back[0]);
    //ds2775g_read_register(OW_port, protector_threshold_register, &ds2775g_data_sent_back[1]);
    //ds2775g_read_register(OW_port, status_register, &ds2775g_data_sent_back[2]);
    //ds2775g_data_sent_back[2] &= 0xf0;
    //ds2775g_read_register(OW_port, control_register, &ds2775g_data_sent_back[3]);
    //ds2775g_read_register(OW_port, overcurrent_thresholds_register, &ds2775g_data_sent_back[4]);
    //ds2775g_read_register(OW_port, current_gain_LSB_register, &ds2775g_data_sent_back[5]);
    //ds2775g_read_register(OW_port, accumulated_current_MSB_register, &ds2775g_data_sent_back[6]);
    //ds2775g_read_register(OW_port, accumulated_current_LSB_register, &ds2775g_data_sent_back[7]);

    uint8_t i = 0;
    uint8_t string[4];

    /* TODO: Legacy code, update to newer clean log scheme! */
    //if(uart_avaliable(UART_port)){
    //
    //    for(i = 0; i < 8; i++){
    //          sprintf(string, "%#04x", one_wire_data_sent_back[i]);
    //          uart_write(UART_port, string, 0x4);
    //          if(i != 7){
    //              string = {','};
    //              uart_write(UART_port, string, 0x1);
    //          }
    //          else{
    //              string = {'\r\n'};
    //              uart_write(UART_port, string, 0x4);
    //          }
    //      }
    //
    //}
    //else{
    //    sys_log_print_event_from_module(SYS_LOG_ERROR, UART_MODULE_NAME, "UART bus is not avaliable!");
    //}

#endif //End debug routine

    return 0;
}

int ds2775g_write_data(onewire_port_t port, uint8_t *data, uint16_t len)
{

    /* Master reset */
    if(onewire_reset(port) == 0)
    {
        return -1;
    }

    /* Write EEPROM address, operation, register address and value to the register */
    if(onewire_write_byte(port, data, len) == -1)
    {
        return -1;
    }
    return 0;

}

int ds2775g_read_register(onewire_port_t port, uint8_t register_address, uint8_t *data_read)
{

    uint8_t read_command[3] = {skip_address, read_data, register_address};

    /* Generate reset, sends the general address (0xCC) and the read command (0x69) */
    if(ds2775g_write_data(port, read_command, 0x3) == -1)
    {
        return -1;
    }

    /* Read data */
    if(onewire_read_byte(port, data_read, 0x1) == -1)
    {
        return -1;
    }

    return 0;

}

/*  Write 3Ah to battery accumulated current */
int write_accumulated_current_max_value(onewire_port_t port)
{

    uint8_t acc_write_msb[4] = {skip_address, write_data, accumulated_current_MSB_register, ACCUMULATED_CURRENT_MSB};
    uint8_t acc_copy_msb[3] = {skip_address, copy_data, accumulated_current_MSB_register};
    uint8_t acc_write_lsb[4] = {skip_address, write_data, accumulated_current_LSB_register, ACCUMULATED_CURRENT_LSB};
    uint8_t acc_copy_lsb[3] = {skip_address, copy_data, accumulated_current_LSB_register};

    /* Write ACCUMULATED_CURRENT_MSB to the accumulated current MSB register */
    if (ds2775g_write_data(port, acc_write_msb, 0x4) == -1)
    {
        return -1;
    }

    /* Copy the data from EEPROM shadow RAM  to EEPROM */
    if (ds2775g_write_data(port, acc_copy_msb, 0x3) == -1)
    {
        return -1;
    }

    /* Write ACCUMULATED_CURRENT_LSB to the accumulated current LSB register */
    if (ds2775g_write_data(port, acc_write_lsb, 0x4) == -1)
    {
        return -1;
    }

    /* Copy the data from EEPROM shadow RAM  to EEPROM */
    if (ds2775g_write_data(port, acc_copy_lsb, 0x3) == -1)
    {
        return -1;
    }

    return 0;
}

/** \} End of ds2775g group */
