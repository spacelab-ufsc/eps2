/*
 * eps2_data.c
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
 * \brief EPS data structure implementation.
 *
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * \author André M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 *
 * \version 0.2.17
 *
 * \date 2021/03/31
 *
 * \addgroup epd_data
 * \{
 */

#include <system/sys_log/sys_log.h>

#include "eps2_data.h"

eps_data_t eps_data_buff;

int eps_buffer_write(uint8_t id, uint32_t *value)
{
	switch(id)
    {
        case EPS2_PARAM_ID_TIME_COUNTER:
        	eps_data_buff.time_counter_ms = *value;
            break;
        case EPS2_PARAM_ID_MCU_TEMP:
            eps_data_buff.eps_mcu_temp_kelvin = *value;
            break;
        case EPS2_PARAM_ID_EPS_CURRENT:
            eps_data_buff.eps_beacon_ma = *value;
            break;
        case EPS2_PARAM_ID_LAST_RESET_CAUSE:
            eps_data_buff.last_reset_cause = *value;
            break;
        case EPS2_PARAM_ID_RESET_COUNTER:
            eps_data_buff.reset_counter = *value;
            break;
        case EPS2_PARAM_ID_SP_MY_PX_VOLTAGE:
            eps_data_buff.minus_y_plus_x_solar_panel_mv = *value;
            break;
        case EPS2_PARAM_ID_SP_MX_PZ_VOLTAGE:
            eps_data_buff.minus_x_plus_z_solar_panel_mv = *value;
            break;
        case EPS2_PARAM_ID_SP_MZ_PY_VOLTAGE:
            eps_data_buff.minus_z_plus_y_solar_panel_mv = *value;
            break;
        case EPS2_PARAM_ID_SP_MY_CURRENT:
            eps_data_buff.minus_y_solar_panel_ma = *value;
            break;
        case EPS2_PARAM_ID_SP_PY_CURRENT:
            eps_data_buff.plus_y_solar_panel_ma = *value;
            break;
        case EPS2_PARAM_ID_SP_MX_CURRENT:
            eps_data_buff.minus_x_solar_panel_ma = *value;
            break;
        case EPS2_PARAM_ID_SP_PX_CURRENT:
            eps_data_buff.plus_x_solar_panel_ma = *value;
            break;
        case EPS2_PARAM_ID_SP_MZ_CURRENT:
            eps_data_buff.minus_z_solar_panel_ma = *value;
            break;
        case EPS2_PARAM_ID_SP_PZ_CURRENT:
            eps_data_buff.plus_z_solar_panel_ma = *value;
            break;
        case EPS2_PARAM_ID_MPPT_1_DUTY_CYCLE:
            eps_data_buff.mppt_1_duty_cycle = *value;
            break;
        case EPS2_PARAM_ID_MPPT_2_DUTY_CYCLE:
            eps_data_buff.mppt_2_duty_cycle = *value;
            break;
        case EPS2_PARAM_ID_MPPT_3_DUTY_CYCLE:
            eps_data_buff.mppt_3_duty_cycle = *value;
            break;
        case EPS2_PARAM_ID_SP_VOLTAGE_MPPT:
            eps_data_buff.total_solar_panels_mv = *value;
            break;
        case EPS2_PARAM_ID_MAIN_POWER_BUS_VOLTAGE:
            eps_data_buff.main_power_buss_mv = *value;
            break;
        case EPS2_PARAM_ID_RTD_0_TEMP:
            eps_data_buff.batteries_rtd0_kelvin = *value;
            break;
        case EPS2_PARAM_ID_RTD_1_TEMP:
            eps_data_buff.batteries_rtd1_kelvin = *value;
            break;
        case EPS2_PARAM_ID_RTD_2_TEMP:
            eps_data_buff.batteries_rtd2_kelvin = *value;
            break;
        case EPS2_PARAM_ID_RTD_3_TEMP:
            eps_data_buff.batteries_rtd3_kelvin = *value;
            break;
        case EPS2_PARAM_ID_RTD_4_TEMP:
            eps_data_buff.solar_panels_rtd4_kelvin = *value;
            break;
        case EPS2_PARAM_ID_RTD_5_TEMP:
            eps_data_buff.solar_panels_rtd5_kelvin = *value;
            break;
        case EPS2_PARAM_ID_RTD_6_TEMP:
            eps_data_buff.solar_panels_rtd6_kelvin = *value;
            break;
        case EPS2_PARAM_ID_BAT_VOLTAGE:
            eps_data_buff.batteries_mv = *value;
            break;
        case EPS2_PARAM_ID_BAT_CURRENT:
            eps_data_buff.batteries_ma = *value;
            break;
        case EPS2_PARAM_ID_BAT_AVERAGE_CURRENT:
            eps_data_buff.batteries_average_ma = *value;
            break;
        case EPS2_PARAM_ID_BAT_ACC_CURRENT:
            eps_data_buff.batteries_accumulated_ma = *value;
            break;
        case EPS2_PARAM_ID_BAT_CHARGE:
            eps_data_buff.batteries_charge_mah = *value;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_TEMP:
            eps_data_buff.bm_temp_kelvin = *value;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_STATUS:
            eps_data_buff.bm_status_reg = *value;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_PROTECT:
            eps_data_buff.bm_protection_reg = *value;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_CYCLE_COUNTER:
            eps_data_buff.bm_cycle_counter_reg = *value;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_RAAC:
            eps_data_buff.bm_raac_mah = *value;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_RSAC:
            eps_data_buff.bm_rsac_mah = *value;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_RARC:
            eps_data_buff.bm_rarc_percent = *value;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_RSRC:
            eps_data_buff.bm_rsrc_percent = *value;
            break;
        case EPS2_PARAM_ID_BAT_HEATER_1_DUTY_CYCLE:
            eps_data_buff.heater1_duty_cycle = *value;
            break;
        case EPS2_PARAM_ID_BAT_HEATER_2_DUTY_CYCLE:
            eps_data_buff.heater2_duty_cycle = *value;
            break;
        case EPS2_PARAM_ID_HW_VERSION:
            eps_data_buff.firmware_version = *value;
            break;
        case EPS2_PARAM_ID_FW_VERSION:
            eps_data_buff.hardware_version = *value;
            break;
        case EPS2_PARAM_ID_MPPT_1_MODE:
            eps_data_buff.mppt_1_mode = *value;
            break;
        case EPS2_PARAM_ID_MPPT_2_MODE:
            eps_data_buff.mppt_2_mode = *value;
            break;
        case EPS2_PARAM_ID_MPPT_3_MODE:
            eps_data_buff.mppt_3_mode = *value;
            break;
        case EPS2_PARAM_ID_BAT_HEATER_1_MODE:
            eps_data_buff.heater1_mode = *value;
            break;
        case EPS2_PARAM_ID_BAT_HEATER_2_MODE:
            eps_data_buff.heater2_mode = *value;
            break;
        case EPS2_PARAM_ID_DEVICE_ID:
            eps_data_buff.device_id = *value;
            break;
        default:
            sys_log_print_event_from_module(SYS_LOG_ERROR, EPS_DATA_NAME, "Unknown parameter ID!");
            sys_log_new_line();
            return -1;
    }

    return 0;
}

