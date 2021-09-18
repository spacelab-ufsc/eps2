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
#include <config/config.h>
#include <system/sys_log/sys_log.h>
#include "ds2777g.h"

int ds2777g_init(ds2777g_config_t config)
{
    /* Protection register configuration. */
    if (ds2777g_enable_charge(config) != 0) {return -1;}
    if (ds2777g_enable_discharge(config) != 0) {return -1;}

    /* Control register configuration. */
    // Check if already set correctly from EEPROM on power-up.
    uint8_t control_register_current_value[1];
    if (ds2777g_read_data(config, DS2777G_CONTROL_REGISTER, control_register_current_value, 1) != 0) {return -1;}
    if (control_register_current_value[0] != 0x0C)
    {
        // Write to control register.
        uint8_t buf[2] = {DS2777G_CONTROL_REGISTER, 0x0C}; // <-- Sets undervoltage treshold to 2.60V.
        if (ds2777g_write_data(config, buf, 2) != 0) {return -1;}
        // Copy from shadow RAM to EEPROM.
        buf[0] = DS2777G_COPY_DATA_PARAMETER_EEPROM;
        if (ds2777g_write_data(config, buf, 1) != 0) {return -1;}
    }

    return 0;
}

int ds2777g_enable_charge(ds2777g_config_t config)
{
    uint8_t value = 0;
    if (ds2777g_read_data(config, DS2777G_PROTECTION_REGISTER, &value, 1) != 0) {return -1;}

    uint8_t temp[2] = {DS2777G_PROTECTION_REGISTER, (value | DS2777G_CHARGE_ENABLE_BIT)};
    if (ds2777g_write_data(config, temp, 2) != 0) {return -1;}

    return 0;
}

int ds2777g_enable_discharge(ds2777g_config_t config)
{
    uint8_t value = 0;
    if (ds2777g_read_data(config, DS2777G_PROTECTION_REGISTER, &value, 1) != 0) {return -1;}

    uint8_t temp[2] = {DS2777G_PROTECTION_REGISTER, (value | DS2777G_DISCHARGE_ENABLE_BIT)};
    if (ds2777g_write_data(config, temp, 2) != 0) {return -1;}
    return 0;
}

int ds2777g_disable_charge(ds2777g_config_t config)
{
    uint8_t value = 0;
    if (ds2777g_read_data(config, DS2777G_PROTECTION_REGISTER, &value, 1) != 0) {return -1;}

    uint8_t temp[2] = {DS2777G_PROTECTION_REGISTER, (value & (0xFF - DS2777G_CHARGE_ENABLE_BIT))};
    if (ds2777g_write_data(config, temp, 2) != 0) {return -1;}

    return 0;
}

int ds2777g_disable_discharge(ds2777g_config_t config)
{
    uint8_t value = 0;
    if (ds2777g_read_data(config, DS2777G_PROTECTION_REGISTER, &value, 1) != 0) {return -1;}

    uint8_t temp[2] = {DS2777G_PROTECTION_REGISTER, (value & (0xFF - DS2777G_DISCHARGE_ENABLE_BIT))};
    if (ds2777g_write_data(config, temp, 2) != 0) {return -1;}

    return 0;
}

int ds2777g_read_voltage_raw(ds2777g_config_t config, int16_t *voltage_raw, uint8_t battery_select)
{
    uint8_t buf[2];
    if (battery_select == 1)
    {
        if (ds2777g_read_data(config, DS2777G_VOLTAGE_REGISTER_MSB_Vin1_Vss, buf, 2) != 0) {return -1;}
    }
    else if (battery_select == 2)
    {
        if (ds2777g_read_data(config, DS2777G_VOLTAGE_REGISTER_MSB_Vin2_Vin1, buf, 2) != 0) {return -1;}
    }
    else{
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS2777G_MODULE_NAME, "Invalid value for battery number. (Must either 1 or 2)");
        return -1;
    }
    *voltage_raw = ((int16_t)((buf[1] << 8) + buf[0])) >> 5;
    return 0;
}

int16_t ds2777g_voltage_raw_to_mv(int16_t raw)
{
    return raw * 4.8828;
}

int ds2777g_read_voltage_mv(ds2777g_config_t config, int16_t *voltage_mv, uint8_t battery_select)
{
    int16_t voltage_raw = 0;

    if (ds2777g_read_voltage_raw(config, &voltage_raw, battery_select) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS2777G_MODULE_NAME, "Error reading the raw voltage value!");
        sys_log_new_line();
        return -1;
    }

    *voltage_mv = ds2777g_voltage_raw_to_mv(voltage_raw);
    return 0;
}

int ds2777g_read_temperature_raw(ds2777g_config_t config, int16_t *temp_raw)
{
    uint8_t buf[2];
    if (ds2777g_read_data(config, DS2777G_TEMPERATURE_REGISTER_MSB, buf, 2) != 0) {return -1;}
    *temp_raw = ((int16_t)((buf[1] << 8) + buf[0])) >> 5;
    return 0;
}

float ds2777g_temperature_raw_to_celsius(int16_t raw)
{
    return raw * 0.125;
}

