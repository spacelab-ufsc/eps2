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
 * 
 * \version 0.1.1
 * 
 * \date 2020/10/24
 * 
 * \defgroup ads1248 ADS1248
 * \ingroup drivers
 * \{
 */

#ifndef ADS1248_H_
#define ADS1248_H_

#include <drivers/spi/spi.h>
#include <drivers/gpio/gpio.h>

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
 * \brief ADS1248 initialization.
 *
 * \param[in,out] config is a pointer to the ADS1248 configuration parameters.
 *
 * \return The status/error code.
 */
int ads1248_init(ads1248_config_t *config);

/**
 * \brief Resets teh device.
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
 * \brief Sets the power-down mode.
 *
 * Power consumption is reduced to a minimum by placing the device into power-down mode. There are two ways
 * to put the device into power-down mode: using the SLEEP command and taking the START pin low.
 *
 * \param[in,out] config is a pointer to the configuration parameters of the device.
 *
 * \return The status/error code.
 */
int ads1248_set_powerdown_mode(ads1248_config_t *config);

/**
 * \brief Writes a command to the device.
 *
 * \param[in,out] config is a pointer to the configuration parameters of the device.
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
int ads1248_write_cmd(ads1248_config_t *config, ads1248_cmd_t cmd);

#endif /* ADS1248_H_ */

/** \} End of ads1248 group */
