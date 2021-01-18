/*
 * max9934.c
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
 * \brief MAX9934 driver implementation.
 * 
 * \authors Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * 
 * \version 0.1.2
 * 
 * \date 2021/01/17
 * 
 * \addtogroup max9934
 * \{
 */

#include "max9934.h"
#include "system/sys_log/sys_log.h"

int max9934_init(max9934_config_t *config)
{
#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
    sys_log_print_event_from_module(SYS_LOG_INFO, MAX9934_MODULE_NAME, "Initializing the MAX9934...");
    sys_log_new_line();
#endif /* CONFIG_DRIVERS_DEBUG_ENABLED */

    if (adc_init(config->adc_port, (adc_config_t){}) != 0)
    {
#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, MAX9934_MODULE_NAME, "Error initializing MAX9934!");
        sys_log_new_line();
#endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return -1;
    }

    return 0;
}

int max9934_enable(max9934_config_t *config)
{
    return gpio_set_state(config->cs_pin, GPIO_STATE_HIGH);
}

int max9934_disable(max9934_config_t *config)
{
    return gpio_set_state(config->cs_pin, GPIO_STATE_LOW);
}

int max9934_read(max9934_config_t *config, uint16_t *raw_val)
{
    return adc_read(config->adc_port, raw_val);
}

/** \} End of max9934 group */
