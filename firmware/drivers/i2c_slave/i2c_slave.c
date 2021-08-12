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
 * \author Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * 
 * \version 0.2.19
 * 
 * \date 2021/06/22
 * 
 * \addtogroup i2c_slave
 * \{
 */

#include <hal/usci_b_i2c.h>
#include <hal/gpio.h>

#include <config/config.h>
#include <system/sys_log/sys_log.h>

#include <app/tasks/param_server.h>

#include "i2c_slave.h"

uint8_t i2c_rx_buffer[I2C_RX_BUFFER_MAX_SIZE];
uint8_t i2c_received_data_size = 0;
uint8_t i2c_buffer_index = 0;

int i2c_slave_init(i2c_slave_port_t port)
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
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P8, GPIO_PIN5 + GPIO_PIN6);
        break;
    case I2C_PORT_2:
        base_address = USCI_B2_BASE;
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN5 + GPIO_PIN6);
        break;
    default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_SLAVE_MODULE_NAME, "Invalid port!");
            sys_log_new_line();
        #endif             /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return -1; /* Invalid I2C port */
    }

    USCI_B_I2C_initSlave(base_address, EPS_SLAVE_ADDRESS);

    /* Setting the mode is only required during the initialization, the rest are automatically switched */
    USCI_B_I2C_setMode(base_address, USCI_B_I2C_RECEIVE_MODE);

    return 0;
}

int i2c_slave_enable(i2c_slave_port_t port)
{
    uint16_t base_address;
    switch (port)
    {
    case I2C_PORT_0:
        base_address = USCI_B0_BASE;
        break;
    case I2C_PORT_1:
        base_address = USCI_B1_BASE;
        break;
    case I2C_PORT_2:
        base_address = USCI_B2_BASE;
        break;
    default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_SLAVE_MODULE_NAME, "Invalid port!");
            sys_log_new_line();
        #endif             /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return -1; /* Invalid I2C port */
    }

    USCI_B_I2C_enable(base_address);
    USCI_B_I2C_clearInterrupt(base_address,
        USCI_B_I2C_RECEIVE_INTERRUPT +
        USCI_B_I2C_STOP_INTERRUPT
    );
    USCI_B_I2C_enableInterrupt(base_address,
        USCI_B_I2C_RECEIVE_INTERRUPT +
        USCI_B_I2C_STOP_INTERRUPT
    );

    return 0;
};

int i2c_slave_disable(i2c_slave_port_t port)
{
    uint16_t base_address;
    switch (port)
    {
    case I2C_PORT_0:
        base_address = USCI_B0_BASE;
        break;
    case I2C_PORT_1:
        base_address = USCI_B1_BASE;
        break;
    case I2C_PORT_2:
        base_address = USCI_B2_BASE;
        break;
    default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_SLAVE_MODULE_NAME, "Invalid port!");
            sys_log_new_line();
        #endif             /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return -1;  /* Invalid I2C port */
    }

    USCI_B_I2C_disable(base_address);
    USCI_B_I2C_disableInterrupt(base_address,
        USCI_B_I2C_RECEIVE_INTERRUPT +
        USCI_B_I2C_STOP_INTERRUPT
    );

    return 0;
};

int i2c_slave_write(i2c_slave_port_t port, uint8_t *data, uint16_t len)
{
    uint16_t base_address;

    switch(port)
    {
        case I2C_PORT_0:   
            base_address = USCI_A0_BASE;    
            break;
        case I2C_PORT_1:   
            base_address = USCI_A1_BASE;    
            break;
        case I2C_PORT_2:   
            base_address = USCI_A2_BASE;    
            break;
        default:
            #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
                sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_SLAVE_MODULE_NAME, "Error during writing: Invalid port!");
                sys_log_new_line();
            #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;
    }

    uint16_t i = 0;
    for(i=0; i<len; i++)
    {
        USCI_B_I2C_slavePutData(base_address, data[i]);
    }

    return 0;
}


#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_B2_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_B2_VECTOR)))
#endif
void USCI_B2_ISR (void)
{
    switch (__even_in_range(UCB1IV,12))
    {
        case USCI_I2C_UCRXIFG:
            i2c_rx_buffer[i2c_buffer_index++] = USCI_B_I2C_slaveGetData(USCI_B2_BASE);
            break;
        case USCI_I2C_UCSTPIFG:     
            #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
                sys_log_print_event_from_module(SYS_LOG_INFO, I2C_SLAVE_MODULE_NAME, "Received data: ");
                for (int i = 0; i < i2c_buffer_index; i++)
                {
                    sys_log_print_hex(i2c_rx_buffer[i]);
                    sys_log_print_msg(",");
                }
                sys_log_new_line();
            #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */

            i2c_received_data_size = i2c_buffer_index;
            i2c_buffer_index = 0;

            /* xHigherPriorityTaskWoken must be initialised to pdFALSE.  If calling
            xTaskNotifyFromISR() unblocks the handling task, and the priority of
            the handling task is higher than the priority of the currently running task,
            then xHigherPriorityTaskWoken will automatically get set to pdTRUE. */
            BaseType_t xHigherPriorityTaskWoken = pdFALSE;

            xTaskNotifyFromISR(xTaskParamServerHandle, NOTIFICATION_VALUE_TO_I2C_ISR, eSetBits, &xHigherPriorityTaskWoken);

            /* Force a context switch if xHigherPriorityTaskWoken is now set to pdTRUE. */
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

            break;
        default:
            break;
    }
}

/** \} End of i2c_slave group */
