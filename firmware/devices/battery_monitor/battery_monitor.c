/*
 * battery_monitor.c
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
 * along with EPS 2.0. If not, see <http:/\/www.gnu.org/licenses/>.
 *
 */

/**
 * \brief Battery Monitor device implementation.
 *
 * \author Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * \author Ramon de Araujo Borba <ramonborba97@gmail.com>
 *
 * \version 0.4.0
 *
 * \date 2021/09/18
 *
 * \addtogroup battery_monitor
 * \{
 */

#include <stdint.h>

#include "battery_monitor.h"

#include <system/sys_log/sys_log.h>

#include <drivers/ds277Xg/ds277Xg.h>
#include <drivers/i2c/i2c.h>

/**
 * \brief Get the cell one voltage.
 * 
 * \param[in,out] voltage Voltage in mV.
 * \return int The status/error code.
 */
static int bm_get_cell_one_voltage(int16_t *voltage);

/**
 * \brief Get the cell two voltage.
 * 
 * \param[in,out] voltage Voltage in mV.
 * \return int The status/error code.
 */
static int bm_get_cell_two_voltage(int16_t *voltage);

ds277Xg_config_t battery_monitor_config = {.port = I2C_PORT_0, .slave_adr = DS2777G_DEFAULT_SLAVE_ADDRESS};

int battery_monitor_init(void)
{
    int err = 0;
    sys_log_print_event_from_module(SYS_LOG_INFO, BATTERY_MONITOR_MODULE_NAME, "Initializing Battery Monitor device.");
    sys_log_new_line();

    if(ds277Xg_init(&battery_monitor_config) != 0)
    {
       sys_log_print_event_from_module(SYS_LOG_ERROR, BATTERY_MONITOR_MODULE_NAME, "Error initializing Battery Monitor device!");
       sys_log_new_line();

       err += -1;
    }

    return err;
}

int bm_get_cell_one_voltage(int16_t *voltage)
{
    int err = 0;
    if (ds277Xg_read_voltage_mv(&battery_monitor_config, voltage, 1) != 0) {err += -1;}
    return err;
}

int bm_get_cell_two_voltage(int16_t *voltage)
{
    int err = 0;
    if (ds277Xg_read_voltage_mv(&battery_monitor_config, voltage, 2) != 0) {err += -1;}
    return err;
}

int bm_get_voltage(uint16_t *voltage)
{
    int err = 0;
    int16_t buf = 0;
    if (bm_get_cell_one_voltage(&buf) != 0) {err += -1;}
    *voltage = buf;
    if (bm_get_cell_two_voltage(&buf) != 0) {err += -1;}
    *voltage += buf;
    return err;
}

int bm_get_temperature_kelvin(uint16_t *temp)
{
    int err = 0;
    if (ds277Xg_read_temperature_kelvin(&battery_monitor_config, temp) != 0) {err += -1;}
    return err;
}

int bm_get_instantaneous_current(int16_t *current)
{
    int err = 0;
    if (ds277Xg_read_current_ma(&battery_monitor_config, current, false) != 0) {err += -1;}
    return err;
}

int bm_get_average_current(int16_t *current)
{
    int err = 0; 
    if (ds277Xg_read_current_ma(&battery_monitor_config, current, true) != 0) {err += -1;}
    return err;
}

int bm_get_status_register_data(uint8_t *data)
{
    int err = 0;
    if (ds277Xg_read_data(&battery_monitor_config, DS277XG_STATUS_REGISTER, data, 1) != 0) {err += -1;}
    return err;
}

int bm_get_protection_register_data(uint8_t *data)
{
    int err = 0;
    if (ds277Xg_read_data(&battery_monitor_config, DS277XG_PROTECTION_REGISTER, data, 1) != 0) {err += -1;}
    return err;
}

int bm_get_raac_mah(uint16_t *data)
{
    int err = 0;
    uint8_t rd_buf[2] = {0};
    if (ds277Xg_read_data(&battery_monitor_config, DS277XG_RAAC_REGISTER_MSB, rd_buf, 2) != 0) {err += -1;}
    *data = (uint16_t)(((rd_buf[0] << 8) + rd_buf[1]) * 1.6);
    return err;
}

int bm_get_rsac_mah(uint16_t *data)
{
    int err = 0;
    uint8_t rd_buf[2] = {0};
    if (ds277Xg_read_data(&battery_monitor_config, DS277XG_RSAC_REGISTER_MSB, rd_buf, 2) != 0) {err += -1;}
    *data = (uint16_t)(((rd_buf[0] << 8) + rd_buf[1]) * 1.6);
    return err;
}

int bm_get_rarc_percent(uint8_t *data)
{
    int err = 0;
    if (ds277Xg_read_data(&battery_monitor_config, DS277XG_RARC_REGISTER, data, 1) != 0) {err += -1;}
    return err;
}

int bm_get_rsrc_percent(uint8_t *data)
{
    int err = 0;
    if (ds277Xg_read_data(&battery_monitor_config, DS277XG_RSRC_REGISTER, data, 1) != 0) {err += -1;}
    return err;
}

int bm_get_acc_current_mah(uint16_t *data)
{
    int err = 0;
    if (ds277Xg_read_accumulated_current_mah(&battery_monitor_config, data) != 0) { err += -1; }
    return err;
}

int bm_get_full_capacity_ppm(uint32_t *data)
{
    int err = 0;
    uint8_t rd_buf[2] = {0};
    if (ds277Xg_read_data(&battery_monitor_config, DS277XG_FULL_REGISTER_MSB, rd_buf, 2) != 0) { err += -1; }
    *data = ((uint32_t)(((rd_buf[0] << 8) + rd_buf[1]) >> 1) * 61U);
    return err;
}

int bm_get_active_empty_capacity_ppm(uint32_t *data)
{
    int err = 0;
    uint8_t rd_buf[2] = {0};
    if (ds277Xg_read_data(&battery_monitor_config, DS277XG_ACTIVE_EMPTY_REGISTER_MSB, rd_buf, 2) != 0) { err += -1; }
    *data = ((uint32_t)(((rd_buf[0] << 8) + rd_buf[1]) >> 1) * 61U);
    return err;
}

int bm_get_standby_empty_capacity_ppm(uint32_t *data)
{
    int err = 0;
    uint8_t rd_buf[2] = {0};
    if (ds277Xg_read_data(&battery_monitor_config, DS277XG_STANDBY_EMPTY_REGISTER_MSB, rd_buf, 2) != 0) { err += -1; }
    *data = ((uint32_t)(((rd_buf[0] << 8) + rd_buf[1]) >> 1) * 61U);
    return err;
}