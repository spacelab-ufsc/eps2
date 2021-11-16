/*
 * eps2_data.h
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
 * \brief EPS data structure definition.
 *
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 *
 * \version 0.2.5
 *
 * \date 2021/04/09
 *
 * \defgroup epd_data EPS Data
 * \ingroup structs
 * \{
 */

#ifndef EPS_DATA_H_
#define EPS_DATA_H_

#include <stdint.h>
#include <config/config.h>

#define EPS_DATA_NAME       "EPS2 Buffer"

/**
 * \brief Parameters' IDs.
 */
typedef enum
{
    EPS2_PARAM_ID_TIME_COUNTER              = 0,
    EPS2_PARAM_ID_MCU_TEMP                  = 1,
    EPS2_PARAM_ID_EPS_CURRENT               = 2,
    EPS2_PARAM_ID_LAST_RESET_CAUSE          = 3,
    EPS2_PARAM_ID_RESET_COUNTER             = 4,
    EPS2_PARAM_ID_SP_MY_PX_VOLTAGE          = 5,
    EPS2_PARAM_ID_SP_MX_PZ_VOLTAGE          = 6,
    EPS2_PARAM_ID_SP_MZ_PY_VOLTAGE          = 7,
    EPS2_PARAM_ID_SP_MY_CURRENT             = 8,
    EPS2_PARAM_ID_SP_PY_CURRENT             = 9,
    EPS2_PARAM_ID_SP_MX_CURRENT             = 10,
    EPS2_PARAM_ID_SP_PX_CURRENT             = 11,
    EPS2_PARAM_ID_SP_MZ_CURRENT             = 12,
    EPS2_PARAM_ID_SP_PZ_CURRENT             = 13,
    EPS2_PARAM_ID_MPPT_1_DUTY_CYCLE         = 14,
    EPS2_PARAM_ID_MPPT_2_DUTY_CYCLE         = 15,
    EPS2_PARAM_ID_MPPT_3_DUTY_CYCLE         = 16,
    EPS2_PARAM_ID_SP_VOLTAGE_MPPT           = 17,
    EPS2_PARAM_ID_MAIN_POWER_BUS_VOLTAGE    = 18,
    EPS2_PARAM_ID_RTD_0_TEMP                = 19,
    EPS2_PARAM_ID_RTD_1_TEMP                = 20,
    EPS2_PARAM_ID_RTD_2_TEMP                = 21,
    EPS2_PARAM_ID_RTD_3_TEMP                = 22,
    EPS2_PARAM_ID_RTD_4_TEMP                = 23,
    EPS2_PARAM_ID_RTD_5_TEMP                = 24,
    EPS2_PARAM_ID_RTD_6_TEMP                = 25,
    EPS2_PARAM_ID_BAT_VOLTAGE               = 26,
    EPS2_PARAM_ID_BAT_CURRENT               = 27,
    EPS2_PARAM_ID_BAT_AVERAGE_CURRENT       = 28,
    EPS2_PARAM_ID_BAT_ACC_CURRENT           = 29,
    EPS2_PARAM_ID_BAT_CHARGE                = 30,
    EPS2_PARAM_ID_BAT_MONITOR_TEMP          = 31,
    EPS2_PARAM_ID_BAT_MONITOR_STATUS        = 32,
    EPS2_PARAM_ID_BAT_MONITOR_PROTECT       = 33,
    EPS2_PARAM_ID_BAT_MONITOR_CYCLE_COUNTER = 34,
    EPS2_PARAM_ID_BAT_MONITOR_RAAC          = 35,
    EPS2_PARAM_ID_BAT_MONITOR_RSAC          = 36,
    EPS2_PARAM_ID_BAT_MONITOR_RARC          = 37,
    EPS2_PARAM_ID_BAT_MONITOR_RSRC          = 38,
    EPS2_PARAM_ID_BAT_HEATER_1_DUTY_CYCLE   = 39,
    EPS2_PARAM_ID_BAT_HEATER_2_DUTY_CYCLE   = 40,
    EPS2_PARAM_ID_HW_VERSION                = 41,
    EPS2_PARAM_ID_FW_VERSION                = 42,
    EPS2_PARAM_ID_MPPT_1_MODE               = 43,
    EPS2_PARAM_ID_MPPT_2_MODE               = 44,
    EPS2_PARAM_ID_MPPT_3_MODE               = 45,
    EPS2_PARAM_ID_BAT_HEATER_1_MODE         = 46,
    EPS2_PARAM_ID_BAT_HEATER_2_MODE         = 47,
    EPS2_PARAM_ID_DEVICE_ID                 = 48
} eps2_param_id_e;

/**
 * \brief EPS data.
 */
