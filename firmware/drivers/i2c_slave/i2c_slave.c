/*
 * i2c_slave.c
 * 
 * Copyright The EPS 2.0 Contributors.
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
 * along with EPS 2.0. If not, see <http:/\/www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief I2C driver definition.
 * 
 * \author Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * \author Andre M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * \author Joao Claudio Elsen Barcellos <joaoclaudiobarcellos@gmail.com>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.44
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

/**
 * \brief Status (idle, RX or TX).
 */
typedef enum
{
    I2C_SLAVE_STATUS_IDLE=0,
    I2C_SLAVE_STATUS_RX,
    I2C_SLAVE_STATUS_TX
} i2c_slave_mode_t;

uint16_t i2c_slave_base_address = UINT16_MAX;

uint8_t i2c_rx_buffer[I2C_RX_BUFFER_MAX_SIZE] = {0};
//uint8_t i2c_rx_data_size = 0;
uint8_t i2c_rx_buffer_index = 0;

uint8_t i2c_tx_buffer[I2C_TX_BUFFER_MAX_SIZE] = {0};
uint8_t i2c_tx_buffer_data_size = 0;
uint8_t i2c_tx_buffer_index = 0;

uint8_t i2c_slave_status = I2C_SLAVE_STATUS_IDLE;

int i2c_slave_init(i2c_slave_port_t port, i2c_slave_address_t adr)
{
    int err = 0;

    switch(port)
    {
        case I2C_PORT_0:
            i2c_slave_base_address = USCI_B0_BASE;

            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN1 + GPIO_PIN2);

            break;
        case I2C_PORT_1:
            i2c_slave_base_address = USCI_B1_BASE;

            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P8, GPIO_PIN5 + GPIO_PIN6);

            break;
        case I2C_PORT_2:
            i2c_slave_base_address = USCI_B2_BASE;

            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN5 + GPIO_PIN6);

            break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_SLAVE_MODULE_NAME, "Invalid port!");
            sys_log_new_line();
        #endif             /* CONFIG_DRIVERS_DEBUG_ENABLED */
            err = -1;

            break;
    }

    if (err == 0)
    {
        USCI_B_I2C_initSlave(i2c_slave_base_address, adr);

        /* Setting the mode is only required during the initialization, the rest are automatically switched */
        USCI_B_I2C_setMode(i2c_slave_base_address, USCI_B_I2C_RECEIVE_MODE + USCI_B_I2C_TRANSMIT_MODE);
    }

    return err;
}

int i2c_slave_enable(void)
{
    int err = 0;

    switch(i2c_slave_base_address)
    {
        case USCI_B0_BASE:  break;
        case USCI_B1_BASE:  break;
        case USCI_B2_BASE:  break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_SLAVE_MODULE_NAME, "Invalid port!");
            sys_log_new_line();
        #endif             /* CONFIG_DRIVERS_DEBUG_ENABLED */
            err = -1;

            break;
    }

    if (err == 0)
    {
        USCI_B_I2C_enable(i2c_slave_base_address);
        USCI_B_I2C_clearInterrupt(i2c_slave_base_address, USCI_B_I2C_TRANSMIT_INTERRUPT + USCI_B_I2C_RECEIVE_INTERRUPT + USCI_B_I2C_STOP_INTERRUPT);
        USCI_B_I2C_enableInterrupt(i2c_slave_base_address, USCI_B_I2C_TRANSMIT_INTERRUPT + USCI_B_I2C_RECEIVE_INTERRUPT + USCI_B_I2C_STOP_INTERRUPT);
    }

    return err;
};

int i2c_slave_disable(void)
{
    int err = 0;

    switch(i2c_slave_base_address)
    {
        case USCI_B0_BASE:  break;
        case USCI_B1_BASE:  break;
        case USCI_B2_BASE:  break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_SLAVE_MODULE_NAME, "Invalid port!");
            sys_log_new_line();
        #endif             /* CONFIG_DRIVERS_DEBUG_ENABLED */
            err = -1;

            break;
    }

    if (err == 0)
    {
        USCI_B_I2C_disable(i2c_slave_base_address);
        USCI_B_I2C_disableInterrupt(i2c_slave_base_address, USCI_B_I2C_TRANSMIT_INTERRUPT + USCI_B_I2C_RECEIVE_INTERRUPT + USCI_B_I2C_STOP_INTERRUPT);
    }

    return err;
};

int i2c_slave_read(uint8_t *data, uint16_t *len)
{
    int err = 0;

    switch(i2c_slave_base_address)
    {
        case USCI_B0_BASE:  break;
        case USCI_B1_BASE:  break;
        case USCI_B2_BASE:  break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_SLAVE_MODULE_NAME, "Error during reading: Invalid port!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            err = -1;

            break;
    }

    if (err == 0)
    {
        memcpy(data, i2c_rx_buffer, i2c_rx_data_size);
    }

    return err;
}

int i2c_slave_write(uint8_t *data, uint16_t len)
{
    int err = 0;

    switch(i2c_slave_base_address)
    {
        case USCI_B0_BASE:  break;
        case USCI_B1_BASE:  break;
        case USCI_B2_BASE:  break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, I2C_SLAVE_MODULE_NAME, "Error during writing: Invalid port!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            err = -1;

            break;
    }

    if (err == 0)
    {
        memcpy(i2c_tx_buffer, data, len);

        i2c_tx_buffer_data_size = len;

        i2c_tx_buffer_index = 0;
    }

    return err;
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCI_B2_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(USCI_B2_VECTOR)))
#endif
void USCI_B2_ISR(void)
{
    switch(__even_in_range(UCB2IV, 12))
    {
        case USCI_I2C_UCRXIFG:
            i2c_slave_status = I2C_SLAVE_STATUS_RX;

            i2c_rx_buffer[i2c_rx_buffer_index] = USCI_B_I2C_slaveGetData(USCI_B2_BASE);

            i2c_rx_buffer_index++;

            if (i2c_rx_buffer_index >= I2C_RX_BUFFER_MAX_SIZE)
            {
                i2c_rx_buffer_index = 0;
            }
            break;
        case USCI_I2C_UCTXIFG:
            i2c_slave_status = I2C_SLAVE_STATUS_TX;

            USCI_B_I2C_slavePutData(USCI_B2_BASE, i2c_tx_buffer[i2c_tx_buffer_index]);

            i2c_tx_buffer_index++;

            if (i2c_tx_buffer_index == i2c_tx_buffer_data_size)
            {
                i2c_tx_buffer_index = 0;
            }
            break;
        case USCI_I2C_UCSTPIFG:
            i2c_rx_data_size = i2c_rx_buffer_index;
            i2c_rx_buffer_index = 0;

            /* xHigherPriorityTaskWoken must be initialised to pdFALSE. If calling
            xTaskNotifyFromISR() unblocks the handling task, and the priority of
            the handling task is higher than the priority of the currently running task,
            then xHigherPriorityTaskWoken will automatically get set to pdTRUE. */
            BaseType_t xHigherPriorityTaskWoken = pdFALSE;

            if (i2c_slave_status == I2C_SLAVE_STATUS_RX)
            {
                xTaskNotifyFromISR(xTaskParamServerHandle, I2C_SLAVE_NOTI_VAL_TO_I2C_RX_ISR, eSetBits, &xHigherPriorityTaskWoken);

                /* Force a context switch if xHigherPriorityTaskWoken is now set to pdTRUE. */
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
            }

            i2c_slave_status = I2C_SLAVE_STATUS_IDLE;

            break;
        default:
            break;
    }
}

/** \} End of i2c_slave group */
