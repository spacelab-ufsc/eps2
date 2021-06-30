/*
 * sl_eps2.h
 * 
 * Copyright (C) 2021, SpaceLab.
 * 
 * This file is part of OBDH 2.0.
 * 
 * OBDH 2.0 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * OBDH 2.0 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with OBDH 2.0. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief SpaceLab OBDH 2.0 driver definition.
 * 
 * \author Andre M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * 
 * \version 0.2.1
 * 
 * \date 2021/06/30
 * 
 * \defgroup sl_obdh2 SpaceLab OBDH 2.0
 * \ingroup drivers
 * \{
 */

#ifndef SL_OBDH2_H_
#define SL_OBDH2_H_

#include <stdint.h>

#include <drivers/tca4311a/tca4311a.h>

#define SL_EPS2_SLAVE_ADR                       0x36    /**< 7-bit slave address. */

#define SL_EPS2_DEVICE_ID                       0xEEE2  /**< EPS 2.0 device ID. */

/* EPS 2.0 registers */
#define SL_EPS2_REG_TIME_COUNTER_MS             0       /**< Time counter in millseconds. */
#define SL_EPS2_REG_UC_TEMPERATURE_K            1       /**< Temperature of the uC in K. */
#define SL_EPS2_REG_CURRENT_MA                  2       /**< EPS circuitry and Beacon MCU current in mA. */
#define SL_EPS2_REG_LAST_RESET_CAUSE            3       /**< Last reset cause. */
#define SL_EPS2_REG_RESET_COUNTER               4       /**< Reset counter. */
#define SL_EPS2_REG_SOLAR_PANEL_MY_PX_VOLT_MV   5       /**< Solar panel -Y +X voltage in mV. */
#define SL_EPS2_REG_SOLAR_PANEL_MX_PZ_VOLT_MV   6       /**< Solar panel -X +Z voltage in mV. */
#define SL_EPS2_REG_SOLAR_PANEL_MZ_PY_VOLT_MV   7       /**< Solar panel -Z +Y voltage in mV. */
#define SL_EPS2_REG_SOLAR_PANEL_MY_CUR_MA       8       /**< Solar panel +X current in mA. */
#define SL_EPS2_REG_SOLAR_PANEL_PY_CUR_MA       9       /**< Solar panel -X current in mA. */
#define SL_EPS2_REG_SOLAR_PANEL_MX_CUR_MA       10      /**< Solar panel +Y current in mA. */
#define SL_EPS2_REG_SOLAR_PANEL_PX_CUR_MA       11      /**< Solar panel -Y current in mA. */
#define SL_EPS2_REG_SOLAR_PANEL_MZ_CUR_MA       12      /**< Solar panel +Z current in mA. */
#define SL_EPS2_REG_SOLAR_PANEL_PZ_CUR_MA       13      /**< Solar panel -Z current in mA. */
#define SL_EPS2_REG_MPPT_1_DUTY_CYCLE           14      /**< MPPT 1 duty cycle in %. */
#define SL_EPS2_REG_MPPT_2_DUTY_CYCLE           15      /**< MPPT 2 duty cycle in %. */
#define SL_EPS2_REG_MPPT_3_DUTY_CYCLE           16      /**< MPPT 3 duty cycle in %. */
#define SL_EPS2_REG_SOLAR_PANEL_TOTAL_VOLT_MV   17      /**< Total solar panels output voltage after MPPT in mV. */
#define SL_EPS2_REG_MAIN_POWER_BUS_VOLT_MV      18      /**< Main power bus voltage in mV. */
#define SL_EPS2_REG_RTD0_TEMP_K                 19      /**< RTD0 temperature in K. */
#define SL_EPS2_REG_RTD1_TEMP_K                 20      /**< RTD1 temperature in K. */
#define SL_EPS2_REG_RTD2_TEMP_K                 21      /**< RTD2 temperature in K. */
#define SL_EPS2_REG_RTD3_TEMP_K                 22      /**< RTD3 temperature in K. */
#define SL_EPS2_REG_RTD4_TEMP_K                 23      /**< RTD4 temperature in K. */
#define SL_EPS2_REG_RTD5_TEMP_K                 24      /**< RTD5 temperature in K. */
#define SL_EPS2_REG_RTD6_TEMP_K                 25      /**< RTD6 temperature in K. */
#define SL_EPS2_REG_BATTERY_VOLT_MV             26      /**< Battery voltage in mV. */
#define SL_EPS2_REG_BATTERY_CUR_MA              27      /**< Battery current in mA. */
#define SL_EPS2_REG_BATTERY_AVEG_CUR_MA         28      /**< Battery average current in mA. */
#define SL_EPS2_REG_BATTERY_ACC_CUR_MA          29      /**< Battery accumulated current in mA. */
#define SL_EPS2_REG_BATTERY_CHARGE_MAH          30      /**< Battery charge in mAh. */
#define SL_EPS2_REG_BAT_MONITOR_TEMP_K          31      /**< Battery monitor IC temperature in K. */
#define SL_EPS2_REG_BAT_MONITOR_STATUS          32      /**< Battery monitor status register. */
#define SL_EPS2_REG_BAT_MONITOR_PROTECTION      33      /**< Battery monitor protection register. */
#define SL_EPS2_REG_BAT_MONITOR_CYCLE_COUNTER   34      /**< Battery monitor cycle counter. */
#define SL_EPS2_REG_BAT_MONITOR_RAAC_MAH        35      /**< Battery monitor Remaining Active-Absolute Capacity (RAAC) in mAh. */
#define SL_EPS2_REG_BAT_MONITOR_RSAC_MAH        36      /**< Battery monitor Remaining Standby-Absolute Capacity (RSAC) in mAh. */
#define SL_EPS2_REG_BAT_MONITOR_RARC_PERC       37      /**< Battery monitor Remaining Active-Relative Capacity (RARC) in %. */
#define SL_EPS2_REG_BAT_MONITOR_RSRC_PERC       38      /**< Battery monitor Remaining Standby-Relative Capacity (RSRC) in %. */
#define SL_EPS2_REG_BAT_HEATER_1_DUTY_CYCLE     39      /**< Battery heater 1 duty cycle in %. */
#define SL_EPS2_REG_BAT_HEATER_2_DUTY_CYCLE     40      /**< Battery heater 2 duty cycle in %. */
#define SL_EPS2_REG_HARDWARE_VERSION            41      /**< Hardware version. */
#define SL_EPS2_REG_FIRMWARE_VERSION            42      /**< Firmware version (ex.: “v1.2.3”’ = 0x00010203). */
#define SL_EPS2_REG_MPPT_1_MODE                 43      /**< MPPT 1 mode (0x00 = automatic, 0x01 = manual). */
#define SL_EPS2_REG_MPPT_2_MODE                 44      /**< MPPT 2 mode (0x00 = automatic, 0x01 = manual). */
#define SL_EPS2_REG_MPPT_3_MODE                 45      /**< MPPT 3 mode (0x00 = automatic, 0x01 = manual). */
#define SL_EPS2_REG_BAT_HEATER_1_MODE           46      /**< Battery heater 1 mode (0x00 = automatic, 0x01 = manual). */
#define SL_EPS2_REG_BAT_HEATER_2_MODE           47      /**< Battery heater 2 mode (0x00 = automatic, 0x01 = manual). */
#define SL_EPS2_REG_DEVICE_ID                   48      /**< Device ID (0xEEE2). */

