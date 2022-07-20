/*
 * ads1248.c
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
 * \brief ADS1248 driver implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * \author Joao Claudio Elsen Barcellos <joaoclaudiobarcellos@gmail.com>
 * 
 * \version 0.2.33
 * 
 * \date 2021/03/09
 * 
 * \addtogroup ads1248
 * \{
 */

#include <stddef.h>

#include <config/config.h>
#include <system/sys_log/sys_log.h>

#include "ads1248.h"

int ads1248_init(ads1248_config_t *config)
{
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_INFO, ADS1248_MODULE_NAME, "Initializing the ADS1248...");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */

    int res_start = gpio_init(config->start_pin, (gpio_config_t){.mode=GPIO_MODE_OUTPUT});
    
    int res_reset = gpio_init(config->reset_pin, (gpio_config_t){.mode=GPIO_MODE_OUTPUT});
    
    int res_spi = spi_init(config->spi_port, config->spi_config);
    
    if ((res_start != 0) || (res_start != 0) || (res_spi != 0))
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

    ads1248_reset(config, ADS1248_RESET_PIN);

    spi_select_slave(config->spi_port, SPI_CS_0, true);  /* Enable device communication (protocol specific) */

    ads1248_reset(config, ADS1248_RESET_CMD);

    ads1248_write_cmd(config, ADS1248_CMD_SDATAC, NULL, 0);

    ads1248_config_regs(config);

    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        uint8_t regs[18];
        ads1248_read_regs(config, regs);
        ads1248_delay(1);
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */

    spi_select_slave(config->spi_port, SPI_CS_0, true);  /* Enable device communication (protocol specific) */
    uint8_t cmd[2]={0};
    uint8_t dummy[2]={0};
    cmd[0] = ADS1248_CMD_SYNC;
    cmd[1] = ADS1248_CMD_SYNC;
    spi_transfer_no_cs(config->spi_port, cmd, dummy, 2);
    cmd[0] = ADS1248_CMD_SLEEP;
    spi_transfer_no_cs(config->spi_port, cmd, dummy, 1);

    return 0;
}

int ads1248_reset(ads1248_config_t *config, ads1248_reset_mode_t mode)
{
    if (mode != 0) /* if the reset mode is by command (ADS1248_RESET_CMD = 1) */
    {
        ads1248_write_cmd(config, ADS1248_CMD_RESET, NULL, 0);
        ads1248_delay(1);
    }
    else           /* if the reset mode is using the reset pin (ADS1248_RESET_PIN = 0) */
    {
        gpio_set_state(config->reset_pin, false);
        
        ads1248_delay(1); /* RESET pulse duration (minimal is 4 tclk (4*0.488u = 1.95us). 1ms is the lowest delay FreeRTOS can do) */

        gpio_set_state(config->reset_pin, true);
    }
    
    ads1248_delay(1);
    
    return 0;
}

