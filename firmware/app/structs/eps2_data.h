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
 * \brief EPS variables.
 */
typedef struct
{
    uint16_t minus_y_plus_x_solar_panel_voltage;    /**< -Y and +X sides solar panel voltage. */
    uint16_t minus_x_plus_z_solar_panel_voltage;    /**< -X and +Z sides solar panel voltage. */
    uint16_t minus_z_plus_y_solar_panel_voltage;    /**< -Z and +Y sides solar panel voltage. */
    uint16_t minus_y_solar_panel_current;           /**< -Y side soldar panel current. */
    uint16_t plux_y_solar_panel_current;            /**< +Y side solar panel current. */
    uint16_t minus_x_solar_panel_current;           /**< -X side solar panel current. */
    uint16_t plus_x_solar_panel_current;            /**< +X side solar panel current. */
    uint16_t minus_z_solar_panel_current;           /**< -Z side solar panel current. */
    uint16_t plus_z_solar_panel_current;            /**< +Z side solar panel current. */
    uint16_t eps_beacon_current;                    /**< EPS2 circuitry and Beacon MCU current. */
    uint16_t main_power_buss_voltage;               /**< Main power buss voltage. */
    uint32_t batteries_rtd1_temperature;            /**< Batteries RTD 1 temperature. */
    uint32_t batteries_rtd2_temperature;            /**< Batteries RTD 2 temperature. */
    uint32_t batteries_rtd3_temperature;            /**< Batteries RTD 3 temperature. */
    uint32_t batteries_rtd4_temperature;            /**< Batteries RTD 4 temperature. */
    uint16_t eps_mcu_temperature;                   /**< Internal EPS2 MCU temperature. */
    uint16_t batteries_voltage;                     /**< Batteries voltage. */
    uint16_t batteries_current;                     /**< Batteries current. */
    uint16_t batteries_average_current;             /**< Batteries average current in 8 measurements. */
    uint16_t batteries_accumulated_current;         /**< Batteries accumulated current. */
    uint16_t batteries_charge;                      /**< Batteries charge. */
    uint16_t bm_temperature;                        /**< Battery monitor IC temperature. */
    uint8_t bm_status_register;                     /**< Batteries monitor status register. */
    uint8_t bm_protection_register;                 /**< Batteries monitor protection register. */
    uint8_t bm_cycle_counter_register;              /**< Batteries monitor cycle counter. */
    uint16_t bm_remaining_active_absolute_capacity  /**< Batteries monitor remaining active absolute capacity register. */
    uint16_t bm_remaining_standby_absolute_capacity /**< Batteries monitor remaining standby absolute capacity register. */
    uint8_t bm_remaining_active_relative_capacity   /**< Batteries monitor remaining active relative capacity registe. */
    uint8_t bm_remaining_standby_relative_capacity  /**< Batteries monitor remaining standby relative capacity register. */
} eps_variables_value_t;

#endif /* EPS_DATA_H_ */

/** \} End of eps_data group */