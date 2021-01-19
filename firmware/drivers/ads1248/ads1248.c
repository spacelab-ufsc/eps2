/*
 * ads1248.c
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
 * \brief ADS1248 driver implementation.
 * 
 * \authors Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * 
 * \version 0.1.3
 * 
 * \date 2020/10/24
 * 
 * \addtogroup ads1248
 * \{
 */

#include <config/config.h>
#include <system/sys_log/sys_log.h>

#include "ads1248.h"

void ads1248_delay(uint8_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

int ads1248_init(ads1248_config_t *config)
{
    ads1248_delay(16); // 16 ms delay to allow power supplies to settle and power-on reset to complete
    
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_INFO, ADS1248_MODULE_NAME, "Initializing the ADS1248...");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */

    int res_start = gpio_init(config->start_pin, (gpio_config_t){.mode=GPIO_MODE_OUTPUT});
    
    int res_reset = gpio_init(config->reset_pin, (gpio_config_t){.mode=GPIO_MODE_OUTPUT});
    
    int res_spi = spi_init(config->spi_port, config->spi_config);
    
    if ((res_start != 0) || (res_reset != 0) || (res_spi != 0))
    {
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, ADS1248_MODULE_NAME, "Error during the initialization!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return ADS1248_ERROR;
    }

    if (gpio_set_state(config->start_pin, true) != 0)
    {
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, ADS1248_MODULE_NAME, "Error during setting START pin to high state during initialization!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return ADS1248_ERROR;
    }

    if (spi_select_slave(config->spi_port, config->spi_cs, false) != 0)
    {
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, ADS1248_MODULE_NAME, "Error during setting CS pin to low state during initialization!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return ADS1248_ERROR;
    }
    
    // Delay time (10ns) for first SCLK rising edge after CS falling edge needed?
    
    ads1248_write_cmd(config, ADS1248_RESET_PIN); // Sends reset command to make sure the device is properly reset after power up;

    ads1248_delay(1); // 1 ms delay time for SCLK rising edge (start of serial interface communication) after RESET rising edge

    ads1248_write_cmd(config, ADS1248_CMD_SDATAC); // Sends stop read data continuous mode command;

    return ADS1248_READY;
}

int ads1248_reset(ads1248_config_t *config, ads1248_reset_mode_t mode)
{
    if (mode != 0) // if the reset mode is by command (ADS1248_RESET_CMD = 1)
    {
        if (ads1248_write_cmd(config, ADS1248_CMD_RESET) != 0);
            {
            #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
                sys_log_print_event_from_module(SYS_LOG_ERROR, ADS1248_MODULE_NAME, "Error sending RESET command!");
                sys_log_new_line();
            #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
                return ADS1248_ERROR;
            }
    }
    else        // if the reset mode is using the rest pin (ADS1248_RESET_PIN = 0)
    {
        if (gpio_set_state(config->reset_pin, true) != 0)
            {
            #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
                sys_log_print_event_from_module(SYS_LOG_ERROR, ADS1248_MODULE_NAME, "Error during setting RESET pin to high state!");
                sys_log_new_line();
            #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
                return ADS1248_ERROR;
            }
    }
    return ADS1248_RESET;
}

int ads1248_set_powerdown_mode(ads1248_config_t *config)
{
    return -1;
}

int ads1248_write_cmd(ads1248_config_t *config, ads1248_cmd_t cmd)
{
    return -1;
}

/** \} End of ads1248 group */
