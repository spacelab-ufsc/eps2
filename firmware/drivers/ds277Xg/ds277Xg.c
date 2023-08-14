/*
 * ds277Xg.c
 *
 * Copyright The EPS 2.0 Contributors.
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
 * \brief DS277XG+ driver implementation.
 *
 * \author Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * \author Ramon de Araujo Borba     <ramonborba97@gmail.com>
 *
 * \version 0.4.0
 *
 * \date 2021/08/17
 *
 * \addtogroup ds277Xg
 * \{
 */

#include <config/config.h>
#include <system/sys_log/sys_log.h>

#include "ds277Xg.h"

int ds277Xg_init(ds277Xg_config_t *config)
{
    /* I2C port initialization. */
    if (i2c_init(config->port, (i2c_config_t){.speed_hz = 100000}) != 0)
    {
    #if defined(CONFIG_DRIVERS_DEBUG_ENABLED) && (CONFIG_DRIVERS_DEBUG_ENABLED == 1)
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS277XG_MODULE_NAME, "Error initializing I2C port!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */

        return -1;
    }

    /* Protection register configuration. */
    if (ds277Xg_enable_charge(config) != 0) {return -1;}
    if (ds277Xg_enable_discharge(config) != 0) {return -1;}

    /* Parameters registers configuration. */
    bool rewrite = false;
    uint8_t read_buffer[DS277XG_PARAMETER_EEPROM_SIZE] = { 0 };
    uint8_t params[DS277XG_PARAMETER_EEPROM_SIZE+1] = {
        DS277XG_PARAMETER_EEPROM_ADDRESS,   // First byte must be address for write operation
        DS277XG_CONTROL_REG_VALUE,
        DS277XG_ACCUMULATION_BIAS_REG_VALUE,
        DS277XG_AGING_CAPACITY_REG_VALUE_MSB,
        DS277XG_AGING_CAPACITY_REG_VALUE_LSB,
        DS277XG_CHARGE_VOLTAGE_REG_VALUE,
        DS277XG_MINIMUM_CHARGE_CURRENT_REG_VALUE,
        DS277XG_ACTIVE_EMPTY_VOLTAGE_REG_VALUE,
        DS277XG_ACTIVE_EMPTY_CURRENT_REG_VALUE,
        DS277XG_ACTIVE_EMPTY_40_REG_VALUE,
        DS277XG_SENSE_RESISTOR_PRIME_REG_VALUE,
        DS277XG_FULL_40_MSB_REG_VALUE,
        DS277XG_FULL_40_LSB_REG_VALUE,
        DS277XG_FULL_SEGMENTE_4_SLOPE_REG_VALUE,
        DS277XG_FULL_SEGMENTE_3_SLOPE_REG_VALUE,
        DS277XG_FULL_SEGMENTE_2_SLOPE_REG_VALUE,
        DS277XG_FULL_SEGMENTE_1_SLOPE_REG_VALUE,
        DS277XG_AE_SEGMENTE_4_SLOPE_REG_VALUE,
        DS277XG_AE_SEGMENTE_3_SLOPE_REG_VALUE,
        DS277XG_AE_SEGMENTE_2_SLOPE_REG_VALUE,
        DS277XG_AE_SEGMENTE_1_SLOPE_REG_VALUE,
        DS277XG_SE_SEGMENTE_4_SLOPE_REG_VALUE,
        DS277XG_SE_SEGMENTE_3_SLOPE_REG_VALUE,
        DS277XG_SE_SEGMENTE_2_SLOPE_REG_VALUE,
        DS277XG_SE_SEGMENTE_1_SLOPE_REG_VALUE,
        DS277XG_SENSE_RESISTOR_GAIN_REG_VALUE_MSB,
        DS277XG_SENSE_RESISTOR_GAIN_REG_VALUE_LSB,
        DS277XG_SENSE_RESISTOR_TEMPERATURE_COEFFICIENT_REG_VALUE,
        DS277XG_CURRENT_OFFSET_BIAS_REG_VALUE,
        DS277XG_TBP34_REG_VALUE,
        DS277XG_TBP23_REG_VALUE,
        DS277XG_TBP12_REG_VALUE,
        DS277XG_PROTECTOR_THRESHOLD_REG_VALUE,
        DS277XG_TWO_WIRE_SLAVE_ADDRESS_REG_VALUE,
    };

    /* Read data from DS277Xg parameter EEPROM memory */
    if (ds277Xg_read_data(config, DS277XG_PARAMETER_EEPROM_ADDRESS, read_buffer, DS277XG_PARAMETER_EEPROM_SIZE) != 0) { return -1; };

    /* Check if registers are set correctly */
    for (uint8_t i = 0; i < DS277XG_PARAMETER_EEPROM_SIZE; i++)
    {
        if (read_buffer[i] != params[i+1])
        {
            rewrite = true;
        }
    }
    if (rewrite)
    {
        /* Write parameters to DS277Xg RAM memory */
        ds277Xg_write_data(config, params, DS277XG_PARAMETER_EEPROM_SIZE);

        /* Send copy data command to store the values in the DS277Xg EEPROM memory */
        uint8_t wr_buf[2] = {
            DS277XG_TWO_WIRE_COMMAND_REGISTER,
            DS277XG_COPY_DATA_PARAMETER_EEPROM,
        };
        if (ds277Xg_write_data(config, wr_buf, 2) != 0) {return -1;}
    }

#if defined(RESET_BATTERY_TO_INITIAL_STATE) && (RESET_BATTERY_TO_INITIAL_STATE == 1)
    if (ds277Xg_set_battery_to_initial_state(config) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS277XG_MODULE_NAME, "Error configuring battery to initial state!");
        sys_log_new_line();
    }
