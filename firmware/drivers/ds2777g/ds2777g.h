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

#define DS2777_MODULE_NAME          "DS2777"

/**
 * https://datasheets.maximintegrated.com/en/ds/DS2775-DS2778.pdf
 */
#define DS2777_DEFAULT_SLAVE_ADDRESS        0b1011001

/**
 * \brief Memory map.
 */
// Read/Write registers.
#define PROTECTION_REGISTER                             0x00
#define STATUS_REGISTER                                 0x01
#define ACCUMULATED_CURRENT_MSB                         0x10
#define ACCUMULATED_CURRENT_LSB                         0x11
#define AGE_SCALAR_REGISTER                             0x14
#define SPECIAL_FEATURE_REGISTER                        0x15
#define CYCLE_COUNTER_REGISTER                          0x1E
#define EEPROM_REGISTER                                 0x1F
// 0x20 to 0x2F <-- User EEPROM Register, Lockable, Block 0.
#define USER_EEPROM_BYTE_1                              0x20
#define USER_EEPROM_BYTE_2                              0x21
#define USER_EEPROM_BYTE_3                              0x22
#define USER_EEPROM_BYTE_4                              0x23
#define USER_EEPROM_BYTE_5                              0x24
#define USER_EEPROM_BYTE_6                              0x25
#define USER_EEPROM_BYTE_7                              0x26
#define USER_EEPROM_BYTE_8                              0x27
#define USER_EEPROM_BYTE_9                              0x28
#define USER_EEPROM_BYTE_10                             0x29
#define USER_EEPROM_BYTE_11                             0x2A
#define USER_EEPROM_BYTE_12                             0x2B
#define USER_EEPROM_BYTE_13                             0x2C
#define USER_EEPROM_BYTE_14                             0x2D
#define USER_EEPROM_BYTE_15                             0x2E
#define USER_EEPROM_BYTE_16                             0x2F
// 0x60 to 0x80 <-- Parameter EEPROM Register, Lockable, Block 1.
#define CONTROL_REGISTER                                0x60
#define ACCUMULATION_BIAS_REGISTER                      0x61
#define AGING_CAPACITY_REGISTER_MSB                     0x62
#define AGING_CAPACITY_REGISTER_LSB                     0x63
#define CHARGE_VOLTAGE_REGISTER                         0x64
#define MINIMUN_CHARGE_CURRENT_REGISTER                 0x65
#define ACTIVE_EMPTY_VOLTAGE_REGISTER                   0x66
#define ACTIVE_EMPTY_CURRENT_REGISTER                   0x67
#define ACTIVE_EMPTY_40_REGISTER                        0x68
#define SENSE_RESISTOR_PRIME_REGISTER                   0x69
#define FULL_40_MSB_REGISTER                            0x6A
#define FULL_40_LSB_REGISTER                            0x6B
#define FULL_SEGMENTE_4_SLOPE_REGISTER                  0x6C
#define FULL_SEGMENTE_3_SLOPE_REGISTER                  0x6D
#define FULL_SEGMENTE_2_SLOPE_REGISTER                  0x6E
#define FULL_SEGMENTE_1_SLOPE_REGISTER                  0x6F
#define AE_SEGMENTE_4_SLOPE_REGISTER                    0x70
#define AE_SEGMENTE_3_SLOPE_REGISTER                    0x71
#define AE_SEGMENTE_2_SLOPE_REGISTER                    0x72
#define AE_SEGMENTE_1_SLOPE_REGISTER                    0x73
#define SE_SEGMENTE_4_SLOPE_REGISTER                    0x74
#define SE_SEGMENTE_3_SLOPE_REGISTER                    0x75
#define SE_SEGMENTE_2_SLOPE_REGISTER                    0x76
#define SE_SEGMENTE_1_SLOPE_REGISTER                    0x77
#define SENSE_RESISTOR_GAIN_REGISTER_MSB                0x78
#define SENSE_RESISTOR_GAIN_REGISTER_LSB                0x79
#define SENSE_RESISTOR_TEMPERATURE_COEFFICIENT_REGISTER 0x7A
#define CURRENT_OFFSET_BIAS_REGISTER                    0x7B
#define TBP34_REGISTER                                  0x7C
#define TBP23_REGISTER                                  0x7D
#define TBP12_REGISTER                                  0x7E
#define PROTECTOR_THRESHOLD_REGISTER                    0x7F
#define TWO_WIRE_SLAVE_ADDRESS_REGISTER                 0x80
// Read registers.
#define RAAC_REGISTER_MSB                               0x02
#define RAAC_REGISTER_LSB                               0x03
#define RSAC_REGISTER_MSB                               0x04
#define RSAC_REGISTER_LSB                               0x05
#define RARC_REGISTER                                   0x06
#define RSRC_REGISTER                                   0x07
#define AVERAGE_CURRENT_REGISTER_MSB                    0x08
#define AVERAGE_CURRENT_REGISTER_LSB                    0x09
#define TEMPERATURE_REGISTER_MSB                        0x0A
#define TEMPERATURE_REGISTER_LSB                        0x0B
#define VOLTAGE_REGISTER_MSB_Vin1_Vss                   0x0C
#define VOLTAGE_REGISTER_LSB_Vin1_Vss                   0x0D
#define CURRENT_REGISTER_MSB                            0x0E
#define CURRENT_REGISTER_LSB                            0x0F
#define ACCUMULATED_CURRENT_LSB_MINUS_1                 0x12
#define ACCUMULATED_CURRENT_LSB_MINUS_2                 0x13
#define FULL_REGISTER_MSB                               0x16
#define FULL_REGISTER_LSB                               0x17
#define ACTIVE_EMPTY_REGISTER_MSB                       0x18
#define ACTIVE_EMPTY_REGISTER_LSB                       0x19
#define STANDBY_EMPTY_REGISTER_MSB                      0x1A
#define STANDBY_EMPTY_REGISTER_LSB                      0x1B
#define VOLTAGE_REGISTER_MSB_Vin2_Vin1                  0x1C
#define VOLTAGE_REGISTER_LSB_Vin2_Vin1                  0x1D
#define FACTORY_GAIN_RSGAIN_REGISTER_MSB                0xB0
#define FACTORY_GAIN_RSGAIN_REGISTER_LSB                0xB1
// Write registers.
#define TWO_WIRE_COMMAND_REGISTER                       0xFE

