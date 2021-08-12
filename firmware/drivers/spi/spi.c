/*
 * spi.c
 * 
 * Copyright (C) 2021, SpaceLab.
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
 * \brief SPI driver implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * 
 * \version 0.2.14
 * 
 * \date 2021/02/17
 * 
 * \addtogroup spi
 * \{
 */

#include <hal/usci_a_spi.h>
#include <hal/usci_b_spi.h>
#include <hal/gpio.h>
#include <hal/ucs.h>

#include <config/config.h>
#include <system/sys_log/sys_log.h>

#include <drivers/gpio/gpio.h>

#include "spi.h"

int spi_setup_gpio(spi_port_t port)
{
    switch(port)
    {
        case SPI_PORT_0:
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN0 + GPIO_PIN3 + GPIO_PIN4);
            break;
        case SPI_PORT_1:
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P8, GPIO_PIN1 + GPIO_PIN2 + GPIO_PIN3);
            
            /* Init the only CS pin used */
            gpio_init(GPIO_PIN_59, (gpio_config_t){.mode=GPIO_MODE_OUTPUT});

            /* Set the only CS pin used to high */
            gpio_set_state(GPIO_PIN_59, true);
            
            break;
        case SPI_PORT_2:
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN1 + GPIO_PIN2 + GPIO_PIN3);
            break;
        case SPI_PORT_3:
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN1 + GPIO_PIN2 + GPIO_PIN3);
            break;
        case SPI_PORT_4:
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P8, GPIO_PIN1 + GPIO_PIN5 + GPIO_PIN6);
            break;
        case SPI_PORT_5:
            GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P9, GPIO_PIN1 + GPIO_PIN5 + GPIO_PIN6);
            break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, SPI_MODULE_NAME, "Error during GPIO configuration: Invalid port!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;  /* Invalid SPI port */
    }

    return 0;
}

int spi_select_slave(spi_port_t port, spi_cs_t cs, bool active)
{
    switch(port)
    {
        case SPI_PORT_0:
            /* TODO: Define the CS pins pf port 0 */
            break;
        case SPI_PORT_1:
            switch(cs)
            {
                case SPI_CS_0:      gpio_set_state(GPIO_PIN_59, !active);      break;
                default:
                #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
                    sys_log_print_event_from_module(SYS_LOG_ERROR, SPI_MODULE_NAME, "Error selecting a slave from port 1: Invalid CS pin!");
                    sys_log_new_line();
                #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
                    return -1;  /* Invalid CS pin */
            }

            break;
        case SPI_PORT_2:
            /* TODO: Define the CS pins pf port 2 */
            break;
        case SPI_PORT_3:
            /* TODO: Define the CS pins pf port 3 */
            break;
        case SPI_PORT_4:
            /* TODO: Define the CS pins pf port 4 */
            break;
        case SPI_PORT_5:
            /* TODO: Define the CS pins pf port 5 */
            break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, SPI_MODULE_NAME, "Error selecting a slave: Invalid port!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;  /* Invalid SPI port */
    }

    return 0;
}