int eps_buffer_read(uint8_t id, uint32_t *value)
{

    #if CONFIG_SET_DUMMY_EPS == 1
    switch(id)
    {
        case EPS2_PARAM_ID_TIME_COUNTER:
            *value = 0;
            break;
        case EPS2_PARAM_ID_MCU_TEMP:
            *value = 1;
            break;
        case EPS2_PARAM_ID_EPS_CURRENT:
            *value = 2;
            break;
        case EPS2_PARAM_ID_LAST_RESET_CAUSE:
            *value = 3;
            break;
        case EPS2_PARAM_ID_RESET_COUNTER:
            *value = 4;
            break;
        case EPS2_PARAM_ID_SP_MY_PX_VOLTAGE:
            *value = 5;
            break;
        case EPS2_PARAM_ID_SP_MX_PZ_VOLTAGE:
            *value = 6;
            break;
        case EPS2_PARAM_ID_SP_MZ_PY_VOLTAGE:
            *value = 7;
            break;
        case EPS2_PARAM_ID_SP_MY_CURRENT:
            *value = 8;
            break;
        case EPS2_PARAM_ID_SP_PY_CURRENT:
            *value = 9;
            break;
        case EPS2_PARAM_ID_SP_MX_CURRENT:
            *value = 10;
            break;
        case EPS2_PARAM_ID_SP_PX_CURRENT:
            *value = 11;
            break;
        case EPS2_PARAM_ID_SP_MZ_CURRENT:
            *value = 12;
            break;
        case EPS2_PARAM_ID_SP_PZ_CURRENT:
            *value = 13;
            break;
        case EPS2_PARAM_ID_MPPT_1_DUTY_CYCLE:
            *value = 14;
            break;
        case EPS2_PARAM_ID_MPPT_2_DUTY_CYCLE:
            *value = 15;
            break;
        case EPS2_PARAM_ID_MPPT_3_DUTY_CYCLE:
            *value = 16;
            break;
        case EPS2_PARAM_ID_SP_VOLTAGE_MPPT:
            *value = 17;
            break;
        case EPS2_PARAM_ID_MAIN_POWER_BUS_VOLTAGE:
            *value = 18;
            break;
        case EPS2_PARAM_ID_RTD_0_TEMP:
            *value = 19;
            break;
        case EPS2_PARAM_ID_RTD_1_TEMP:
            *value = 20;
            break;
        case EPS2_PARAM_ID_RTD_2_TEMP:
            *value = 21;
            break;
        case EPS2_PARAM_ID_RTD_3_TEMP:
            *value = 22;
            break;
        case EPS2_PARAM_ID_RTD_4_TEMP:
            *value = 23;
            break;
        case EPS2_PARAM_ID_RTD_5_TEMP:
            *value = 24;
            break;
        case EPS2_PARAM_ID_RTD_6_TEMP:
            *value = 25;
            break;
        case EPS2_PARAM_ID_BAT_VOLTAGE:
            *value = 26;
            break;
        case EPS2_PARAM_ID_BAT_CURRENT:
            *value = 27;
            break;
        case EPS2_PARAM_ID_BAT_AVERAGE_CURRENT:
            *value = 28;
            break;
        case EPS2_PARAM_ID_BAT_ACC_CURRENT:
            *value = 29;
            break;
        case EPS2_PARAM_ID_BAT_CHARGE:
            *value = 30;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_TEMP:
            *value = 31;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_STATUS:
            *value = 32;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_PROTECT:
            *value = 33;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_CYCLE_COUNTER:
            *value = 34;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_RAAC:
            *value = 35;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_RSAC:
            *value = 36;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_RARC:
            *value = 37;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_RSRC:
            *value = 38;
            break;
        case EPS2_PARAM_ID_BAT_HEATER_1_DUTY_CYCLE:
            *value = 39;
            break;
        case EPS2_PARAM_ID_BAT_HEATER_2_DUTY_CYCLE:
            *value = 40;
            break;
        case EPS2_PARAM_ID_HW_VERSION:
            *value = 41;
            break;
        case EPS2_PARAM_ID_FW_VERSION:
            *value = 42;
            break;
        case EPS2_PARAM_ID_MPPT_1_MODE:
            *value = 43;
            break;
        case EPS2_PARAM_ID_MPPT_2_MODE:
            *value = 44;
            break;
        case EPS2_PARAM_ID_MPPT_3_MODE:
            *value = 45;
            break;
        case EPS2_PARAM_ID_BAT_HEATER_1_MODE:
            *value = 0;
            break;
        case EPS2_PARAM_ID_BAT_HEATER_2_MODE:
            *value = 0;
            break;
        case EPS2_PARAM_ID_DEVICE_ID:
            *value = 0xEEE2U;
            break;
        default:
            sys_log_print_event_from_module(SYS_LOG_ERROR, EPS_DATA_NAME, "Unknown parameter ID!");
            sys_log_new_line();
            return -1;
    }

    return 0;
    #endif

	switch(id)
    {
        case EPS2_PARAM_ID_TIME_COUNTER:
        	*value = eps_data_buff.time_counter_ms;
            break;
        case EPS2_PARAM_ID_MCU_TEMP:
            *value = eps_data_buff.eps_mcu_temp_kelvin;
            break;
        case EPS2_PARAM_ID_EPS_CURRENT:
            *value = eps_data_buff.eps_beacon_ma;
            break;
        case EPS2_PARAM_ID_LAST_RESET_CAUSE:
            *value = eps_data_buff.last_reset_cause;
            break;
        case EPS2_PARAM_ID_RESET_COUNTER:
            *value = eps_data_buff.reset_counter;
            break;
        case EPS2_PARAM_ID_SP_MY_PX_VOLTAGE:
            *value = eps_data_buff.minus_y_plus_x_solar_panel_mv;
            break;
        case EPS2_PARAM_ID_SP_MX_PZ_VOLTAGE:
            *value = eps_data_buff.minus_x_plus_z_solar_panel_mv;
            break;
        case EPS2_PARAM_ID_SP_MZ_PY_VOLTAGE:
            *value = eps_data_buff.minus_z_plus_y_solar_panel_mv;
            break;
        case EPS2_PARAM_ID_SP_MY_CURRENT:
            *value = eps_data_buff.minus_y_solar_panel_ma;
            break;
        case EPS2_PARAM_ID_SP_PY_CURRENT:
            *value = eps_data_buff.plus_y_solar_panel_ma;
            break;
        case EPS2_PARAM_ID_SP_MX_CURRENT:
            *value = eps_data_buff.minus_x_solar_panel_ma;
            break;
        case EPS2_PARAM_ID_SP_PX_CURRENT:
            *value = eps_data_buff.plus_x_solar_panel_ma;
            break;
        case EPS2_PARAM_ID_SP_MZ_CURRENT:
            *value = eps_data_buff.minus_z_solar_panel_ma;
            break;
        case EPS2_PARAM_ID_SP_PZ_CURRENT:
            *value = eps_data_buff.plus_z_solar_panel_ma;
            break;
        case EPS2_PARAM_ID_MPPT_1_DUTY_CYCLE:
            *value = eps_data_buff.mppt_1_duty_cycle;
            break;
        case EPS2_PARAM_ID_MPPT_2_DUTY_CYCLE:
            *value = eps_data_buff.mppt_2_duty_cycle;
            break;
        case EPS2_PARAM_ID_MPPT_3_DUTY_CYCLE:
            *value = eps_data_buff.mppt_3_duty_cycle;
            break;
        case EPS2_PARAM_ID_SP_VOLTAGE_MPPT:
            *value = eps_data_buff.total_solar_panels_mv;
            break;
        case EPS2_PARAM_ID_MAIN_POWER_BUS_VOLTAGE:
            *value = eps_data_buff.main_power_buss_mv;
            break;
        case EPS2_PARAM_ID_RTD_0_TEMP:
            *value = eps_data_buff.batteries_rtd0_kelvin;
            break;
        case EPS2_PARAM_ID_RTD_1_TEMP:
            *value = eps_data_buff.batteries_rtd1_kelvin;
            break;
        case EPS2_PARAM_ID_RTD_2_TEMP:
            *value = eps_data_buff.batteries_rtd2_kelvin;
            break;
        case EPS2_PARAM_ID_RTD_3_TEMP:
            *value = eps_data_buff.batteries_rtd3_kelvin;
            break;
        case EPS2_PARAM_ID_RTD_4_TEMP:
            *value = eps_data_buff.solar_panels_rtd4_kelvin;
            break;
        case EPS2_PARAM_ID_RTD_5_TEMP:
            *value = eps_data_buff.solar_panels_rtd5_kelvin;
            break;
        case EPS2_PARAM_ID_RTD_6_TEMP:
            *value = eps_data_buff.solar_panels_rtd6_kelvin;
            break;
        case EPS2_PARAM_ID_BAT_VOLTAGE:
            *value = eps_data_buff.batteries_mv;
            break;
        case EPS2_PARAM_ID_BAT_CURRENT:
            *value = eps_data_buff.batteries_ma;
            break;
        case EPS2_PARAM_ID_BAT_AVERAGE_CURRENT:
            *value = eps_data_buff.batteries_average_ma;
            break;
        case EPS2_PARAM_ID_BAT_ACC_CURRENT:
            *value = eps_data_buff.batteries_accumulated_ma;
            break;
        case EPS2_PARAM_ID_BAT_CHARGE:
            *value = eps_data_buff.batteries_charge_mah;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_TEMP:
            *value = eps_data_buff.bm_temp_kelvin;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_STATUS:
            *value = eps_data_buff.bm_status_reg;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_PROTECT:
            *value = eps_data_buff.bm_protection_reg;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_CYCLE_COUNTER:
            *value = eps_data_buff.bm_cycle_counter_reg;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_RAAC:
            *value = eps_data_buff.bm_raac_mah;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_RSAC:
            *value = eps_data_buff.bm_rsac_mah;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_RARC:
            *value = eps_data_buff.bm_rarc_percent;
            break;
        case EPS2_PARAM_ID_BAT_MONITOR_RSRC:
            *value = eps_data_buff.bm_rsrc_percent;
            break;
        case EPS2_PARAM_ID_BAT_HEATER_1_DUTY_CYCLE:
            *value = eps_data_buff.heater1_duty_cycle;
            break;
        case EPS2_PARAM_ID_BAT_HEATER_2_DUTY_CYCLE:
            *value = eps_data_buff.heater2_duty_cycle;
            break;
        case EPS2_PARAM_ID_HW_VERSION:
            *value = eps_data_buff.firmware_version;
            break;
        case EPS2_PARAM_ID_FW_VERSION:
            *value = eps_data_buff.hardware_version;
            break;
        case EPS2_PARAM_ID_MPPT_1_MODE:
            *value = eps_data_buff.mppt_1_mode;
            break;
        case EPS2_PARAM_ID_MPPT_2_MODE:
            *value = eps_data_buff.mppt_2_mode;
            break;
        case EPS2_PARAM_ID_MPPT_3_MODE:
            *value = eps_data_buff.mppt_3_mode;
            break;
        case EPS2_PARAM_ID_BAT_HEATER_1_MODE:
            *value = eps_data_buff.heater1_mode;
            break;
        case EPS2_PARAM_ID_BAT_HEATER_2_MODE:
            *value = eps_data_buff.heater2_mode;
            break;
        case EPS2_PARAM_ID_DEVICE_ID:
            *value = eps_data_buff.device_id;
            break;
        default:
            sys_log_print_event_from_module(SYS_LOG_ERROR, EPS_DATA_NAME, "Unknown parameter ID!");
            sys_log_new_line();
			return -1;
    }

    return 0;
}

/** \} End of eps_data group */