int ads1248_config_regs(ads1248_config_t *config)
{
    uint8_t data_config_regs[18];
    uint8_t dummy[7]={0};

    data_config_regs[0] = ADS1248_CMD_WREG;  /* command WREG plus information to write to the first register MUX0 (0x00) */
    data_config_regs[1] = 0x03; /* number of bytes minus 1 to be written by WREG command */
    data_config_regs[2] = (ADS1248_POSITIVE_INPUTS << 3) | ADS1248_NEGATIVE_INPUT; /* value to register MUX0: burn out detect current off, number of positive input channel shifted and negative channel AIN7 */
    data_config_regs[3] = 0x00; /* value to register VBIAS: bias voltage not enabled */
    data_config_regs[4] = 0x20; /* value to register MUX1: internal reference always on, REFP0 and REFPN0 reference inputs and normal operation */
    data_config_regs[5] = 0x03; /* value to register SYSO: data output rate of 40 SPS */
    data_config_regs[6] = 0x00; /* value to register OFC0: standard value on first offset calibration coefficient register */
    data_config_regs[7] = 0x00; /* value to register OFC1: standard value on second offset calibration coefficient register */
    data_config_regs[8] = 0x00; /* value to register OFC2: standard value on third offset calibration coefficient register */
    data_config_regs[9] = 0x00; /* value to register FSC0: standard value on first full-scale calibration coefficient register */
    data_config_regs[10] = 0x00; /* value to register FSC1: standard value on second full-scale calibration coefficient register */
    data_config_regs[11] = 0x00; /* value to register FSC2: standard value on third full-scale calibration coefficient register */
    data_config_regs[12] = 0x02; /* value to register IDAC0: DOUT/DRDY pins functions only as data out and excitation output current magnitude to 100uA */
    data_config_regs[13] = 0x06; /* value to register IDAC1: excitation outputs 1 to AIN0 and 2 to AIN6 pins */
    data_config_regs[14] = 0x00; /* value to register GPIOCFG: GPIOS not enabled */
    data_config_regs[15] = 0x00; /* value to register GPIODIR: GPIOS not enabled */
    data_config_regs[16] = 0x00; /* value to register GPIODAT: GPIOS not enabled */
        
    spi_transfer_no_cs(config->spi_port, data_config_regs, dummy, 6); /* Writes to all registers in one half-duplex SPI communication */

    data_config_regs[0] = ADS1248_CMD_WREG | 0x0A;  /* command WREG plus information to write to the first register MUX0 (0x00) */
    data_config_regs[1] = 0x04; /* number of bytes minus 1 to be written by WREG command */
    data_config_regs[2] = 0x02; /* value to register IDAC0: DOUT/DRDY pins functions only as data out and excitation output current magnitude to 100uA */
    data_config_regs[3] = 0x06; /* value to register IDAC1: excitation outputs 1 to AIN0 and 2 to AIN6 pins */
    data_config_regs[4] = 0x00; /* value to register GPIOCFG: GPIOS not enabled */
    data_config_regs[5] = 0x00; /* value to register GPIODIR: GPIOS not enabled */
    data_config_regs[6] = 0x00; /* value to register GPIODAT: GPIOS not enabled */

    spi_transfer_no_cs(config->spi_port, data_config_regs, dummy, 7);

    return 0;
}

int ads1248_read_regs(ads1248_config_t *config, uint8_t *rd)
{
    uint8_t data_read_regs[18];

    data_read_regs[0] = ADS1248_CMD_RREG;
    data_read_regs[1] = 0x0E;               /* number of bytes to be sent minus 1 */
    data_read_regs[2] = ADS1248_CMD_NOP;    /* no operation command to read the byte configuration of each register */
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

    spi_transfer_no_cs(config->spi_port, data_read_regs, rd, 17);

    /* implement system log debug for registers configuration here or somewhere else */
    /*
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_INFO, ADS1248_MODULE_NAME, "ADS1248 Configuration registers values:");
        sys_log_new_line();
        for (uint8_t i = 2; i <= 15; i++)
        {
            sys_log_print_msg("Adress: ")
            sys_log_print_hex(rd[i]);
            sys_log_print_msg("\tValue: ")
            sys_log_print_hex(*rd[i]);
            sys_log_new_line();
        }
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */

    return 0;
}