typedef struct
{
    /**
     *  EPS MCU related data.
     */
    uint32_t time_counter_ms;                   /**< Time counter in milliseconds. */
    uint8_t last_reset_cause;                   /**< EPS MCU last reset cause */
    uint16_t reset_counter;                     /**< EPS MCU reset counter */
    uint16_t eps_mcu_temp_kelvin;               /**< EPS MCU temperature in kelvin. */
    uint16_t eps_beacon_ma;                     /**< EPS circuitry and Beacon MCU current in mA. */
    uint16_t main_power_buss_mv;                /**< Main power buss voltage in mV. */
    uint8_t mppt_1_duty_cycle;                  /**< MPPT 1 duty cycle in %. */
    uint8_t mppt_2_duty_cycle;                  /**< MPPT 2 duty cycle in %. */
    uint8_t mppt_3_duty_cycle;                  /**< MPPT 3 duty cycle in %. */
    uint8_t mppt_1_mode;                        /**< MPPT 1 mode flag. */
    uint8_t mppt_2_mode;                        /**< MPPT 2 mode flag. */
    uint8_t mppt_3_mode;                        /**< MPPT 3 mode flag. */
    uint8_t heater1_mode;                       /**< Heater 1 mode flag. */
    uint8_t heater2_mode;                       /**< Heater 2 mode flag. */

    /**
     *  Solar panels related data.
     */
    uint16_t minus_y_plus_x_solar_panel_mv;     /**< -Y and +X sides solar panel voltage in mV. */
    uint16_t minus_x_plus_z_solar_panel_mv;     /**< -X and +Z sides solar panel voltage in mV. */
    uint16_t minus_z_plus_y_solar_panel_mv;     /**< -Z and +Y sides solar panel voltage in mV. */
    uint16_t total_solar_panels_mv;             /**< Total solar panels output voltage after MPPT in mV. */
    uint16_t minus_y_solar_panel_ma;            /**< -Y side soldar panel current in mA. */
    uint16_t plus_y_solar_panel_ma;             /**< +Y side solar panel current in mA. */
    uint16_t minus_x_solar_panel_ma;            /**< -X side solar panel current in mA. */
    uint16_t plus_x_solar_panel_ma;             /**< +X side solar panel current in mA. */
    uint16_t minus_z_solar_panel_ma;            /**< -Z side solar panel current in mA. */
    uint16_t plus_z_solar_panel_ma;             /**< +Z side solar panel current in mA. */
    uint32_t solar_panels_rtd4_kelvin;          /**< Solar panels RTD 4 temperature in kelvin. */
    uint32_t solar_panels_rtd5_kelvin;          /**< Solar panels RTD 5 temperature in kelvin. */
    uint32_t solar_panels_rtd6_kelvin;          /**< Solar panels RTD 6 temperature in kelvin. */

    /**
     *  Batteries related data.
     */
    uint16_t batteries_mv;                      /**< Batteries voltage in mV. */
    uint16_t batteries_ma;                      /**< Batteries current in mA. */
    uint16_t batteries_average_ma;              /**< Batteries average current in 8 mA measurements. */
    uint16_t batteries_accumulated_ma;          /**< Batteries accumulated current in mA. */
    uint16_t batteries_charge_mah;              /**< Batteries charge in mAh. */
    uint32_t batteries_rtd0_kelvin;             /**< Batteries RTD 0 temperature in kelvin. */
    uint32_t batteries_rtd1_kelvin;             /**< Batteries RTD 1 temperature in kelvin. */
    uint32_t batteries_rtd2_kelvin;             /**< Batteries RTD 2 temperature in kelvin. */
    uint32_t batteries_rtd3_kelvin;             /**< Batteries RTD 3 temperature in kelvin. */
    uint8_t heater1_duty_cycle;                  /**< Batteries heater 1 duty cyle in %. */
    uint8_t heater2_duty_cycle;                  /**< Batteries heater 2 duty cyle in %. */

    /**
     *  Battery monitor related data.
     */
    uint16_t bm_temp_kelvin;                    /**< Battery monitor IC temperature in kelvin. */
    uint8_t bm_status_reg;                      /**< Batteries monitor status register. */
    uint8_t bm_protection_reg;                  /**< Batteries monitor protection register. */
    uint8_t bm_cycle_counter_reg;               /**< Batteries monitor cycle counter register. */
    uint16_t bm_raac_mah;                       /**< Battery monitor Remaining Active-Absolute Capacity (RAAC) in mAh. */
    uint16_t bm_rsac_mah;                       /**< Battery monitor Remaining Standby-Absolute Capacity (RSAC) in mAh. */
    uint8_t bm_rarc_percent;                    /**< Battery monitor Remaining Active-Relative Capacity (RARC) in %. */
    uint8_t bm_rsrc_percent;                    /**< Battery monitor Remaining Standby-Relative Capacity (RSRC) in %. */

    /**
     *  EPS misc related data.
     */
    uint32_t firmware_version;                  /**< Hard-coded firmware version of EPS. */
    uint8_t hardware_version;                   /**< Hard-coded hardware version of EPS. */
    uint16_t device_id;                          /**< Hard-coded device id of EPS. */

} eps_data_t;

/**
 * \brief Function to write a value into the EPS data buffer.
 *
 * \param[in] id is a value to select a variable within the data buffer.
 *
 * \param[out] value is the data that will overwrite the previous data.
 *
 * \return The status/error code.
 */
int eps_buffer_write(uint8_t id, uint32_t *value);

/**
 * \brief Function to read a value of the EPS data buffer.
 *
 * \param[in] id is a value to select a variable within the data buffer.
 *
 * \param[out] value is the data that will be read from the buffer.
 *
 * \return The status/error code.
 */
int eps_buffer_read(uint8_t id, uint32_t *value);

#endif /* EPS_DATA_H_ */

/** \} End of eps_data group */
