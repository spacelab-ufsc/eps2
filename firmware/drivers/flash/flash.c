/*
 * flash.c
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
 * \brief Flash driver implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 2020/10/24
 * 
 * \addtogroup flash
 * \{
 */

#include <msp430.h>

#include "flash.h"

char *flash_ptr;

long *current_flash_ptr;

int flash_init()
{
    return 0;
}

void flash_write(uint8_t *data, uint16_t len)
{
    uint16_t i;

    if (FCTL3 & LOCKA)
    {
        FCTL3 = FWKEY | LOCKA;              /* Clear Lock bit and LockA */
    }
    else
    {
        FCTL3 = FWKEY;                      /* Clear Lock bit */
    }

    FCTL1 = FWKEY | WRT;                    /* Set WRT bit for write operation */
    for(i=0; i<len; i++)
    {
        *flash_ptr++ = data[i];             /* Write value to flash */

        while((FCTL3 & BUSY) == 1);         /* Check if Flash being used */
    }

    FCTL1 = FWKEY;                          /* Clear WRT bit */
    FCTL3 = FWKEY | LOCK | LOCKA;           /* Set LOCK bit */
}

void flash_write_single(uint8_t data, uint8_t *addr)
{
    if (FCTL3 & LOCKA)
    {
        FCTL3 = FWKEY | LOCKA;              /* Clear Lock bit and LockA */
    }
    else
    {
        FCTL3 = FWKEY;                      /* Clear Lock bit */
    }

    FCTL1 = FWKEY | WRT;                    /* Set WRT bit for write operation */
    *addr = data;                           /* Write value to flash */

    while((FCTL3 & BUSY) == 1);             /* Check if Flash being used */

    FCTL1 = FWKEY;                          /* Clear WRT bit */
    FCTL3 = FWKEY | LOCK | LOCKA;           /* Set LOCK bit */
}

uint8_t flash_read_single(uint8_t *addr)
{
    return *addr;
}

void flash_write_long(uint32_t data, uint32_t *addr)
{
    if (FCTL3 & LOCKA)
    {
        FCTL3 = FWKEY | LOCKA;              /* Clear Lock bit and LockA */
    }
    else
    {
        FCTL3 = FWKEY;                      /* Clear Lock bit */
    }

    FCTL1 = FWKEY | BLKWRT;                 /* Set WRT bit for write operation */
    *addr = data;                           /* Write value to flash */

    while((FCTL3 & BUSY) == 1);             /* Check if Flash being used */

    FCTL1 = FWKEY;                          /* Clear WRT bit */
    FCTL3 = FWKEY | LOCK | LOCKA;           /* Set LOCK bit */
}

uint32_t flash_read_long(uint32_t *addr)
{
    return *addr;
}

void flash_erase(uint32_t *region)
{
    uint32_t *erase_ptr = region;

    if (FCTL3 & LOCKA)
    {
        FCTL3 = FWKEY | LOCKA;              /* Clear Lock bit and LockA */
    }
    else
    {
        FCTL3 = FWKEY;                      /* Clear Lock bit */
    }

    switch((uint32_t)region)
    {
        case FLASH_BANK_0_ADR:  FCTL1 = FWKEY | MERAS;          break;
        case FLASH_BANK_1_ADR:  FCTL1 = FWKEY | MERAS;          break;
        case FLASH_BANK_2_ADR:  FCTL1 = FWKEY | MERAS;          break;
        case FLASH_BANK_3_ADR:  FCTL1 = FWKEY | MERAS;          break;
        case FLASH_SEG_A_ADR:   FCTL1 = FWKEY | ERASE;          break;
        case FLASH_SEG_B_ADR:   FCTL1 = FWKEY | ERASE;          break;
        case FLASH_SEG_C_ADR:   FCTL1 = FWKEY | ERASE;          break;
        case FLASH_SEG_D_ADR:   FCTL1 = FWKEY | ERASE;          break;
        case FLASH_MASS_ERASE:  FCTL1 = FWKEY | MERAS | ERASE;  break;
    }

    *erase_ptr = 0;

    while((FCTL3 & BUSY) == 1);

    FCTL1 = FWKEY;                          /* Clear WRT bit */
    FCTL3 = FWKEY | LOCK | LOCKA;           /* Set LOCK bit */
}

/** \} End of flash group */
