/*
 * tps54540.c
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
 * \brief TPS54540 driver implementation.
 * 
 * \authors Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 2021/01/18
 * 
 * \addtogroup tps54540
 * \{
 */

#include "tps54540.h"
#include "system/sys_log/sys_log.h"

int tps54540_init(tps54540_config_t *config)
{
    gpio_init(config->enable_pin, (gpio_config_t){.mode = GPIO_MODE_OUTPUT});
}

int tps54540_enable(tps54540_config_t *config)
{
    return gpio_set_state(config->enable_pin, GPIO_STATE_HIGH);
}

int tps54540_disable(tps54540_config_t *config)
{
    return gpio_set_state(config->enable_pin, GPIO_STATE_LOW);
}

/** \} End of tps54540 group */