/**
 * \brief Configuration parameters structure of the driver.
 */
typedef tca4311a_config_t sl_obdh2_config_t;

/**
 * \brief Initialization of the EPS module driver.
 *
 * \param[in] config is a structure with the configuration parameters of the driver.
 *
 * \return The status/error code.
 */
int sl_obdh2_init(sl_obdh2_config_t config);

/**
 * \brief Computes the CRC-8 of a sequence of bytes.
 *
 * \param[in] data is an array of data to compute the CRC-8.
 *
 * \param[in] len is the number of bytes of the given array.
 *
 * \return The computed CRC-8 value of the given data.
 */
uint8_t sl_obdh2_crc8(uint8_t *data, uint8_t len);

/**
 * \brief Checks the CRC value of a given sequence of bytes.
 *
 * \param[in] data is the data to check the CRC.
 *
 * \param[in] len is the number of bytes to check the CRC value.
 *
 * \param[in] crc is the CRC-8 value to check.
 *
 * \return TRUE/FALSE if the given CRC value is correct or not.
 */
bool sl_obdh2_check_crc(uint8_t *data, uint8_t len, uint8_t crc);

/**
 * \brief Writes a value to a register of the EPS module.
 *
 * \param[in] config is a structure with the configuration parameters of the driver.
 *
 * \param[in] adr is the register address to write.
 *
 * \param[in,out] val is the value to answer to the OBDH.
 *
 * \return The status/error code.
 */
int sl_obdh2_answer(sl_obdh2_config_t config, uint8_t adr, uint32_t val);

#endif /* SL_OBDH2_H_ */

/** \} End of sl_obdh2 group */