#endif /* RESET_BATTERY_TO_INITIAL_STATE */

    return 0;
}

int ds277Xg_set_battery_to_initial_state(ds277Xg_config_t *config)
{
    uint8_t wr_buf[3] = {0};

    /* Set battery configurations to initial state */

    /* Set Age Scalar to 100% */
    wr_buf[0] = DS277XG_AGE_SCALAR_REGISTER;
    wr_buf[1] = (uint8_t)(CELL_INITIAL_AGE_SCALAR/DS277XG_AGE_SCALAR_REG_RESOLUTION);
    if (ds277Xg_write_data(config, wr_buf, 2) != 0) {return -1;}

    /* Set accumulated current to maximum battery capacity */
    ds277Xg_write_accumulated_current_max_value(config);

    // Copy from shadow RAM to EEPROM.
    wr_buf[0] = DS277XG_TWO_WIRE_COMMAND_REGISTER;
    wr_buf[1] = DS277XG_COPY_DATA_PARAMETER_EEPROM;
    if (ds277Xg_write_data(config, wr_buf, 2) != 0) {return -1;}

    return 0;
}

int ds277Xg_enable_charge(ds277Xg_config_t *config)
{
    uint8_t value = 0;
    if (ds277Xg_read_data(config, DS277XG_PROTECTION_REGISTER, &value, 1) != 0) {return -1;}

    uint8_t temp[2] = {DS277XG_PROTECTION_REGISTER, (value | DS277XG_CHARGE_ENABLE_BIT)};
    if (ds277Xg_write_data(config, temp, 2) != 0) {return -1;}

    return 0;
}

int ds277Xg_enable_discharge(ds277Xg_config_t *config)
{
    uint8_t value = 0;
    if (ds277Xg_read_data(config, DS277XG_PROTECTION_REGISTER, &value, 1) != 0) {return -1;}

    uint8_t temp[2] = {DS277XG_PROTECTION_REGISTER, (value | DS277XG_DISCHARGE_ENABLE_BIT)};
    if (ds277Xg_write_data(config, temp, 2) != 0) {return -1;}
    return 0;
}

int ds277Xg_disable_charge(ds277Xg_config_t *config)
{
    uint8_t value = 0;
    if (ds277Xg_read_data(config, DS277XG_PROTECTION_REGISTER, &value, 1) != 0) {return -1;}

    uint8_t temp[2] = {DS277XG_PROTECTION_REGISTER, (value & (0xFF - DS277XG_CHARGE_ENABLE_BIT))};
    if (ds277Xg_write_data(config, temp, 2) != 0) {return -1;}

    return 0;
}

int ds277Xg_disable_discharge(ds277Xg_config_t *config)
{
    uint8_t value = 0;
    if (ds277Xg_read_data(config, DS277XG_PROTECTION_REGISTER, &value, 1) != 0) {return -1;}

    uint8_t temp[2] = {DS277XG_PROTECTION_REGISTER, (value & (0xFF - DS277XG_DISCHARGE_ENABLE_BIT))};
    if (ds277Xg_write_data(config, temp, 2) != 0) {return -1;}

    return 0;
}