int spi_init(spi_port_t port, spi_config_t config)
{
    uint16_t base_address;

    switch(port)
    {
        case SPI_PORT_0:    base_address = USCI_A0_BASE;    break;
        case SPI_PORT_1:    base_address = USCI_A1_BASE;    break;
        case SPI_PORT_2:    base_address = USCI_A2_BASE;    break;
        case SPI_PORT_3:    base_address = USCI_B0_BASE;    break;
        case SPI_PORT_4:    base_address = USCI_B1_BASE;    break;
        case SPI_PORT_5:    base_address = USCI_B2_BASE;    break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, SPI_MODULE_NAME, "Error during initialization: Invalid port!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;  /* Invalid SPI port */
    }

    if (spi_setup_gpio(port) != 0)
    {
        return -1;
    }

    if ((port == SPI_PORT_0) || (port == SPI_PORT_1) || (port == SPI_PORT_2))
    {
        USCI_A_SPI_initMasterParam spi_params;

        spi_params.selectClockSource        = USCI_A_SPI_CLOCKSOURCE_SMCLK;
        spi_params.clockSourceFrequency     = UCS_getSMCLK();
        spi_params.desiredSpiClock          = config.speed_hz;
        spi_params.msbFirst                 = USCI_A_SPI_LSB_FIRST;

        /* SPI mode */
        switch(config.mode)
        {
            case SPI_MODE_0:
                spi_params.clockPhase       = USCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
                spi_params.clockPolarity    = USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
                break;
            case SPI_MODE_1:
                spi_params.clockPhase       = USCI_A_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;
                spi_params.clockPolarity    = USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
                break;
            case SPI_MODE_2:
                spi_params.clockPhase       = USCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
                spi_params.clockPolarity    = USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
                break;
            case SPI_MODE_3:
                spi_params.clockPhase       = USCI_A_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;
                spi_params.clockPolarity    = USCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
                break;
            default:
            #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
                sys_log_print_event_from_module(SYS_LOG_ERROR, SPI_MODULE_NAME, "Error during initialization: Invalid mode!");
                sys_log_new_line();
            #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
                return -1;  /* Invalid SPI mode */
        }

        if (USCI_A_SPI_initMaster(base_address, &spi_params) != STATUS_SUCCESS)
        {
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, SPI_MODULE_NAME, "Error configuring as master!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;      /* Error initializing the SPI port */
        }

        USCI_A_SPI_enable(base_address);
    }
    else
    {
        USCI_B_SPI_initMasterParam spi_params;

        spi_params.selectClockSource        = USCI_B_SPI_CLOCKSOURCE_SMCLK;
        spi_params.clockSourceFrequency     = UCS_getSMCLK();
        spi_params.desiredSpiClock          = config.speed_hz;
        spi_params.msbFirst                 = USCI_B_SPI_LSB_FIRST;

        /* SPI mode */
        switch(config.mode)
        {
            case SPI_MODE_0:
                spi_params.clockPhase       = USCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
                spi_params.clockPolarity    = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
                break;
            case SPI_MODE_1:
                spi_params.clockPhase       = USCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;
                spi_params.clockPolarity    = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_LOW;
                break;
            case SPI_MODE_2:
                spi_params.clockPhase       = USCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT;
                spi_params.clockPolarity    = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
                break;
            case SPI_MODE_3:
                spi_params.clockPhase       = USCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT;
                spi_params.clockPolarity    = USCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH;
                break;
            default:
            #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
                sys_log_print_event_from_module(SYS_LOG_ERROR, SPI_MODULE_NAME, "Error during initialization: Invalid mode!");
                sys_log_new_line();
            #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
                return -1;  /* Invalid SPI mode */
        }

        if (USCI_B_SPI_initMaster(base_address, &spi_params) != STATUS_SUCCESS)
        {
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, SPI_MODULE_NAME, "Error configuring as master!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;      /* Error initializing the SPI port */
        }

        USCI_B_SPI_enable(base_address);
    }

    return 0;
}

void spi_write_byte(uint16_t base_address, uint8_t byte)
{
    if ((base_address == USCI_A0_BASE) || (base_address == USCI_A1_BASE) || (base_address == USCI_A2_BASE))
    {
        /* Wait until TX buffer ready */
        while(!USCI_A_SPI_getInterruptStatus(base_address, USCI_A_SPI_TRANSMIT_INTERRUPT));

        USCI_A_SPI_clearInterrupt(base_address, USCI_A_SPI_TRANSMIT_INTERRUPT);

        USCI_A_SPI_transmitData(base_address, byte);
    }
    else
    {
        /* Wait until TX buffer ready */
        while(!USCI_B_SPI_getInterruptStatus(base_address, USCI_B_SPI_TRANSMIT_INTERRUPT));

        USCI_B_SPI_clearInterrupt(base_address, USCI_B_SPI_TRANSMIT_INTERRUPT);

        USCI_B_SPI_transmitData(base_address, byte);
    }
}

