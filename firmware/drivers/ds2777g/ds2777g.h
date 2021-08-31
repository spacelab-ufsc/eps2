/*
 * ds2777g.h
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
 * \brief DS2777G+ driver definition.
 * 
 * \author Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 * 
 * \version 0.2.0
 * 
 * \date 2021/08/17
 * 
 * \defgroup ds2777g DS2777G
 * \ingroup drivers
 * \{
 */

#ifndef DS2777G_H_
#define DS2777G_H_

#include <stdint.h>
#include <stdbool.h>

#include <drivers/i2c/i2c.h>

#define DS2777G_MODULE_NAME "DS2777"

#define DS2777G_RSENSE                                          0.01 /* Unit: Ohm. */

/**
 * https://datasheets.maximintegrated.com/en/ds/DS2775-DS2778.pdf
 */
#define DS2777G_DEFAULT_SLAVE_ADDRESS                           0b1011001

/**
 * \brief Memory map.
 */
// Read/Write registers.
#define DS2777G_PROTECTION_REGISTER                             0x00
#define DS2777G_STATUS_REGISTER                                 0x01
#define DS2777G_ACCUMULATED_CURRENT_MSB                         0x10
#define DS2777G_ACCUMULATED_CURRENT_LSB                         0x11
#define DS2777G_AGE_SCALAR_REGISTER                             0x14
#define DS2777G_SPECIAL_FEATURE_REGISTER                        0x15
#define DS2777G_CYCLE_COUNTER_REGISTER                          0x1E
#define DS2777G_EEPROM_REGISTER                                 0x1F
// 0x20 to 0x2F <-- User EEPROM Register, Lockable, Block 0.
#define DS2777G_USER_EEPROM_BYTE_1                              0x20
#define DS2777G_USER_EEPROM_BYTE_2                              0x21
#define DS2777G_USER_EEPROM_BYTE_3                              0x22
#define DS2777G_USER_EEPROM_BYTE_4                              0x23
#define DS2777G_USER_EEPROM_BYTE_5                              0x24
#define DS2777G_USER_EEPROM_BYTE_6                              0x25
#define DS2777G_USER_EEPROM_BYTE_7                              0x26
#define DS2777G_USER_EEPROM_BYTE_8                              0x27
#define DS2777G_USER_EEPROM_BYTE_9                              0x28
#define DS2777G_USER_EEPROM_BYTE_10                             0x29
#define DS2777G_USER_EEPROM_BYTE_11                             0x2A
#define DS2777G_USER_EEPROM_BYTE_12                             0x2B
#define DS2777G_USER_EEPROM_BYTE_13                             0x2C
#define DS2777G_USER_EEPROM_BYTE_14                             0x2D
#define DS2777G_USER_EEPROM_BYTE_15                             0x2E
#define DS2777G_USER_EEPROM_BYTE_16                             0x2F
// 0x60 to 0x80 <-- Parameter EEPROM Register, Lockable, Block 1.
#define DS2777G_CONTROL_REGISTER                                0x60
#define DS2777G_ACCUMULATION_BIAS_REGISTER                      0x61
#define DS2777G_AGING_CAPACITY_REGISTER_MSB                     0x62
#define DS2777G_AGING_CAPACITY_REGISTER_LSB                     0x63
#define DS2777G_CHARGE_VOLTAGE_REGISTER                         0x64
#define DS2777G_MINIMUN_CHARGE_CURRENT_REGISTER                 0x65
#define DS2777G_ACTIVE_EMPTY_VOLTAGE_REGISTER                   0x66
#define DS2777G_ACTIVE_EMPTY_CURRENT_REGISTER                   0x67
#define DS2777G_ACTIVE_EMPTY_40_REGISTER                        0x68
#define DS2777G_SENSE_RESISTOR_PRIME_REGISTER                   0x69
#define DS2777G_FULL_40_MSB_REGISTER                            0x6A
#define DS2777G_FULL_40_LSB_REGISTER                            0x6B
#define DS2777G_FULL_SEGMENTE_4_SLOPE_REGISTER                  0x6C
#define DS2777G_FULL_SEGMENTE_3_SLOPE_REGISTER                  0x6D
#define DS2777G_FULL_SEGMENTE_2_SLOPE_REGISTER                  0x6E
#define DS2777G_FULL_SEGMENTE_1_SLOPE_REGISTER                  0x6F
#define DS2777G_AE_SEGMENTE_4_SLOPE_REGISTER                    0x70
#define DS2777G_AE_SEGMENTE_3_SLOPE_REGISTER                    0x71
#define DS2777G_AE_SEGMENTE_2_SLOPE_REGISTER                    0x72
#define DS2777G_AE_SEGMENTE_1_SLOPE_REGISTER                    0x73
#define DS2777G_SE_SEGMENTE_4_SLOPE_REGISTER                    0x74
#define DS2777G_SE_SEGMENTE_3_SLOPE_REGISTER                    0x75
#define DS2777G_SE_SEGMENTE_2_SLOPE_REGISTER                    0x76
#define DS2777G_SE_SEGMENTE_1_SLOPE_REGISTER                    0x77
#define DS2777G_SENSE_RESISTOR_GAIN_REGISTER_MSB                0x78
#define DS2777G_SENSE_RESISTOR_GAIN_REGISTER_LSB                0x79
#define DS2777G_SENSE_RESISTOR_TEMPERATURE_COEFFICIENT_REGISTER 0x7A
#define DS2777G_CURRENT_OFFSET_BIAS_REGISTER                    0x7B
#define DS2777G_TBP34_REGISTER                                  0x7C
#define DS2777G_TBP23_REGISTER                                  0x7D
#define DS2777G_TBP12_REGISTER                                  0x7E
#define DS2777G_PROTECTOR_THRESHOLD_REGISTER                    0x7F
#define DS2777G_TWO_WIRE_SLAVE_ADDRESS_REGISTER                 0x80
// Read registers.
#define DS2777G_RAAC_REGISTER_MSB                               0x02
#define DS2777G_RAAC_REGISTER_LSB                               0x03
#define DS2777G_RSAC_REGISTER_MSB                               0x04
#define DS2777G_RSAC_REGISTER_LSB                               0x05
#define DS2777G_RARC_REGISTER                                   0x06
#define DS2777G_RSRC_REGISTER                                   0x07
#define DS2777G_AVERAGE_CURRENT_REGISTER_MSB                    0x08
#define DS2777G_AVERAGE_CURRENT_REGISTER_LSB                    0x09
#define DS2777G_TEMPERATURE_REGISTER_MSB                        0x0A
#define DS2777G_TEMPERATURE_REGISTER_LSB                        0x0B
#define DS2777G_VOLTAGE_REGISTER_MSB_Vin1_Vss                   0x0C
#define DS2777G_VOLTAGE_REGISTER_LSB_Vin1_Vss                   0x0D
#define DS2777G_CURRENT_REGISTER_MSB                            0x0E
#define DS2777G_CURRENT_REGISTER_LSB                            0x0F
#define DS2777G_ACCUMULATED_CURRENT_LSB_MINUS_1                 0x12
#define DS2777G_ACCUMULATED_CURRENT_LSB_MINUS_2                 0x13
#define DS2777G_FULL_REGISTER_MSB                               0x16
#define DS2777G_FULL_REGISTER_LSB                               0x17
#define DS2777G_ACTIVE_EMPTY_REGISTER_MSB                       0x18
#define DS2777G_ACTIVE_EMPTY_REGISTER_LSB                       0x19
#define DS2777G_STANDBY_EMPTY_REGISTER_MSB                      0x1A
#define DS2777G_STANDBY_EMPTY_REGISTER_LSB                      0x1B
#define DS2777G_VOLTAGE_REGISTER_MSB_Vin2_Vin1                  0x1C
#define DS2777G_VOLTAGE_REGISTER_LSB_Vin2_Vin1                  0x1D
#define DS2777G_FACTORY_GAIN_RSGAIN_REGISTER_MSB                0xB0
#define DS2777G_FACTORY_GAIN_RSGAIN_REGISTER_LSB                0xB1
// Write registers.
#define DS2777G_TWO_WIRE_COMMAND_REGISTER                       0xFE