/**
 * @brief Function commands.
 */
#define COPY_DATA_USER_EEPROM                           0x42
#define COPY_DATA_PARAMETER_EEPROM                      0x44
#define RECALL_DATA_USER_EEPROM                         0xB2
#define RECALL_DATA_PARAMETER_EEPROM                    0xB4
#define LOCK_USER_EEPROM                                0x63
#define LOCK_PARAMETER_EEPROM                           0x66
#define READ_ROM_ID                                     0x39

/**
 * @brief Register specific bit mask.
 */
// Protection register.
#define CHARGE_CONTROL_FLAG                             (1 << 3)
#define DISCHARGE_CONTROL_FLAG                          (1 << 2)
#define CHARGE_ENABLE_BIT                               (1 << 1)
#define DISCHARGE_ENABLE_BIT                            (1 << 0)

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
 * @brief Get the temperature in celsius from the DS2777G.
 * 
 * @param config DS2777G configuration parameters.
 * @param valid Tell whether the read value is valid (1 valid, 0 not valid).
 * @return float Temperature in celsius (0xFFFF if error).
 */
float ds2777g_read_temperature(ds2777g_config_t config, bool *valid);

/**
 * @brief Reads both temperature registers (MSB and LSB).
 * 
 * Sign | 2^9 | 2^8 | 2^7 | 2^6 | 2^5 | 2^4 | 2^3 | 2^2 | 2^1 | 2^0 | X | X | X | X | X
 *                       MSB                      |                    LSB              
 * Resolution: 0.125 degree C.
 * 
 * @param config DS2777G configuration parameters.
 * @param temperature Pointer to store the raw value.
 * @return int 
 */
int ds2777g_read_temperature_raw(ds2777g_config_t config, int16_t *temp_raw);

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
