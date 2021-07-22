/*
 * sl_obdh2.c
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
 * \brief SpaceLab OBDH 2.0 driver implementation.
 * 
 * \author Andre M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * 
 * \version 0.2.1
 * 
 * \date 2021/06/30
 * 
 * \addtogroup sl_obdh2
 * \{
 */

#include <stdbool.h>

#include <drivers/tca4311a/tca4311a.h>
#include <drivers/i2c/i2c.h>
#include <drivers/i2c_slave/i2c_slave.h>
#include <drivers/gpio/gpio.h>

#include "sl_obdh2.h"

#define SL_OBDH2_CRC8_INITIAL_VALUE          0       /**< CRC8-CCITT initial value. */
#define SL_OBDH2_CRC8_POLYNOMIAL             0x07    /**< CRC8-CCITT polynomial. */


int sl_obdh2_init(sl_obdh2_config_t config)
{
    if (tca4311a_init(config, true) != TCA4311A_READY)
    {
        return -1;      /* Error initializing the I2C port buffer CI*/
    }

    if (i2c_slave_init(config.i2c_port) != 0)
    {
#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, SL_OBDH2_MODULE_NAME, "Error initializing I2C as slave!");
        sys_log_new_line();
#endif             /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return -1;
    }

    if (i2c_slave_set_mode(config.i2c_port, I2C_RECEIVE_MODE) != 0)
    {
#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, SL_OBDH2_MODULE_NAME, "Error setting I2C slave mode!");
        sys_log_new_line();
#endif             /* CONFIG_DRIVERS_DEBUG_ENABLED */
    }

    if (i2c_slave_enable(config.i2c_port) != 0)
    {
#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, SL_OBDH2_MODULE_NAME, "Error enabling I2C slave!");
        sys_log_new_line();
#endif             /* CONFIG_DRIVERS_DEBUG_ENABLED */
    }

    return 0;
}

int sl_obdh2_answer(sl_obdh2_config_t config, uint8_t adr, uint32_t val)
{
/*    
    uint8_t buf[1+4+1] = {0};

    buf[0] = adr;
    buf[1] = (val >> 24) & 0xFF;
    buf[2] = (val >> 16) & 0xFF;
    buf[3] = (val >> 8)  & 0xFF;
    buf[4] = (val >> 0)  & 0xFF;
    buf[5] = sl_obdh2_crc8(buf, 5);

    if (tca4311a_write(config, SL_OBDH2_SLAVE_ADR, buf, 6) != TCA4311A_READY)
    {
        return -1;
    }

    return 0;
*/
    return -1;
}

uint8_t sl_obdh2_crc8(uint8_t *data, uint8_t len)
{
    uint8_t crc = SL_OBDH2_CRC8_INITIAL_VALUE;

    while(len--)
    {
        crc ^= *data++;

        uint8_t j = 0;
        for (j=0; j<8; j++)
        {
            crc = (crc << 1) ^ ((crc & 0x80)? SL_OBDH2_CRC8_POLYNOMIAL : 0);
        }

        crc &= 0xFF;
    }

    return crc;
}

bool sl_obdh2_check_crc(uint8_t *data, uint8_t len, uint8_t crc)
{
    if (crc != sl_obdh2_crc8(data, len))
    {
        return false;
    }

    return true;
}

/** \} End of sl_obdh2 group */
