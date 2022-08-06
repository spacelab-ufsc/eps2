/*
 * ttc.c
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
 * \brief TTC device implementation.
 *
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * \author Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 *
 * \version 0.2.29
 *
 * \date 22/04/2021
 *
 * \addtogroup ttc
 * \{
 */

#include <stdbool.h>

#include <system/sys_log/sys_log.h>

#include "ttc.h"

#define TTC_CRC8_INITIAL_VALUE          0       /**< CRC8-CCITT initial value. */
#define TTC_CRC8_POLYNOMIAL             0x07    /**< CRC8-CCITT polynomial. */

ttc_config_t ttc_config = {0};

/**
 * \brief Computes the CRC-8 of a sequence of bytes.
 *
 * \param[in] data is an array of data to compute the CRC-8.
 *
 * \param[in] len is the number of bytes of the given array.
 *
 * \return The computed CRC-8 value of the given data.
 */
uint8_t ttc_crc8(uint8_t *data, uint8_t len);

/**
 * \brief Checks the CRC value of a given sequence of bytes.
 *
 * \param[in] data is the data to check the CRC.
 *
 * \param[in] len is the number of bytes to check the CRC value.
 *
 * \param[in] crc is the CRC-8 value to check.
 *
 * \return TRUE/FALSE if the given CRC value is correct or not.
 */
bool ttc_check_crc(uint8_t *data, uint8_t len, uint8_t crc);


int ttc_init(void)
{
    sys_log_print_event_from_module(SYS_LOG_INFO, TTC_MODULE_NAME, "Initializing TTC device...");
    sys_log_new_line();

    /* TTC configuration */
    ttc_config.uart_port   = UART_PORT_0;
    ttc_config.uart_config = (uart_interrupt_config_t){.baudrate=115200, .data_bits=8, .parity=UART_NO_PARITY, .stop_bits=UART_ONE_STOP_BIT};

    if (uart_interrupt_init(ttc_config.uart_port, ttc_config.uart_config) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, TTC_MODULE_NAME, "Error during the initialization!");
        sys_log_new_line();
        
        return -1;
    }

    if (uart_interrupt_enable(ttc_config.uart_port) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, TTC_MODULE_NAME, "Error during the initialization!");
        sys_log_new_line();
        
        return -1;
    }

    return 0;
}

int ttc_decode(uint8_t *adr, uint32_t *val, uint8_t *cmd) 
{
	uint8_t buf[UART_RX_BUFFER_MAX_SIZE] = {0};
    uint8_t received_size = uart_received_data_size;

	for (int i = 0; i < received_size; i++)
	{
		buf[i] = uart_rx_buffer[i];
	}

	if(ttc_check_crc(buf, received_size - 1U, buf[received_size - 1U]) == true)
	{
		switch(received_size) 
		{
			case TTC_COMMAND_WRITE_SIZE:
			    *adr = buf[0];
			    *val = ((uint32_t)buf[1] << 24) |
			    	   ((uint32_t)buf[2] << 16) |
			    	   ((uint32_t)buf[3] << 8)  |
			    	   ((uint32_t)buf[4] << 0);
			   	*cmd = TTC_COMMAND_WRITE;
				break;
			case TTC_COMMAND_READ_SIZE:
				*adr = buf[0];
			    *val = 0;
			   	*cmd = TTC_COMMAND_READ;
				break;
			default:
				sys_log_print_event_from_module(SYS_LOG_ERROR, TTC_MODULE_NAME, "Invalid command received (CMD)!");
        		sys_log_new_line();
				
				return -1;
		}
	}
	else 
	{
		sys_log_print_event_from_module(SYS_LOG_ERROR, TTC_MODULE_NAME, "Invalid command received (CRC)!");
        sys_log_new_line();
		
		return -1;
	}

    return 0;
}

int ttc_answer(uint8_t adr, uint32_t val) 
{
	uint8_t buf[1+4+1] = {0};

    buf[0] = adr;
    buf[1] = (val >> 24) & 0xFF;
    buf[2] = (val >> 16) & 0xFF;
    buf[3] = (val >> 8)  & 0xFF;
    buf[4] = (val >> 0)  & 0xFF;
    buf[5] = ttc_crc8(buf, 5);

    if (uart_interrupt_write(ttc_config.uart_port, buf, 6) != 0)
    {
        return -1;
    }

    return 0;
}

uint8_t ttc_crc8(uint8_t *data, uint8_t len)
{
    uint8_t crc = TTC_CRC8_INITIAL_VALUE;

    while(len--)
    {
        crc ^= *data++;

        uint8_t j = 0;
        for (j=0; j<8; j++)
        {
            crc = (crc << 1) ^ ((crc & 0x80)? TTC_CRC8_POLYNOMIAL : 0);
        }

        crc &= 0xFF;
    }

    return crc;
}

bool ttc_check_crc(uint8_t *data, uint8_t len, uint8_t crc)
{
    if (crc != ttc_crc8(data, len))
    {
        return false;
    }

    return true;
}

/** \} End of ttc group */