int ds2777g_read_temperature_celsius(ds2777g_config_t config, float *temp_celsius)
{
    int16_t temp_raw = 0;

    if (ds2777g_read_temperature_raw(config, &temp_raw) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS2777G_MODULE_NAME, "Error reading the raw temperature value!");
        sys_log_new_line();
        return -1;
    }

    *temp_celsius = ds2777g_temperature_raw_to_celsius(temp_raw);
    return 0;
}

int ds2777g_read_current_raw(ds2777g_config_t config, int16_t *current_raw, bool read_average)
{
    uint8_t buf[2];
    if (read_average == true)
    {
        if (ds2777g_read_data(config, DS2777G_AVERAGE_CURRENT_REGISTER_MSB, buf, 2) != 0) {return -1;}
    }
    else /* Read instantaneous instead; */
    {
        if (ds2777g_read_data(config, DS2777G_CURRENT_REGISTER_MSB, buf, 2) != 0) {return -1;}
    }
    *current_raw = (uint16_t)((buf[1] << 8) + buf[0]);
    return 0;
}

int16_t ds2777g_current_raw_to_ma(int16_t raw)
{
    return raw * (1.5625 / 1000) / (DS2777G_RSENSE);
}

int ds2777g_read_current_ma(ds2777g_config_t config, int16_t *current_ma, bool read_average)
{
    int16_t current_raw = 0;

    if (ds2777g_read_current_raw(config, &current_raw, read_average) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS2777G_MODULE_NAME, "Error reading the raw current value!");
        sys_log_new_line();
        return -1;
    }

    *current_ma = ds2777g_current_raw_to_ma(current_raw);
    return 0;
}

int ds2777g_write_accumulated_current_raw(ds2777g_config_t config, uint16_t acc_current_raw)
{
    uint8_t buf[3] = {DS2777G_ACCUMULATED_CURRENT_MSB, ((uint8_t)(acc_current_raw >> 8)), ((uint8_t)acc_current_raw)};
    if (ds2777g_write_data(config, buf, 3) != 0) {return -1;}
    return 0;
}

uint16_t ds2777g_accumulated_current_mah_to_raw(uint16_t mah)
{
    return mah * (DS2777G_RSENSE) / (6.25 / 1000);
}

int ds2777g_write_accumulated_current_mah(ds2777g_config_t config, uint16_t acc_current_mah)
{
    return ds2777g_write_accumulated_current_raw(config, ds2777g_accumulated_current_mah_to_raw(acc_current_mah));
}

int ds2777g_write_accumulated_current_max_value(ds2777g_config_t config)
{
    return ds2777g_write_accumulated_current_mah(config, MAX_BATTERY_CHARGE);
}

int ds2777g_read_accumulated_current_raw(ds2777g_config_t config, uint16_t *acc_current_raw)
{
    uint8_t buf[2];
    if (ds2777g_read_data(config, DS2777G_ACCUMULATED_CURRENT_MSB, buf, 2) != 0) {return -1;}
    *acc_current_raw = (uint16_t)((buf[1] << 8) + buf[0]);
    return 0;
}

uint16_t ds2777g_accumulated_current_raw_to_mah(uint16_t raw)
{
    return raw * (6.25 / 1000) / (DS2777G_RSENSE);
}

int ds2777g_read_accumulated_current_mah(ds2777g_config_t config, uint16_t *acc_current_mah)
{
    uint16_t acc_current_raw = 0;

    if (ds2777g_read_accumulated_current_raw(config, &acc_current_raw) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS2777G_MODULE_NAME, "Error reading the raw accumulated current value!");
        sys_log_new_line();
        return -1;
    }

    *acc_current_mah = ds2777g_current_raw_to_ma(acc_current_raw);
    return 0;
}

int ds2777g_write_cycle_counter(ds2777g_config_t config, uint16_t cycles)
{
    if(cycles > 510) { cycles = 510; }
    uint8_t buf[2] = {DS2777G_CYCLE_COUNTER_REGISTER, (uint8_t)(cycles >> 1)}; // shift right to divide by two.
    if (ds2777g_write_data(config, buf, 2) != 0) {return -1;}
    return 0;
}

int ds2777g_read_cycle_counter(ds2777g_config_t config, uint16_t *cycles)
{
    uint8_t buf[1];
    if (ds2777g_read_data(config, DS2777G_CYCLE_COUNTER_REGISTER, buf, 1) != 0) {return -1;}
    *cycles = ((uint16_t)buf) << 1; // shift left to multiply by two.
    return 0;
}

int ds2777g_write_data(ds2777g_config_t config, uint8_t *data, const uint16_t len)
{
    return i2c_write(config.port, config.slave_adr, data, len);
}

int ds2777g_read_data(ds2777g_config_t config, uint8_t target_reg, uint8_t *data, uint16_t len)
{
    uint8_t reg[1] = {target_reg};
    if (i2c_write(config.port, config.slave_adr, reg, 1) != 0) {return -1;}

    return i2c_read(config.port, config.slave_adr, data, len);
}

/** \} End of ds2777g group */
