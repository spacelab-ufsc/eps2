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
#include "ds2777g.h"

int ds2777g_init(ds2777g_config_t config)
{
    /* Protection register configuration. */
    int res = 0;
    res = ds2777g_enable_charge(config);
    if (res != 0) {return res;}
    res = ds2777g_enable_discharge(config);
    if (res != 0) {return res;}

    /* Control register configuration. */
    // Check if already set correctly from EEPROM on power-up.
    uint8_t control_register_current_value[1];
    res = ds2777g_read_data(config, CONTROL_REGISTER, control_register_current_value, 1);
    if (res != 0) {return res;}
    if (control_register_current_value[0] != 0x0C)
    {
        // Write to control register.
        uint8_t buf[2] = {CONTROL_REGISTER, 0x0C}; // <-- Sets undervoltage treshold to 2.60V.
        res = ds2777g_write_data(config, buf, 2);
        if (res != 0) {return res;}
        // Copy from shadow RAM to EEPROM.
        buf[0] = COPY_DATA_PARAMETER_EEPROM;
        ds2777g_write_data(config, buf, 1);
        if (res != 0) {return res;}
    }

    /* TO DO. */

    return -1;
}

int ds2777g_enable_charge(ds2777g_config_t config)
{
    uint8_t value = 0;
    int res = 0;
    res = ds2777g_read_data(config, PROTECTION_REGISTER, &value, 1);
    if (res != 0) {return res;}

    uint8_t temp[2] = {PROTECTION_REGISTER, (value | CHARGE_ENABLE_BIT)};
    res = ds2777g_write_data(config, temp, 2);
    return res;
}

int ds2777g_enable_discharge(ds2777g_config_t config)
{
    uint8_t value = 0;
    int res = 0;
    res = ds2777g_read_data(config, PROTECTION_REGISTER, &value, 1);
    if (res != 0) {return res;}

    uint8_t temp[2] = {PROTECTION_REGISTER, (value | DISCHARGE_ENABLE_BIT)};
    res = ds2777g_write_data(config, temp, 2);
    return res;
}

int ds2777g_disable_charge(ds2777g_config_t config)
{
    uint8_t value = 0;
    int res = 0;
    res = ds2777g_read_data(config, PROTECTION_REGISTER, &value, 1);
    if (res != 0) {return res;}

    uint8_t temp[2] = {PROTECTION_REGISTER, (value & (0xFF - CHARGE_ENABLE_BIT))};
    res = ds2777g_write_data(config, temp, 2);
    return res;
}

int ds2777g_disable_discharge(ds2777g_config_t config)
{
    uint8_t value = 0;
    int res = 0;
    res = ds2777g_read_data(config, PROTECTION_REGISTER, &value, 1);
    if (res != 0) {return res;}

    uint8_t temp[2] = {PROTECTION_REGISTER, (value & (0xFF - DISCHARGE_ENABLE_BIT))};
    res = ds2777g_write_data(config, temp, 2);
    return res;    
}

float ds2777g_read_temperature(ds2777g_config_t config, bool *valid)
{
    float temp_celsius = 0.0;
    int16_t temp_raw = 0;
    int res = 0;

    valid = 0;
    res = ds2777g_read_temperature_raw(config, &temp_raw);
    if (res == 0) {temp_celsius = (float)(temp_raw * 0.125); valid = true;}
    return temp_celsius;
}

int ds2777g_read_temperature_raw(ds2777g_config_t config, int16_t *temp_raw)
{
    int res = 0;
    uint8_t temp_buf[2];
    res = ds2777g_read_data(config, TEMPERATURE_REGISTER_MSB, temp_buf, 2);
    temp_raw = ((int16_t)((temp_buf[1] << 8) + temp_buf[0])) >> 5;
    return res;
}

int ds2777g_write_data(ds2777g_config_t config, uint8_t *data, const uint16_t len)
{
    int res = 0;
    res = i2c_write(config.port, config.slave_adr, data, len);
    return res;
}

int ds2777g_read_data(ds2777g_config_t config, uint8_t target_reg, uint8_t *data, uint16_t len)
{
    int res = 0;
    uint8_t reg[1] = {target_reg};
    res = i2c_write(config.port, config.slave_adr, reg, 1);
    if (res != 0) {return res;}

    res = i2c_read(config.port, config.slave_adr, data, len);
    return res;
}

/** \} End of ds2777g group */
