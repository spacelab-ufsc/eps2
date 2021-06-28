/*
 * media.c
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
 * \brief Media device implementation.
 *
 * \author Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 *
 * \version 0.1.0
 *
 * \date 02/15/2021
 *
 * \addtogroup media
 * \{
 */

#include <system/sys_log/sys_log.h>

#include <drivers/flash/flash.h>

#include "media.h"

int media_init()
{
    return flash_init();

}

int media_write(uint32_t adr, uint32_t *data, uint16_t len)
{
    /* Address index */
    adr += FLASH_SEG_A_ADR;

    uint16_t i = 0;
    for(i=0; i<len; i+=4)
    {
    flash_write_long(data[i], (uint32_t*)(adr + i));
    }

    return 0;

}

int media_read(uint32_t adr, uint32_t *data, uint16_t len)
{

    /* Address index */
    adr += FLASH_SEG_A_ADR;

    uint16_t i = 0;
    for(i=0; i<len; i+=4)
    {
        data[i] = flash_read_long((uint32_t*)(adr + i));
    }

    return 0;

}

int media_erase(uint32_t adr)
{

    flash_write_single(0xFF, (uint8_t*)adr);

    return 0;

}

/** \} End of media group */
