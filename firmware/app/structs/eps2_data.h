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
 * 
 * \version 0.1.0
 * 
 * \date 2021/03/05
 * 
 * \defgroup epd_data EPS Data
 * \ingroup structs
 * \{
 */

#ifndef EPS_DATA_H_
#define EPS_DATA_H_

#include <stdint.h>

/**
 * \brief EPS data.
 */
typedef struct
{
    /**< EPS MCU related data. */
    
    uint32_t time_counter_ms;                   /**< Time counter in milliseconds. */
    uint8_t last_reset_cause;                   /**< EPS MCU last reset cause */
    uint16_t reset_counter;                     /**< EPS MCU reset counter */
    uint16_t eps_mcu_temp_kelvin;               /**< EPS MCU temperature in kelvin. */
    uint16_t eps_beacon_ma;                     /**< EPS circuitry and Beacon MCU current in mA. */
    uint16_t main_power_buss_mv;                /**< Main power buss voltage in mV. */
    uint8_t mppt_1_duty_cycle;                  /**< MPPT 1 duty cycle in %. */
    uint8_t mppt_2_duty_cycle;                  /**< MPPT 2 duty cycle in %. */
    uint8_t mppt_3_duty_cycle;                  /**< MPPT 3 duty cycle in %. */   
    
    /**< Solar panels related data. */
    
    uint16_t minus_y_plus_x_solar_panel_mv;     /**< -Y and +X sides solar panel voltage in mV. */
    uint16_t minus_x_plus_z_solar_panel_mv;     /**< -X and +Z sides solar panel voltage in mV. */
    uint16_t minus_z_plus_y_solar_panel_mv;     /**< -Z and +Y sides solar panel voltage in mV. */
    uint16_t minus_y_solar_panel_ma;            /**< -Y side soldar panel current in mA. */
    uint16_t plus_y_solar_panel_ma;             /**< +Y side solar panel current in mA. */
    uint16_t minus_x_solar_panel_ma;            /**< -X side solar panel current in mA. */
    uint16_t plus_x_solar_panel_ma;             /**< +X side solar panel current in mA. */
    uint16_t minus_z_solar_panel_ma;            /**< -Z side solar panel current in mA. */
    uint16_t plus_z_solar_panel_ma;             /**< +Z side solar panel current in mA. */
    uint32_t solar_panels_rtd4_kelvin;          /**< Solar panels RTD 4 temperature in kelvin. */
    uint32_t solar_panels_rtd5_kelvin;          /**< Solar panels RTD 5 temperature in kelvin. */
    uint32_t solar_panels_rtd6_kelvin;          /**< Solar panels RTD 6 temperature in kelvin. */
    
    /**< Batteries related data. */
    
    uint16_t batteries_mv;                      /**< Batteries voltage in mV. */
    uint16_t batteries_ma;                      /**< Batteries current in mA. */
    uint16_t batteries_average_ma;              /**< Batteries average current in 8 mA measurements. */
    uint16_t batteries_accumulated_ma;          /**< Batteries accumulated current in mA. */
    uint16_t batteries_charge_mah;              /**< Batteries charge in mAh. */
    uint32_t batteries_rtd0_kelvin;             /**< Batteries RTD 0 temperature in kelvin. */
    uint32_t batteries_rtd1_kelvin;             /**< Batteries RTD 1 temperature in kelvin. */
    uint32_t batteries_rtd2_kelvin;             /**< Batteries RTD 2 temperature in kelvin. */
    uint32_t batteries_rtd3_kelvin;             /**< Batteries RTD 3 temperature in kelvin. */
    uint8_t heater1_duty_cycle                  /**< Batteries heater 1 duty cyle in %. */
    uint8_t heater2_duty_cycle                  /**< Batteries heater 2 duty cyle in %. */

    /**< Battery monitor related data. */
    
    uint16_t bm_temp_kelvin;                    /**< Battery monitor IC temperature in kelvin. */
    uint8_t bm_status_reg;                      /**< Batteries monitor status register. */
    uint8_t bm_protection_reg;                  /**< Batteries monitor protection register. */
    uint8_t bm_cycle_counter_reg;               /**< Batteries monitor cycle counter register. */
    uint16_t bm_raac_mah;                       /**< Battery monitor Remaining Active-Absolute Capacity (RAAC) in mAh. */
    uint16_t bm_rsac_mah;                       /**< Battery monitor Remaining Standby-Absolute Capacity (RSAC) in mAh. */
    uint8_t bm_rarc_percent;                    /**< Battery monitor Remaining Active-Relative Capacity (RARC) in %. */
    uint8_t bm_rsrc_percent;                    /**< Battery monitor Remaining Standby-Relative Capacity (RSRC) in %. */

    /**< EPS misc related data. */

    uint32_t firmware_version;                        /**< Hard-coded hardware version of EPS. */
    uint8_t hardware_version;                         /**< Hard-coded hardware version of EPS. */
    
} eps_data_t;

extern eps_data_t eps_data_buff; 

#endif /* EPS_DATA_H_ */

/** \} End of eps_data group */
