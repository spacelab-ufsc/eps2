/*
 * ads1248.h
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
 * \brief ADS1248 driver definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * 
 * \version 0.1.5
 * 
 * \date 2020/02/08
 * 
 * \defgroup ads1248 ADS1248
 * \ingroup drivers
 * \{
 */

#ifndef ADS1248_H_
#define ADS1248_H_

#include <drivers/spi/spi.h>
#include <drivers/gpio/gpio.h>

#define ADS1248_MODULE_NAME            "ADS1248"

#define ADS1248_RANGE       16777216    /**< ADS1248 resolution (24-bit). */

/* SPI Commands */
#define ADS1248_CMD_WAKEUP      0x00    /**< Exit power-down mode. */
#define ADS1248_CMD_SLEEP       0x02    /**< Enter power-down mode. */
#define ADS1248_CMD_SYNC        0x04    /**< Synchronize ADC conversions. */
#define ADS1248_CMD_RESET       0x06    /**< Reset to default values. */
#define ADS1248_CMD_NOP         0xFF    /**< No operation. */
#define ADS1248_CMD_RDATA       0x12    /**< Read data once. */
#define ADS1248_CMD_RDATAC      0x14    /**< Read data continuous mode. */
#define ADS1248_CMD_SDATAC      0x16    /**< Stop read data continuous mode. */
#define ADS1248_CMD_RREG        0x20    /**< Read from register rrrr. */
#define ADS1248_CMD_WREG        0x40    /**< Write to register rrrr. */
#define ADS1248_CMD_SYSOCAL     0x60    /**< System offset calibration. */
#define ADS1248_CMD_SYSGCAL     0x61    /**< System gain calibration. */
#define ADS1248_CMD_SELFOCAL    0x62    /**< Self offset calibration. */

/**
 * \brief ADS1248 configuration parameters.
 */
typedef struct
{
    spi_port_t spi_port;                /**< SPI port. */
    spi_cs_t spi_cs;                    /**< SPI Chip Select pin. */
    spi_config_t spi_config;            /**< SPI port configuration. */
    gpio_pin_t reset_pin;               /**< Reset pin. */
    gpio_pin_t start_pin;               /**< Start pin. */
} ads1248_config_t;

/**
 * \brief ADS1248 command type.
 */
typedef uint8_t ads1248_cmd_t;

/**
 * \brief ADS1248 power-down type.
 */
typedef uint8_t ads1248_power_down_t;

/**
 * \brief ADS1248 reset mode type.
 */
typedef uint8_t ads1248_reset_mode_t;

/**
 * \brief Reset modes.
 */
typedef enum
{
    ADS1248_RESET_PIN = 0,              /**< Reset pin. */
    ADS1248_RESET_CMD                   /**< Reset command. */
} ads1248_reset_e;

/**
 * \brief Power-down modes.
 */
typedef enum
{
    ADS1248_POWER_DOWN_PIN = 0,          /**< Start pin. */
    ADS1248_POWER_DOWN_CMD,              /**< Power-down command. */
} ads1248_power_e;

/**
 * \brief AD1248 states.
 */
typedef enum
{
    ADS1248_ERROR=-1,                  /**< Error during initialization. */
    ADS1248_SUCCESS,                     /**< The chip is ready. */
    ADS1248_RESET,                     /**< The chip is reset. */
} ads1248_status_e;

/**
 * \brief Milliseconds delay.
 * 
 * \param[in] ms is the time to delay in milliseconds.
 *
 * \return None.
 */
void ads1248_delay(uint8_t ms);

/**
 * \brief ADS1248 initialization.
 * 
 * First a 16 ms delay is implemented to allow power supplies to settle and power-on reset to complete.
 * Them the GPIO and SPI pins are initiated. 
 * The START is set to high and the SPI chip select (CS) pin is set to low to begin SPI communication.
 * Next the following commands are sent for the ADS1248 configuration:
 * - ADS1248_CMD_RESET: Reset command to make sure the device is properly reset after power up.
 * 1 ms delay time (minimunn of 0f 0.6ms) for SCLK rising edge (start of serial interface communication) after RESET rising edge.
 * - ADS1248_CMD_SDATAC: Stop read data continuous mode command.
 * - ADS1248_CMD_WREG: Configures the device parameters through registers.
 * If the driver debug is enabladed sends ADS1248_CMD_RREG: Reads the device's configuration registers values for sanity check.
 * - ADS1248_CMD_SYNC: Starts new ADC conversion.
 *
 * \param[in,out] config is a pointer to the ADS1248 configuration parameters.
 *
 * \return The status/error code.
 */
int ads1248_init(ads1248_config_t *config);

/**
 * \brief Resets the device.
 *
 * The ADS1248 can be reset using a GPIO activation on its RESET pin or with a the reset command (ADS1248_CMD_RESET). 
 * When the RESET pin goes low, the device is immediately reset. When the RESET pin goes back to high a 1 ms delay time (minimunn of 0f 0.6ms) is necessary before starting a SPI communication.
 *
 * \param[in,out] config is a pointer to the configuration parameters of the device.
 *
 * \param[in] mode is the reset mode. It can be:
 * \parblock
 *      -\b ADS1248_RESET_PIN
 *      -\b ADS1248_RESET_CMD
 *      .
 * \endparblock
 *
 * \return The status/error code.
 */
