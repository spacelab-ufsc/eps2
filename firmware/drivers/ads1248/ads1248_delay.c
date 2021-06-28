/*
 * ads1248_delay.c
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
 * \brief ADS1248 driver delay implementation.
 * 
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * 
 * \version 0.1.2
 * 
 * \date 2021/01/29
 * 
 * \defgroup ads1248_delay Delay
 * \ingroup ads1248
 * \{
 */

#include <FreeRTOS.h>
#include <task.h>

#include <config/config.h>

#include "ads1248.h"

void ads1248_delay(uint8_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

/** \} End of si446x_delay group */