int ds277Xg_read_voltage_raw(ds277Xg_config_t *config, int16_t *voltage_raw, uint8_t battery_select)
{
    uint8_t buf[2];
    if (battery_select == 1)
    {
        if (ds277Xg_read_data(config, DS277XG_VOLTAGE_REGISTER_MSB_Vin1_Vss, buf, 2) != 0) {return -1;}
    }
    else if (battery_select == 2)
    {
        if (ds277Xg_read_data(config, DS277XG_VOLTAGE_REGISTER_MSB_Vin2_Vin1, buf, 2) != 0) {return -1;}
    }
    else
    {
    #if defined(CONFIG_DRIVERS_DEBUG_ENABLED) && (CONFIG_DRIVERS_DEBUG_ENABLED == 1)
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS277XG_MODULE_NAME, "Invalid value for battery number! (Must either 1 or 2)");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return -1;
    }
    *voltage_raw = ((int16_t)((buf[0] << 8) + buf[1])) >> 5;
    return 0;
}

int16_t ds277Xg_voltage_raw_to_mv(int16_t raw)
{
    return raw * DS277XG_VOLTAGE_REG_RESOLUTION;
}

int ds277Xg_read_voltage_mv(ds277Xg_config_t *config, int16_t *voltage_mv, uint8_t battery_select)
{
    int16_t voltage_raw = 0;

    if (ds277Xg_read_voltage_raw(config, &voltage_raw, battery_select) != 0)
    {
    #if defined(CONFIG_DRIVERS_DEBUG_ENABLED) && (CONFIG_DRIVERS_DEBUG_ENABLED == 1)
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS277XG_MODULE_NAME, "Error reading the raw voltage value!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return -1;
    }

    *voltage_mv = ds277Xg_voltage_raw_to_mv(voltage_raw);
    return 0;
}

int ds277Xg_read_temperature_raw(ds277Xg_config_t *config, int16_t *temp_raw)
{
    uint8_t buf[2];
    if (ds277Xg_read_data(config, DS277XG_TEMPERATURE_REGISTER_MSB, buf, 2) != 0) {return -1;}
    *temp_raw = ((int16_t)((buf[0] << 8) + buf[1])) >> 5;
    return 0;
}

uint16_t ds277Xg_temperature_raw_to_kelvin(int16_t raw)
{
    return ((raw * DS277XG_TEMPERATURE_REG_RESOLUTION)/* Temperature in Celsius */ + 273.15 /* Celsius to Kelvin conversion */);
}

int ds277Xg_read_temperature_kelvin(ds277Xg_config_t *config, uint16_t *temp_kelvin)
{
    int16_t temp_raw = 0;

    if (ds277Xg_read_temperature_raw(config, &temp_raw) != 0)
    {
    #if defined(CONFIG_DRIVERS_DEBUG_ENABLED) && (CONFIG_DRIVERS_DEBUG_ENABLED == 1)
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS277XG_MODULE_NAME, "Error reading the raw temperature value!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return -1;
    }

    *temp_kelvin = ds277Xg_temperature_raw_to_kelvin(temp_raw);
    return 0;
}

int ds277Xg_read_current_raw(ds277Xg_config_t *config, int16_t *current_raw, bool read_average)
{
    uint8_t buf[2];
    if (read_average == true)
    {
        if (ds277Xg_read_data(config, DS277XG_AVERAGE_CURRENT_REGISTER_MSB, buf, 2) != 0) {return -1;}
    }
    else /* Read instantaneous instead; */
    {
        if (ds277Xg_read_data(config, DS277XG_CURRENT_REGISTER_MSB, buf, 2) != 0) {return -1;}
    }
    *current_raw = (int16_t)((buf[0] << 8) + buf[1]);
    return 0;
}

int16_t ds277Xg_current_raw_to_ma(int16_t raw)
{
    return raw * (DS277XG_CURRENT_REG_RESOLUTION / DS277XG_RSENSE) /* current in microamps */ / 1000 /* convert microamps to milliamps */;
}

int ds277Xg_read_current_ma(ds277Xg_config_t *config, int16_t *current_ma, bool read_average)
{
    int16_t current_raw = 0;

    if (ds277Xg_read_current_raw(config, &current_raw, read_average) != 0)
    {
    #if defined(CONFIG_DRIVERS_DEBUG_ENABLED) && (CONFIG_DRIVERS_DEBUG_ENABLED == 1)
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS277XG_MODULE_NAME, "Error reading the raw current value!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return -1;
    }

    *current_ma = ds277Xg_current_raw_to_ma(current_raw);
    return 0;
}