uint8_t spi_read_byte(uint16_t base_address)
{
    if ((base_address == USCI_A0_BASE) || (base_address == USCI_A1_BASE) || (base_address == USCI_A2_BASE))
    {
        /* Wait until new data was written into RX buffer */
        while(!USCI_A_SPI_getInterruptStatus(base_address, USCI_A_SPI_RECEIVE_INTERRUPT));

        USCI_A_SPI_clearInterrupt(base_address, USCI_A_SPI_RECEIVE_INTERRUPT);

        return USCI_A_SPI_receiveData(base_address);
    }
    else
    {
        /* Wait until new data was written into RX buffer */
        while(!USCI_B_SPI_getInterruptStatus(base_address, USCI_B_SPI_RECEIVE_INTERRUPT));

        USCI_B_SPI_clearInterrupt(base_address, USCI_B_SPI_RECEIVE_INTERRUPT);

        return USCI_B_SPI_receiveData(base_address);
    }
}

uint8_t spi_transfer_byte(uint16_t base_address, uint8_t wb)
{
    spi_write_byte(base_address, wb);

    return spi_read_byte(base_address);
}

int spi_write(spi_port_t port, spi_cs_t cs, uint8_t *data, uint16_t len)
{
    uint16_t base_address;

    switch(port)
    {
        case SPI_PORT_0:    base_address = USCI_A0_BASE;    break;
        case SPI_PORT_1:    base_address = USCI_A1_BASE;    break;
        case SPI_PORT_2:    base_address = USCI_A2_BASE;    break;
        case SPI_PORT_3:    base_address = USCI_B0_BASE;    break;
        case SPI_PORT_4:    base_address = USCI_B1_BASE;    break;
        case SPI_PORT_5:    base_address = USCI_B2_BASE;    break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, SPI_MODULE_NAME, "Error during writing: Invalid port!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;  /* Invalid SPI port */
    }

    /* Enable the CS pin */
    if (spi_select_slave(port, cs, true) != 0)
    {
        return -1;  /* Invalid CS pin */
    }

    /* Write data */
    while(len--)
    {
        spi_transfer_byte(base_address, *data++);
    }

    /* Disable the CS pin */
    spi_select_slave(port, cs, false);

    return 0;
}

int spi_read(spi_port_t port, spi_cs_t cs, uint8_t *data, uint16_t len)
{
    uint16_t base_address;

    switch(port)
    {
        case SPI_PORT_0:    base_address = USCI_A0_BASE;    break;
        case SPI_PORT_1:    base_address = USCI_A1_BASE;    break;
        case SPI_PORT_2:    base_address = USCI_A2_BASE;    break;
        case SPI_PORT_3:    base_address = USCI_B0_BASE;    break;
        case SPI_PORT_4:    base_address = USCI_B1_BASE;    break;
        case SPI_PORT_5:    base_address = USCI_B2_BASE;    break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, SPI_MODULE_NAME, "Error during reading: Invalid port!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;  /* Invalid SPI port */
    }

    /* Enable the CS pin */
    if (spi_select_slave(port, cs, true) != 0)
    {
        return -1;  /* Invalid CS pin */
    }

    /* Read data */
    while(len--)
    {
        *data++ = spi_transfer_byte(base_address, 0);
    }

    /* Disable the CS pin */
    spi_select_slave(port, cs, false);

    return 0;
}

int spi_transfer(spi_port_t port, spi_cs_t cs, uint8_t *wd, uint8_t *rd, uint16_t len)
{
    uint16_t base_address;

    switch(port)
    {
        case SPI_PORT_0:    base_address = USCI_A0_BASE;    break;
        case SPI_PORT_1:    base_address = USCI_A1_BASE;    break;
        case SPI_PORT_2:    base_address = USCI_A2_BASE;    break;
        case SPI_PORT_3:    base_address = USCI_B0_BASE;    break;
        case SPI_PORT_4:    base_address = USCI_B1_BASE;    break;
        case SPI_PORT_5:    base_address = USCI_B2_BASE;    break;
        default:
            return -1;  /* Invalid SPI port */
    }

    /* Enable the CS pin */
    if (spi_select_slave(port, cs, true) != 0)
    {
        return -1;  /* Invalid CS pin */
    }

    /* Transfer data (write and read) */
    while(len--)
    {
        *rd++ = spi_transfer_byte(base_address, *wd++);
    }

    /* Disable the CS pin */
    spi_select_slave(port, cs, false);

    return 0;
}

/** \} End of spi group */