int ads1248_reset(ads1248_config_t *config, ads1248_reset_mode_t mode);

/**
 * \brief Configuration of the ADS1248 registers.
 *
 * To configure the ADS1248 the ADS1248_CMD_WREG command must be sent via half-duplex SPI communication to the device.
 * The first byte is the command itself (0x40), if the last 4 bits are not specified it will begin writing to the first register MUX0 (0x00).
 * The second byte is the leght of bytes to be sent minus 1. ADS1248 has 15 configuring registers, so to write to all registers on one SPI transmission it needs 0x0E (15 - 1 = 14 in decimal). 
 * The next bytes are the specific configuration values for each register.
 * When the last byte is sent via SPI the CS (active-low) is set high ending communication. 
 *
 * \param[in,out] config is a pointer to the configuration parameters of the device.
 *
 * \return The status/error code.
 */
int ads1248_config_regs(ads1248_config_t *config);

/**
 * \brief Reads ADS1248 registers configuration.
 *
 * To read the ADS1248 registers configuration the ADS1248_CMD_RREG command must be sent via full-duplex SPI communication to the device.
 * Similar to the the ADS1248_CMD_WREG command, first byte is the command itself (0x20), if the last 4 bits are not specified it will begin reading first register MUX0 (0x00).
 * The second byte is the leght of bytes to be read minus 1. ADS1248 has 15 configuring registers, so to read all registers on one SPI transmission it needs 0x0E (15 - 1 = 14 in decimal). 
 * The next bytes sent are no operation commands (ADS1248_CMD_NOP) to maintain full-duplex SPI communication when receiving data from the device.
 * When the last byte is sent via SPI the CS (active-low) is set high ending communication. 
 *
 * \param[in,out] config is a pointer to the configuration parameters of the device.
 *
 * \param[in,out] rd rd is a pointer to store the read data during the SPI transfer.
 *
 * \return The status/error code.
 */
int ads1248_read_regs(ads1248_config_t *config, uint8_t *rd);

/**
 * \brief Reads last conversion of ADS1248.
 *
 * To read the ADS1248 last conversion the ADS1248_CMD_RDATA command must be sent via full-duplex SPI communication to the device.
 * The first byte is the command itself (0x40), the conversion result is read out by sending 3 no operation command (NOP) during 24 SCLKs, each NOP is sent in 8 SCLKs. 
 *
 * \param[in,out] config is a pointer to the configuration parameters of the device.
 *
 * \param[in,out] rd rd is a pointer to store the read data during the SPI transfer.
 *
 * \return The status/error code.
 */
int ads1248_read_data(ads1248_config_t *config, uint8_t *rd);

/**
 * \brief Writes a command to the device.
 *
 * All commands to be sent from master to the ADS1248 slave though SPI is done in this function.
 * Some commands require addiotional bytes besides the command byte to be sent, this is the case for the ADS1248_CMD_WREG, ADS1248_CMD_WREG and ADS1248_CMD_RDATA commands. 
 * For these 3 commands the implementation is done in separate functions.
 * All the other commands only require its byte to be sent.
 *
 * If the START pin is held low, a WAKEUP command will not power up the device.
 *
 * When the START pin is low or the device is in power-down mode, only the RDATA, RDATAC, SDATAC, WAKEUP, and NOP commands can be issued.
 *
 * \param[in,out] config is a pointer to the configuration parameters of the device.
 *
 * \param[in,out] data is a optional pointer only for WREG, RREG and RDATA commands. For the case of WREG, the variable 
 *
 * \param[in] cmd is the command to write. It can be:
 * \parblock
 *      -\b ADS1248_CMD_WAKEUP
 *      -\b ADS1248_CMD_SLEEP
 *      -\b ADS1248_CMD_SYNC
 *      -\b ADS1248_CMD_RESET
 *      -\b ADS1248_CMD_NOP
 *      -\b ADS1248_CMD_RDATA
 *      -\b ADS1248_CMD_RDATAC
 *      -\b ADS1248_CMD_SDATAC
 *      -\b ADS1248_CMD_RREG
 *      -\b ADS1248_CMD_WREG
 *      -\b ADS1248_CMD_SYSOCAL
 *      -\b ADS1248_CMD_SYSGCAL
 *      -\b ADS1248_CMD_SELFOCAL
 *      .
 * \endparblock
 *
 * \return The status/error code.
 */
int ads1248_write_cmd(ads1248_config_t *config, ads1248_cmd_t cmd, uint8_t *rd);

/**
 * \brief Sets the power-down mode.
 *
 * Power consumption is reduced to a minimum by placing the device into power-down mode. There are two ways to put the device into power-down mode: using the SLEEP command or taking the START pin low.
 * When using the SLEEP command, CS (active-low) must be held low for the duration of the power-down mode, this enables only the RDATA, RDATAC, SDATAC, WAKEUP,and NOP commandscan to received.
 *
 * \param[in,out] config is a pointer to the configuration parameters of the device.
 *
 * \param[in] mode is the power-down mode. It can be:
 * \parblock
 *      -\b ADS1248_POWER_DOWN_PIN
 *      -\b ADS1248_POWER_DOWN_CMD
 *      .
 * \endparblock
 *
 * \return The status/error code.
 */
int ads1248_set_powerdown_mode(ads1248_config_t *config, ads1248_power_down_t mode);

#endif /* ADS1248_H_ */

/** \} End of ads1248 group */