int ads1248_read_data(ads1248_config_t *config, uint8_t *rd, uint8_t positive_channel)
{

    uint8_t select_channel_to_read[3] = {0};
    uint8_t select_channel_excitation_current[3] = {0};
    uint8_t data_read_conversion[4] = {0};
    uint8_t cmd[2] = {0};
    uint8_t dummy[4]={0};

    // Wake up device
    cmd[0] = ADS1248_CMD_WAKEUP;
    spi_transfer_no_cs(config->spi_port, cmd, dummy, 1);

    // Configure desired channel for conversion
    select_channel_to_read[0] = ADS1248_CMD_WREG; /* WREG command (0x40), since the last byte is zero it will write to the first register MUX0 (0x00) */
    select_channel_to_read[1] = 0x00;  /* number of bytes minus 1 to be writen by WREG command, in this case 1 byte will be 0 in hex */
    select_channel_to_read[2] = (positive_channel << 3) | ADS1248_NEGATIVE_INPUT; /* positive channel selection + the negative (reference) channel fixed to be AIN7*/

    spi_transfer_no_cs(config->spi_port, select_channel_to_read, dummy, 3); /* Multiplexes channel */

    select_channel_excitation_current[0] = 0x4B; /* WREG command (0x40) plus information to write to the IDAC1 register (0x4B) */
    select_channel_excitation_current[1] = 0x00;  /* number  of bytes minus 1 to be writen by WREG command, in this case 1 byte than 0 in hex */
    select_channel_excitation_current[2] = (positive_channel << 4) | positive_channel; /* output current to selected positive channel*/

    spi_transfer_no_cs(config->spi_port, select_channel_excitation_current, dummy, 3); /* Multiplexes channel */

    // Start a new conversion
    cmd[0] = ADS1248_CMD_SYNC;
    cmd[1] = ADS1248_CMD_SYNC;
    spi_transfer_no_cs(config->spi_port, cmd, dummy, 2);
    // Set device to enter power down mode
    cmd[0] = ADS1248_CMD_SLEEP;
    spi_transfer_no_cs(config->spi_port, cmd, dummy, 1);

    // Wait for conversion to finish
    ads1248_delay(50);

    data_read_conversion[0] = ADS1248_CMD_RDATA; /* commAnd read last ADC conversion */
    data_read_conversion[1] = ADS1248_CMD_NOP; /* 3 no operation commands to clockout data from the device without clocking in a command during SPI duplex communication*/
    data_read_conversion[2] = ADS1248_CMD_NOP;
    data_read_conversion[3] = ADS1248_CMD_NOP;
    
    // Read conversion result
    spi_transfer_no_cs(config->spi_port, data_read_conversion, rd, 4);


    return 0;
}

int ads1248_write_cmd(ads1248_config_t *config, ads1248_cmd_t cmd, uint8_t *rd, uint8_t positive_channel)
{
    switch(cmd)
    {
        case ADS1248_CMD_WREG:
            ads1248_config_regs(config);
            ads1248_delay(1);
            break;
        case ADS1248_CMD_RREG:  
            ads1248_read_regs(config, rd);
            ads1248_delay(1);
            break;
        case ADS1248_CMD_RDATA:
            ads1248_read_data(config, rd, positive_channel);
            ads1248_delay(1);
            break;
        case ADS1248_CMD_WAKEUP:
            if(gpio_get_state(config->start_pin) != true)
            {
                gpio_set_state(config->start_pin, true);
            }
            spi_write(config->spi_port, config->spi_cs, &cmd, 1);
            ads1248_delay(1);
            break;
        default:
            uint8_t dummy[1]={0};
            spi_transfer_no_cs(config->spi_port, &cmd, dummy, 1);
            ads1248_delay(1);
    }

    return 0;
}

int ads1248_set_powerdown_mode(ads1248_config_t *config, ads1248_power_down_t mode)
{
    if (mode != 0)  /* if the power-down mode is by command (ADS1248_POWER_DOWN_CMD = 1) */
    {
        ads1248_write_cmd(config, ADS1248_CMD_SLEEP, NULL, 0);
        ads1248_delay(1);
        spi_select_slave(config->spi_port, SPI_CS_0, true); /* CS (active-low) must be held low for the duration of the power-down mode to be able to receive some commands*/
    }
    else            /* if the power-down mode is using the start pin (ADS1248_POWER_DOWN_PIN = 0) */
    {
        gpio_set_state(config->start_pin, false);
    }
    return 0;
}

/** \} End of ads1248 group */