/**
 * @brief Function commands.
 */
#define DS2777G_COPY_DATA_USER_EEPROM                           0x42
#define DS2777G_COPY_DATA_PARAMETER_EEPROM                      0x44
#define DS2777G_RECALL_DATA_USER_EEPROM                         0xB2
#define DS2777G_RECALL_DATA_PARAMETER_EEPROM                    0xB4
#define DS2777G_LOCK_USER_EEPROM                                0x63
#define DS2777G_LOCK_PARAMETER_EEPROM                           0x66
#define DS2777G_READ_ROM_ID                                     0x39

/**
 * @brief Register specific bit mask.
 */
// Protection register.
#define DS2777G_CHARGE_CONTROL_FLAG                             (1 << 3)
#define DS2777G_DISCHARGE_CONTROL_FLAG                          (1 << 2)
#define DS2777G_CHARGE_ENABLE_BIT                               (1 << 1)
#define DS2777G_DISCHARGE_ENABLE_BIT                            (1 << 0)

typedef struct
{
    i2c_port_t  port;
    i2c_slave_adr_t slave_adr;
} ds2777g_config_t;

/**
 * \brief
 * 
 * \param config DS2777G configuration parameters.
 * \return int The status/error code.
 */
int ds2777g_init(ds2777g_config_t config);

/**
 * @brief Set charge enable bit in protection register.
 * 
 * @param config DS2777G configuration parameters.
 * @return int The status/error code.
 */
int ds2777g_enable_charge(ds2777g_config_t config);

/**
 * @brief Set discharge enable bit in protection register.
 * 
 * @param config DS2777G configuration parameters.
 * @return int The status/error code.
 */
int ds2777g_enable_discharge(ds2777g_config_t config);

