/*
 * tps54x0.c
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
 * \brief TPS54X0 driver implementation.
 * 
 * \authors Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * 
 * \version 0.1.3
 * 
 * \date 2021/01/18
 * 
 * \addtogroup tps54x0
 * \{
 */

#include "tps54x0.h"
#include "system/sys_log/sys_log.h"

int tps54x0_init(tps54x0_config_t *config)
{
    gpio_init(config->enable_pin, (gpio_config_t){.mode = GPIO_MODE_OUTPUT});
}

int tps54x0_enable(tps54x0_config_t *config)
{
    return gpio_set_state(config->enable_pin, GPIO_STATE_HIGH);
}

int tps54x0_disable(tps54x0_config_t *config)
{
    return gpio_set_state(config->enable_pin, GPIO_STATE_LOW);
}

/** \} End of tps54x0 group */