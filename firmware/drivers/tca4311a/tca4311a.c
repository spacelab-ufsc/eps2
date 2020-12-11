/*
 * tca4311a.c
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
 * \brief TCA4311A driver implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 2020/10/24
 * 
 * \addtogroup tca4311a
 * \{
 */

#include <config/config.h>
#include <system/sys_log/sys_log.h>

#include "tca4311a.h"

int tca4311a_init(tca4311a_config_t config, bool en)
{
    int res_i2c = i2c_init(config.i2c_port, config.i2c_config);

    int res_en = gpio_init(config.en_pin, (gpio_config_t){.mode=GPIO_MODE_OUTPUT});

    int res_ready = gpio_init(config.ready_pin, (gpio_config_t){.mode=GPIO_MODE_INPUT});

    if ((res_i2c != 0) || (res_en != 0) || (res_ready != 0))
    {
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, TCA4311A_MODULE_NAME, "Error during the initialization!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return TCA4311A_ERROR;
    }

    if (en)
    {
        return tca4311a_enable(config);
    }
    else
    {
        return tca4311a_disable(config);
    }
}

int tca4311a_enable(tca4311a_config_t config)
{
    if (gpio_set_state(config.en_pin, true) != 0)
    {
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, TCA4311A_MODULE_NAME, "Error during enable!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return TCA4311A_ERROR;
    }

    return tca4311a_is_ready(config);
}

int tca4311a_disable(tca4311a_config_t config)
{
    if (gpio_set_state(config.en_pin, false) != 0)
    {
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, TCA4311A_MODULE_NAME, "Error during disable!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return TCA4311A_ERROR;
    }

    return tca4311a_is_ready(config);
}

int tca4311a_is_ready(tca4311a_config_t config)
{
    int result = gpio_get_state(config.ready_pin);

    if (result == GPIO_STATE_HIGH)
    {
        return TCA4311A_READY;
    }
    else if (result == GPIO_STATE_LOW)
    {
        return TCA4311A_NOT_READY;
    }
    else
    {
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, TCA4311A_MODULE_NAME, "Error reading the state!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return TCA4311A_ERROR;
    }
}

int tca4311a_write(tca4311a_config_t config, i2c_slave_adr_t adr, uint8_t *data, uint16_t len)
{
    if (i2c_write(config.i2c_port, adr, data, len) != 0)
    {
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, TCA4311A_MODULE_NAME, "Error during writing!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return TCA4311A_ERROR;
    }

    return tca4311a_is_ready(config);
}

int tca4311a_read(tca4311a_config_t config, i2c_slave_adr_t adr, uint8_t *data, uint16_t len)
{
    if (i2c_read(config.i2c_port, adr, data, len) != 0)
    {
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, TCA4311A_MODULE_NAME, "Error during reading!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return TCA4311A_ERROR;
    }

    return tca4311a_is_ready(config);
}

int tca4311a_write_byte(tca4311a_config_t config, i2c_slave_adr_t adr, uint8_t byte)
{
    if (i2c_write(config.i2c_port, adr, &byte, 1) != 0)
    {
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, TCA4311A_MODULE_NAME, "Error writing a byte!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return TCA4311A_ERROR;
    }

    return tca4311a_is_ready(config);
}

int tca4311a_read_byte(tca4311a_config_t config, i2c_slave_adr_t adr, uint8_t *byte)
{
    if (i2c_read(config.i2c_port, adr, byte, 1) != 0)
    {
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, TCA4311A_MODULE_NAME, "Error reading a byte!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return TCA4311A_ERROR;
    }

    return tca4311a_is_ready(config);
}

/** \} End of tca4311a group */
