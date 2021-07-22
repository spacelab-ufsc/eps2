/*
 * sl_ttc2.c
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
 * \brief SpaceLab EPS 2.0 driver implementation.
 *
 * \author Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 *
 * \version 0.2.1
 *
 * \date 2021/07/12
 *
 * \addtogroup sl_ttc2
 * \{
 */

#include <stdbool.h>

#include <drivers/uart/uart.h>
#include <drivers/gpio/gpio.h>

#include "sl_ttc2.h"

#define SL_TTC2_CRC8_INITIAL_VALUE          0       /**< CRC8-CCITT initial value. */
#define SL_TTC2_CRC8_POLYNOMIAL             0x07    /**< CRC8-CCITT polynomial. */


int sl_ttc2_init(sl_ttc2_config_t *config)
{
    return -1;
}

int sl_ttc2_answer(sl_ttc2_config_t *config, uint8_t adr, uint32_t val)
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

uint8_t sl_ttc2_crc8(uint8_t *data, uint8_t len)
{
    uint8_t crc = SL_TTC2_CRC8_INITIAL_VALUE;

    while(len--)
    {
        crc ^= *data++;

        uint8_t j = 0;
        for (j=0; j<8; j++)
        {
            crc = (crc << 1) ^ ((crc & 0x80)? SL_TTC2_CRC8_POLYNOMIAL : 0);
        }

        crc &= 0xFF;
    }

    return crc;
}

bool sl_ttc2_check_crc(uint8_t *data, uint8_t len, uint8_t crc)
{
    if (crc != sl_ttc2_crc8(data, len))
    {
        return false;
    }

    return true;
}

/** \} End of sl_ttc2 group */