/**
 * @brief Reset charge enable bit in protection register.
 * 
 * @param config DS2777G configuration parameters.
 * @return int The status/error code.
 */
int ds2777g_disable_charge(ds2777g_config_t config);

/**
 * @brief Reset discharge enable bit in protection register.
 * 
 * @param config DS2777G configuration parameters.
 * @return int The status/error code.
 */
int ds2777g_disable_discharge(ds2777g_config_t config);

/**
 * @brief Get the raw voltage in two's complement form from the DS2777G.
 * 
 * @param config DS2777G configuration parameters.
 * @param voltage_raw The raw voltage value.
 * @param battery_select Must be either 1 or 2.
 * @return int The status/error code.
 */
int ds2777g_read_voltage_raw(ds2777g_config_t config, int16_t *voltage_raw, uint8_t battery_select);

/**
 * @brief Convert from raw data to mV.
 * 
 * Resolution: 4.8828mV. Goes from -5000mV to 4995.1mV
 * Sign | 2^9 | 2^8 | 2^7 | 2^6 | 2^5 | 2^4 | 2^3 | 2^2 | 2^1 | 2^0 | X | X | X | X | X
 *                       MSB                      |                    LSB              
 * 
 * @param raw The raw voltage value.
 * @return float Converted voltage in mV.
 */
int16_t ds2777g_voltage_raw_to_mv(int16_t raw);

/**
 * @brief Get the voltage in mV from one of the batteries connected to the DS2777G.
 * 
 * @param config DS2777G configuration parameters.
 * @param voltage_mv Voltage in mV.
 * @param battery_select Must be either 1 or 2.
 * @return int The status/error code.
 */
int ds2777g_read_voltage_mv(ds2777g_config_t config, int16_t *voltage_mv, uint8_t battery_select);

/**
 * @brief Get the raw temperature in two's complement form from the DS2777G.
 * 
 * @param config DS2777G configuration parameters.
 * @param temp_raw The raw temperature value.
 * @return int The status/error code.
 */
int ds2777g_read_temperature_raw(ds2777g_config_t config, int16_t *temp_raw);

/**
 * @brief Convert from raw data to celsius.
 * 
 * Resolution: 0.125 degrees celsius.
 * Sign | 2^9 | 2^8 | 2^7 | 2^6 | 2^5 | 2^4 | 2^3 | 2^2 | 2^1 | 2^0 | X | X | X | X | X
 *                       MSB                      |                    LSB              
 * 
 * @param raw The raw temperature value.
 * @return float Converted temperature in celsius.
 */
float ds2777g_temperature_raw_to_celsius(int16_t raw);

/**
 * @brief Get the temperature in celsius from the DS2777G.
 * 
 * @param config DS2777G configuration parameters.
 * @param temp_celsius Temperature in celsius.
 * @return int The status/error code.
 */
int ds2777g_read_temperature_celsius(ds2777g_config_t config, float *temp_celsius);

/**
 * @brief Get the raw current in two's complement form from the DS2777G.
 * 
 * @param config DS2777G configuration parameters.
 * @param current_raw The raw current value.
 * @param read_average Whether to read the last current raw value [false] or a mean of the last eight values [true].
 * @return int The status/error code.
 */
int ds2777g_read_current_raw(ds2777g_config_t config, int16_t *current_raw, bool read_average);

/**
 * @brief Convert from raw data to mA.
 * 
 * Resolution: 1.5625uV/R_sense. Goes from -51.2mV/R_sense to 51.2mV/R_sense.
 * 
 * @param raw The raw current value.
 * @return int16_t Converted current in mA.
 */
int16_t ds2777g_current_raw_to_ma(int16_t raw);

/**
 * @brief Get the voltage in mA from the DS2777G (instantaneous or average from last eight).
 * 
 * @param config DS2777G configuration parameters.
 * @param current_ma Current in mA.
 * @param read_average Whether to read the last current raw value [false] or a mean of the last eight values [true].
 * @return int The status/error code.
 */
int ds2777g_read_current_ma(ds2777g_config_t config, int16_t *current_ma, bool read_average);

/**
 * \brief Write-Data Protocol
 * 
 * Start SAddr MAddr Data0 Data1 ... DataN Stop
 * 
 * \param config DS2777G configuration parameters.
 * \param data Data to write. First byte must be target register address.
 * \param len Length of the data to write, including target register.
 * \return int The status/error code.
 */
int ds2777g_write_data(ds2777g_config_t config, uint8_t *data, uint16_t len);

/**
 * @brief 
 * 
 * Start SAddr MAddr StartRepeat SAddr Data0 Data1 ... DataN Stop
 * 
 * \param config DS2777G configuration parameters.
 * \param target_reg Target register to read from.
 * \param data Pointer to store data read.
 * \param len Length of the data do read.
 * \return int The status/error code.
 */
int ds2777g_read_data(ds2777g_config_t config, uint8_t target_reg, uint8_t *data, uint16_t len);

#endif /* DS2777G_H_ */

/** \} End of ds2777g group */
