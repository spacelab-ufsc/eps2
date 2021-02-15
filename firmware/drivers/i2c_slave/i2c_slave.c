/*
 * i2c_slave.c
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
 * \brief I2C driver definition.
 * 
 * \author Vinícius Pimenta Bernardo <viniciuspibi@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 2021/02/10
 * 
 * \addtogroup i2c_slave
 * \{
 */

#include <hal/eusci_b_i2c.h>
#include <hal/gpio.h>
#include <hal/ucs.h>

#include <config/config.h>
#include <system/sys_log/sys_log.h>

#include "i2c_slave.h"

int i2c_slave_init(i2c_port_t port, i2c_config_t config)
{
    uint16_t base_address;
    switch (port)
    {
    case I2C_PORT_0:
        base_address = USCI_B0_BASE;
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN1 + GPIO_PIN2);
        break;
    case I2C_PORT_1:
        base_address = USCI_B1_BASE;
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P8, GPIO_PIN4 + GPIO_PIN5);
        break;
    case I2C_PORT_2:
        base_address = USCI_B2_BASE;
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN5 + GPIO_PIN6);
        break;
    default:
#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_MODULE_NAME, "Invalid port!");
        sys_log_new_line();
#endif             /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return -1; /* Invalid I2C port */
    }

    USCI_B_I2C_initSlaveParam param = {0};
    param.slaveAddress = EPS_SLAVE_ADDRESS;
    param.slaveAddressOffset = EUSCI_B_I2C_OWN_ADDRESS_OFFSET0;
    param.slaveOwnAddressEnable = EUSCI_B_I2C_OWN_ADDRESS_ENABLE;

    USCI_B_I2C_initSlave(base_address, &param);

    return 0;
}

int i2c_slave_enable(i2c_port_t port)
{
    uint16_t base_address;
    switch (port)
    {
    case I2C_PORT_0:
        base_address = USCI_B0_BASE;
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN1 + GPIO_PIN2);
        break;
    case I2C_PORT_1:
        base_address = USCI_B1_BASE;
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P8, GPIO_PIN4 + GPIO_PIN5);
        break;
    case I2C_PORT_2:
        base_address = USCI_B2_BASE;
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN5 + GPIO_PIN6);
        break;
    default:
#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_MODULE_NAME, "Invalid port!");
        sys_log_new_line();
#endif             /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return -1; /* Invalid I2C port */
    }
    EUSCI_B_I2C_enable(base_address);

    EUSCI_B_I2C_clearInterrupt(base_address, EUSCI_B_I2C_TRANSMIT_INTERRUPT0 +
                                                 EUSCI_B_I2C_STOP_INTERRUPT +
                                                 EUSCI_B_I2C_RECEIVE_INTERRUPT0);

    EUSCI_B_I2C_enableInterrupt(base_address, EUSCI_B_I2C_TRANSMIT_INTERRUPT0 +
                                                  EUSCI_B_I2C_STOP_INTERRUPT +
                                                  EUSCI_B_I2C_RECEIVE_INTERRUPT0);
    return 0;
};

int i2c_slave_disable(i2c_port_t port)
{
    uint16_t base_address;
    switch (port)
    {
    case I2C_PORT_0:
        base_address = USCI_B0_BASE;
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN1 + GPIO_PIN2);
        break;
    case I2C_PORT_1:
        base_address = USCI_B1_BASE;
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P8, GPIO_PIN4 + GPIO_PIN5);
        break;
    case I2C_PORT_2:
        base_address = USCI_B2_BASE;
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN5 + GPIO_PIN6);
        break;
    default:
#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_MODULE_NAME, "Invalid port!");
        sys_log_new_line();
#endif             /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return -1; /* Invalid I2C port */
    }
    EUSCI_B_I2C_disable(base_address);

    EUSCI_B_I2C_disableInterrupt(base_address, EUSCI_B_I2C_TRANSMIT_INTERRUPT0 +
                                                   EUSCI_B_I2C_STOP_INTERRUPT +
                                                   EUSCI_B_I2C_RECEIVE_INTERRUPT0);
    return 0;
};

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_B0_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_B0_VECTOR)))
#endif

    void
    USCIB0_ISR(void)
{
    switch (__even_in_range(UCB0IV, USCI_I2C_UCBIT9IFG))
    {
    case USCI_NONE: // No interrupts break;
        break;
    case USCI_I2C_UCALIFG: // Arbitration lost
        break;
    case USCI_I2C_UCNACKIFG: // NAK received (master only)
        break;
    case USCI_I2C_UCSTTIFG: // START condition detected with own address (slave mode only)
        break;
    case USCI_I2C_UCSTPIFG: // STOP condition detected (master & slave mode)
        break;
    case USCI_I2C_UCRXIFG3: // RXIFG3
        break;
    case USCI_I2C_UCTXIFG3: // TXIFG3
        break;
    case USCI_I2C_UCRXIFG2: // RXIFG2
        break;
    case USCI_I2C_UCTXIFG2: // TXIFG2
        break;
    case USCI_I2C_UCRXIFG1: // RXIFG1
        break;
    case USCI_I2C_UCTXIFG1: // TXIFG1
        break;
    case USCI_I2C_UCRXIFG0: // RXIFG0
        break;
    case USCI_I2C_UCTXIFG0: // TXIFG0
        break;
    case USCI_I2C_UCBCNTIFG: // Byte count limit reached (UCBxTBCNT)
        break;
    case USCI_I2C_UCCLTOIFG: // Clock low timeout - clock held low too long
        break;
    case USCI_I2C_UCBIT9IFG: // Generated on 9th bit of a transmit (for debugging)
        break;
    default:
        break;
    }
}

/** \} End of i2c_slave group */