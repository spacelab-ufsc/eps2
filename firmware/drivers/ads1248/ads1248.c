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
 * \version 0.1.4
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
    
    ads1248_reset(config, ADS1248_RESET_CMD); // Sends reset command to make sure the device is properly reset after power up;

    ads1248_write_cmd(config, ADS1248_CMD_SDATAC); // Sends stop read data continuous mode command;

    ads1248_write_cmd(config, ADS1248_CMD_WREG); // Sends WREG command to configure device;

    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        ads1248_write_cmd(config, ADS1248_CMD_RREG); // Sends RREG command to read device configuration;
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */

    return ADS1248_SUCCESS;
}

int ads1248_reset(ads1248_config_t *config, ads1248_reset_mode_t mode)
{
    if (mode != 0) // if the reset mode is by command (ADS1248_RESET_CMD = 1)
    {
        ads1248_write_cmd(config, ADS1248_CMD_RESET);  
    }
    else           // if the reset mode is using the reset pin (ADS1248_RESET_PIN = 0)
    {
        gpio_set_state(config->reset_pin, false);
        
        // Add RESET pulse duration of 4 tclk?

        gpio_set_state(config->reset_pin, true);
    }
    
    ads1248_delay(1); // 1 ms delay time for SCLK rising edge (start of serial interface communication) after RESET rising edge
    
    return ADS1248_RESET;
}

int ads1248_set_powerdown_mode(ads1248_config_t *config, ads1248_power_down_t mode)
{
    if (mode != 0)  // if the power-down mode is by command (ADS1248_POWER_DOWN_CMD = 1)
    {
        spi_select_slave(config->spi_port, config->spi_cs, true); //  When using the SLEEP command, CS (active-low) must be held low for the duration of the power-down mode.
        ads1248_write_cmd(config, ADS1248_CMD_SLEEP);
    }
    else            // if the power-down mode is using the start pin (ADS1248_POWER_DOWN_PIN = 0)
    {
        gpio_set_state(config->start_pin, false);
    }
    return 0;
}

int ads1248_write_cmd(ads1248_config_t *config, ads1248_cmd_t cmd)
{
    uint8_t data_read_regs[17];
    uint8_t data_config_regs[17];

    switch(cmd)
    {
        case ADS1248_CMD_RREG:  

            data_read_regs[0] = cmd;                
            data_read_regs[1] = 0x0E;               // number of bytes to be sent minus 1
            data_read_regs[2] = ADS1248_CMD_NOP;    // no operation command to read the byte configuration of each register
            data_read_regs[3] = ADS1248_CMD_NOP;
            data_read_regs[4] = ADS1248_CMD_NOP;
            data_read_regs[5] = ADS1248_CMD_NOP;
            data_read_regs[6] = ADS1248_CMD_NOP;
            data_read_regs[7] = ADS1248_CMD_NOP;
            data_read_regs[8] = ADS1248_CMD_NOP;
            data_read_regs[9] = ADS1248_CMD_NOP;
            data_read_regs[10] = ADS1248_CMD_NOP;
            data_read_regs[11] = ADS1248_CMD_NOP;
            data_read_regs[12] = ADS1248_CMD_NOP;
            data_read_regs[13] = ADS1248_CMD_NOP;
            data_read_regs[14] = ADS1248_CMD_NOP;
            data_read_regs[15] = ADS1248_CMD_NOP;
            data_read_regs[16] = ADS1248_CMD_NOP;

            spi_read(config->spi_port, config->spi_cs, &data_read_regs, 17);
        break;

        case ADS1248_CMD_WREG:

        data_config_regs[0] = cmd;  // command WREG plus information to write to the first register MUX0;
        data_config_regs[1] = 0x0E; // number of bytes minus 1 to be writen by WREG command;
        data_config_regs[2] = 0x37; // value to register MUX0: burn out detect current off, positive input channel AIN3 (?) and negative channel AIN7;
        data_config_regs[3] = 0x00; // value to register VBIAS: bias voltage not enabled;
        data_config_regs[4] = 0x20; // value to register MUX1: internal reference always on, REFP0 and REFPN0 reference inputs and normal operation;
        data_config_regs[5] = 0x03; // value to register SYSO: data output rate of 40 SPS;
        data_config_regs[6] = 0x00; // value to register OFC0: stadard value on first offset calibration coefficient register;
        data_config_regs[7] = 0x00; // value to register OFC1: stadard value on second offset calibration coefficient register;
        data_config_regs[8] = 0x00; // value to register OFC2: stadard value on third offset calibration coefficient register;
        data_config_regs[9] = 0x00; // value to register FSC0: stadard value on first full-scale calibration coefficient register;
        data_config_regs[10] = 0x00; // value to register FSC1: stadard value on second full-scale calibration coefficient register;
        data_config_regs[11] = 0x00; // value to register FSC2: stadard value on third full-scale calibration coefficient register;
        data_config_regs[12] = 0x02; // value to register IDAC0: DOUT/DRDY pins functions only as data out and excitation output current magnitude to 100uA;
        data_config_regs[13] = 0x06; // value to register IDAC1: excitation outputs 1 to AIN0 and 2 to AIN6 pins;
        data_config_regs[14] = 0x00; // value to register GPIOCFG: GPIOS not enabled;
        data_config_regs[15] = 0x00; // value to register GPIODIR: GPIOS not enabled;
        data_config_regs[16] = 0x00; // value to register GPIODAT: GPIOS not enabled;
        
        spi_write(config->spi_port, config->spi_cs, &data_config_regs, 17);
        break;

        case ADS1248_CMD_WAKEUP:
        
        if(gpio_get_state(config->start_pin) != true) // If the START pin is held low, a WAKEUP command will not power up the device.
        {
          gpio_set_state(config->start_pin, true);  
        }
        
        spi_write(config->spi_port, config->spi_cs, &cmd, 1);
        break;

        default:
        spi_write(config->spi_port, config->spi_cs, &cmd, 1);
    }
    return 0;
}

/** \} End of ads1248 group */
