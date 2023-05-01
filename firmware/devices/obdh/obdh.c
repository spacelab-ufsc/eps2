/*
 * obdh.c
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
 * \brief OBDH device implementation.
 *
 * \author Andre M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * \author Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 * \author Jo�o Cla�dio Elsen Barcellos <joaoclaudiobarcellos@gmail.com>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 0.2.40
 *
 * \date 2021/07/05
 *
 * \addtogroup obdh
 * \{
 */


#include <drivers/i2c_slave/i2c_slave.h>
#include <system/sys_log/sys_log.h>

#include "obdh.h"

#define OBDH_CRC8_INITIAL_VALUE          0       /**< CRC8-CCITT initial value. */
#define OBDH_CRC8_POLYNOMIAL             0x07    /**< CRC8-CCITT polynomial. */

obdh_config_t obdh_config = {0};

int obdh_init(void)
{
    sys_log_print_event_from_module(SYS_LOG_INFO, OBDH_MODULE_NAME, "Initializing OBDH device.");
    sys_log_new_line();

    /* OBDH configuration */
    obdh_config.i2c_port     = I2C_PORT_2;
    obdh_config.i2c_config   = (i2c_config_t){.speed_hz=100000};
    obdh_config.en_pin       = GPIO_PIN_66;
    obdh_config.ready_pin    = GPIO_PIN_69;

    if (tca4311a_init(obdh_config, true) != TCA4311A_READY)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, OBDH_MODULE_NAME, "Error during the initialization (I2C buffer init)!");
        sys_log_new_line();

        return -1;      /* Error initializing the I2C port buffer CI*/
    }

    if (i2c_slave_init(obdh_config.i2c_port, EPS_SLAVE_ADDRESS) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, OBDH_MODULE_NAME, "Error during the initialization (I2C slave init)!");
        sys_log_new_line();

        return -1;
    }

    if (i2c_slave_enable() != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, OBDH_MODULE_NAME, "Error during the initialization (I2C slave enable)!");
        sys_log_new_line();

        return -1;
    }

    return 0;
}

int obdh_decode(uint8_t *adr, uint32_t *val, uint8_t *cmd)
{
    int err = 0;

    uint8_t buf[I2C_RX_BUFFER_MAX_SIZE] = {0};
    uint16_t received_size = 0;

    if (i2c_slave_read(buf, &received_size) == 0)
    {
        if (obdh_check_crc(buf, received_size - 1U, buf[received_size - 1U]) == true)
        {
            switch(received_size)
            {
                case OBDH_COMMAND_WRITE_SIZE:
                    *adr = buf[0];
                    *val = ((uint32_t)buf[1] << 24) |
                           ((uint32_t)buf[2] << 16) |
                           ((uint32_t)buf[3] << 8)  |
                           ((uint32_t)buf[4] << 0);
                    *cmd = OBDH_COMMAND_WRITE;

                    break;
                case OBDH_COMMAND_READ_SIZE:
                    *adr = buf[0];
                    *val = 0;
                    *cmd = OBDH_COMMAND_READ;

                    break;
                default:
                    sys_log_print_event_from_module(SYS_LOG_ERROR, OBDH_MODULE_NAME, "Invalid command received (CMD)!");
                    sys_log_new_line();

                    err = -1;

                    break;
            }
        }
        else
        {
            sys_log_print_event_from_module(SYS_LOG_ERROR, OBDH_MODULE_NAME, "Invalid command received (CRC)!");
            sys_log_new_line();

            err = -1;
        }
    }
    else
    {
        err = -1;
    }

    return err;
}

int obdh_write_output_buffer(uint8_t adr, uint32_t val)
{
    uint8_t buf[1 + 4 + 1] = {0};

    buf[0] = adr;
    buf[1] = (val >> 24) & 0xFF;
    buf[2] = (val >> 16) & 0xFF;
    buf[3] = (val >> 8)  & 0xFF;
    buf[4] = (val >> 0)  & 0xFF;
    buf[5] = obdh_crc8(buf, 5);

    return i2c_slave_write(buf, 6);
}

uint8_t obdh_crc8(uint8_t *data, uint8_t len)
{
    uint8_t crc = OBDH_CRC8_INITIAL_VALUE;

    uint8_t i = 0U;
    for(i = 0; i < len; i++)
    {
        crc ^= data[i];

        uint8_t j = 0U;
        for (j = 0U; j < 8U; j++)
        {
            crc = (crc << 1) ^ ((crc & 0x80U) ? OBDH_CRC8_POLYNOMIAL : 0U);
        }

        crc &= 0xFFU;
    }

    return crc;
}

bool obdh_check_crc(uint8_t *data, uint8_t len, uint8_t crc)
{
    if (crc != obdh_crc8(data, len))
    {
        return false;
    }

    return true;
}

/** \} End of obdh group */