int ds277Xg_write_accumulated_current_raw(ds277Xg_config_t *config, uint16_t acc_current_raw)
{
    uint8_t buf[3] = {DS277XG_ACCUMULATED_CURRENT_MSB, ((uint8_t)(acc_current_raw >> 8)), ((uint8_t)acc_current_raw)};
    if (ds277Xg_write_data(config, buf, 3) != 0) {return -1;}
    return 0;
}

uint16_t ds277Xg_accumulated_current_mah_to_raw(uint16_t mah)
{
    return mah * (DS277XG_RSENSE) / (DS277XG_ACCUMULATED_CURRENT_REG_RESOLUTION / 1000);
}

int ds277Xg_write_accumulated_current_mah(ds277Xg_config_t *config, uint16_t acc_current_mah)
{
    return ds277Xg_write_accumulated_current_raw(config, ds277Xg_accumulated_current_mah_to_raw(acc_current_mah));
}

int ds277Xg_write_accumulated_current_max_value(ds277Xg_config_t *config)
{
    return ds277Xg_write_accumulated_current_mah(config, (2*MAX_BATTERY_CHARGE));
}

int ds277Xg_read_accumulated_current_raw(ds277Xg_config_t *config, uint16_t *acc_current_raw)
{
    uint8_t buf[2];
    if (ds277Xg_read_data(config, DS277XG_ACCUMULATED_CURRENT_MSB, buf, 2) != 0) {return -1;}
    *acc_current_raw = (int16_t)((buf[0] << 8) + buf[1]);
    return 0;
}

uint16_t ds277Xg_accumulated_current_raw_to_mah(uint16_t raw)
{
    return raw * DS277XG_ACCUMULATED_CURRENT_REG_RESOLUTION / (DS277XG_RSENSE_MOHMS);
}

int ds277Xg_read_accumulated_current_mah(ds277Xg_config_t *config, uint16_t *acc_current_mah)
{
    uint16_t acc_current_raw = 0;

    if (ds277Xg_read_accumulated_current_raw(config, &acc_current_raw) != 0)
    {
    #if defined(CONFIG_DRIVERS_DEBUG_ENABLED) && (CONFIG_DRIVERS_DEBUG_ENABLED == 1)
        sys_log_print_event_from_module(SYS_LOG_ERROR, DS277XG_MODULE_NAME, "Error reading the raw accumulated current value!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return -1;
    }

    *acc_current_mah = ds277Xg_current_raw_to_ma(acc_current_raw);
    return 0;
}

int ds277Xg_write_cycle_counter(ds277Xg_config_t *config, uint16_t cycles)
{
    if(cycles > 510) { cycles = 510; }
    uint8_t buf[2] = {DS277XG_CYCLE_COUNTER_REGISTER, (uint8_t)(cycles >> 1)}; // shift right to divide by two.
    if (ds277Xg_write_data(config, buf, 2) != 0) {return -1;}
    return 0;
}

int ds277Xg_read_cycle_counter(ds277Xg_config_t *config, uint16_t *cycles)
{
    uint8_t buf[1];
    if (ds277Xg_read_data(config, DS277XG_CYCLE_COUNTER_REGISTER, buf, 1) != 0) {return -1;}
    *cycles = ((uint16_t)*buf) << 1; // shift left to multiply by two.
    return 0;
}

int ds277Xg_write_data(ds277Xg_config_t *config, uint8_t *data, const uint16_t len)
{
#if defined(CONFIG_DRIVERS_DS277X_ONEWIRE_VERSION) && (CONFIG_DRIVERS_DS277X_ONEWIRE_VERSION == 1)
    if(onewire_reset(config->port) == 0) {return -1;}
    if(onewire_write_byte(config->port, data, len) == -1) {return -1;}
    return 0;
#else
    return i2c_write(config->port, config->slave_adr, data, len);
#endif
}

int ds277Xg_read_data(ds277Xg_config_t *config, uint8_t target_reg, uint8_t *data, uint16_t len)
{
#if defined(CONFIG_DRIVERS_DS277X_ONEWIRE_VERSION) && (CONFIG_DRIVERS_DS277X_ONEWIRE_VERSION == 1)
    uint8_t read_command[3] = {DS2775G_SKIP_ADDRESS, DS2775G_READ_DATA, target_reg};
    if(ds277Xg_write_data(config, read_command, 0x3) == -1) {return -1;}
    if(onewire_read_byte(config->port, data, len) == -1) {return -1;}
    return 0;
#else
    uint8_t reg[1] = {target_reg};

    if (i2c_write(config->port, config->slave_adr, reg, 1) != 0) {return -1;}
    return i2c_read(config->port, config->slave_adr, data, len);
#endif
}

/** \} End of ds277Xg group */
