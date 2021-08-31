/*
 * ds2777g.c
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
 * \brief DS2777G+ driver implementation.
 * 
 * \author Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * 
 * \version 0.2.0
 * 
 * \date 2021/08/17
 * 
 * \addtogroup ds2777g
 * \{
 */

#include <stdio.h>
#include <system/sys_log/sys_log.h>
#include "ds2777g.h"

int ds2777g_init(ds2777g_config_t config)
{
    /* Protection register configuration. */
    int res = -1;
    res = ds2777g_enable_charge(config);
    if (res != 0) {return res;}
    res = ds2777g_enable_discharge(config);
    if (res != 0) {return res;}

    /* Control register configuration. */
    // Check if already set correctly from EEPROM on power-up.
    uint8_t control_register_current_value[1];
    res = ds2777g_read_data(config, DS2777G_CONTROL_REGISTER, control_register_current_value, 1);
    if (res != 0) {return res;}
    if (control_register_current_value[0] != 0x0C)
    {
        // Write to control register.
        uint8_t buf[2] = {DS2777G_CONTROL_REGISTER, 0x0C}; // <-- Sets undervoltage treshold to 2.60V.
        res = ds2777g_write_data(config, buf, 2);
        if (res != 0) {return res;}
        // Copy from shadow RAM to EEPROM.
        buf[0] = DS2777G_COPY_DATA_PARAMETER_EEPROM;
        ds2777g_write_data(config, buf, 1);
        if (res != 0) {return res;}
    }

    /* TO DO. */

    return -1;
}

int ds2777g_enable_charge(ds2777g_config_t config)
{
    uint8_t value = 0;
    int res = -1;
    res = ds2777g_read_data(config, DS2777G_PROTECTION_REGISTER, &value, 1);
    if (res != 0) {return res;}

    uint8_t temp[2] = {DS2777G_PROTECTION_REGISTER, (value | DS2777G_CHARGE_ENABLE_BIT)};
    res = ds2777g_write_data(config, temp, 2);
    return res;
}

int ds2777g_enable_discharge(ds2777g_config_t config)
{
    uint8_t value = 0;
    int res = -1;
    res = ds2777g_read_data(config, DS2777G_PROTECTION_REGISTER, &value, 1);
    if (res != 0) {return res;}

    uint8_t temp[2] = {DS2777G_PROTECTION_REGISTER, (value | DS2777G_DISCHARGE_ENABLE_BIT)};
    res = ds2777g_write_data(config, temp, 2);
    return res;
}

int ds2777g_disable_charge(ds2777g_config_t config)
{
    uint8_t value = 0;
    int res = -1;
    res = ds2777g_read_data(config, DS2777G_PROTECTION_REGISTER, &value, 1);
    if (res != 0) {return res;}

    uint8_t temp[2] = {DS2777G_PROTECTION_REGISTER, (value & (0xFF - DS2777G_CHARGE_ENABLE_BIT))};
    res = ds2777g_write_data(config, temp, 2);
    return res;
}

int ds2777g_disable_discharge(ds2777g_config_t config)
{
    uint8_t value = 0;
    int res = -1;
    res = ds2777g_read_data(config, DS2777G_PROTECTION_REGISTER, &value, 1);
    if (res != 0) {return res;}

    uint8_t temp[2] = {DS2777G_PROTECTION_REGISTER, (value & (0xFF - DS2777G_DISCHARGE_ENABLE_BIT))};
    res = ds2777g_write_data(config, temp, 2);
    return res;    
}

int ds2777g_read_voltage_raw(ds2777g_config_t config, int16_t *voltage_raw, uint8_t battery_select)
{
    int res = -1;
    uint8_t buf[2];
    if (battery_select == 1)
    {
        res = ds2777g_read_data(config, DS2777G_VOLTAGE_REGISTER_MSB_Vin1_Vss, buf, 2);
    }
    else if (battery_select == 2)
    {
        res = ds2777g_read_data(config, DS2777G_VOLTAGE_REGISTER_MSB_Vin2_Vin1, buf, 2);
    }
    else{
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS2777G_MODULE_NAME, "Invalid value for battery number. (Must either 1 or 2)");
        return res;
    }
    *voltage_raw = ((int16_t)((buf[1] << 8) + buf[0])) >> 5;
    return res;
}

int16_t ds2777g_voltage_raw_to_mv(int16_t raw)
{
    return raw * 4.8828;
}

int ds2777g_read_voltage_mv(ds2777g_config_t config, int16_t *voltage_mv, uint8_t battery_select)
{
    int res = -1;
    int16_t voltage_raw = 0;

    res = ds2777g_read_voltage_raw(config, &voltage_raw, battery_select);
    if (res != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS2777G_MODULE_NAME, "Error reading the raw voltage value!");
        sys_log_new_line();
        return res;
    }

    *voltage_mv = ds2777g_voltage_raw_to_mv(voltage_raw);
    return res;
}

int ds2777g_read_temperature_raw(ds2777g_config_t config, int16_t *temp_raw)
{
    int res = -1;
    uint8_t buf[2];
    res = ds2777g_read_data(config, DS2777G_TEMPERATURE_REGISTER_MSB, buf, 2);
    *temp_raw = ((int16_t)((buf[1] << 8) + buf[0])) >> 5;
    return res;
}

float ds2777g_temperature_raw_to_celsius(int16_t raw)
{
    return raw * 0.125;
}

int ds2777g_read_temperature_celsius(ds2777g_config_t config, float *temp_celsius)
{
    int res = -1;
    int16_t temp_raw = 0;

    res = ds2777g_read_temperature_raw(config, &temp_raw);
    if (res != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS2777G_MODULE_NAME, "Error reading the raw temperature value!");
        sys_log_new_line();
        return res;
    }

    *temp_celsius = ds2777g_temperature_raw_to_celsius(temp_raw);
    return res;
}

int ds2777g_read_current_raw(ds2777g_config_t config, int16_t *current_raw, bool read_average)
{
    int res = -1;
    uint8_t buf[2];
    if (read_average == true)
    {
        res = ds2777g_read_data(config, DS2777G_AVERAGE_CURRENT_REGISTER_MSB, buf, 2);
    }
    else /* Read instantaneous instead; */
    {
        res = ds2777g_read_data(config, DS2777G_CURRENT_REGISTER_MSB, buf, 2);
    }
    return res;
}

int16_t ds2777g_current_raw_to_ma(int16_t raw)
{
    return raw * (1.5625 * 1000) / (DS2777G_RSENSE);
}

int ds2777g_read_current_ma(ds2777g_config_t config, int16_t *current_ma, bool read_average)
{
    int res = -1;
    int16_t current_raw = 0;

    res = ds2777g_read_current_raw(config, &current_raw, read_average);
    if (res != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS2777G_MODULE_NAME, "Error reading the raw current value!");
        sys_log_new_line();
        return res;
    }

    *current_ma = ds2777g_current_raw_to_ma(current_raw);
    return res;
}

int ds2777g_write_data(ds2777g_config_t config, uint8_t *data, const uint16_t len)
{
    int res = -1;
    res = i2c_write(config.port, config.slave_adr, data, len);
    return res;
}

int ds2777g_read_data(ds2777g_config_t config, uint8_t target_reg, uint8_t *data, uint16_t len)
{
    int res = -1;
    uint8_t reg[1] = {target_reg};
    res = i2c_write(config.port, config.slave_adr, reg, 1);
    if (res != 0) {return res;}

    res = i2c_read(config.port, config.slave_adr, data, len);
    return res;
}

/** \} End of ds2777g group */
