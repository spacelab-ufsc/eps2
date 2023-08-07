/*
 * ds277Xg.h
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
 * \brief DS277XG+ driver definition.
 * 
 * \author Vinicius Pimenta Bernardo    <viniciuspibi@gmail.com>
 * \author Ramon de Araujo Borba        <ramonborba97@gmail.com>
 * 
 * \version 0.4.0
 * 
 * \date 2021/08/17
 * 
 * \defgroup ds277Xg DS277XG
 * \ingroup drivers
 * \{
 */

#ifndef DS277XG_H_
#define DS277XG_H_

#include <stdint.h>
#include <stdbool.h>

#include <config/config.h>

#if defined(CONFIG_DRIVERS_DS277X_ONEWIRE_VERSION) && (CONFIG_DRIVERS_DS277X_ONEWIRE_VERSION == 1)
#include <drivers/onewire/onewire.h>
#else
#include <drivers/i2c/i2c.h>
#endif

#define DS277XG_MODULE_NAME "DS277X"

/**
 * References
 * https://datasheets.maximintegrated.com/en/ds/DS2775-DS2778.pdf
 * https://www.maximintegrated.com/en/design/technical-documents/app-notes/3/3584.html
 * https://www.maximintegrated.com/en/design/technical-documents/app-notes/1/131.html
 */

/**
 * @brief DS277XG IC parameters
 */
#define DS277XG_RSENSE                                          0.01        /* Unit: Ohm. */
#define DS277XG_RSENSE_MOHMS                                    10          /* Unit: milliohms. */
#define DS277XG_RSENSE_CONDUCTANCE                              100         /* Unit: Siemens. */
#define DS277XG_CHARGE_VOLTAGE_REG_RESOLUTION                   0.0195      /* Unit: millivolts */
#define DS277XG_MINIMUM_CHARGE_CURRENT_REG_RESOLUTION           50          /* Unit: microvolts */
#define DS277XG_ACTIVE_EMPTY_VOLTAGE_REG_RESOLUTION             0.0195      /* Unit: Volts */
#define DS277XG_ACTIVE_EMPTY_CURRENT_REG_RESOLUTION             200         /* Unit: microolts */
#define DS277XG_AGE_SCALAR_REG_RESOLUTION                       0.0078125   /* Unit: Dimentionless (percentage) */
#define DS277XG_VOLTAGE_REG_RESOLUTION                          4.8828      /* Unit: millivolts */
#define DS277XG_CURRENT_REG_RESOLUTION                          1.5625      /* Unit: microvolts */
#define DS277XG_TEMPERATURE_REG_RESOLUTION                      0.125       /* Unit: degrees Celsius */
#define DS277XG_ACCUMULATED_CURRENT_REG_RESOLUTION              6.25        /* Unit: microvolts */
#define DS277XG_FULL_40_REG_RESOLUTION                          6.25        /* Unit: microvolts */
#define DS277XG_ACTIVE_EMPTY_40_REG_RESOLUTION                  976.5625    /* Unit: ppm */
#define DS277XG_SEGMENT_SLOPE_REG_RESOLUTION                    61          /* Unit: ppm */

/**
 * @brief Battery cell parameters
 */
#define CELL_NOMINAL_VOLTAGE                                    3.6                             /* Unit: Volts (ICR18650-30B-Samsung). */
#define CELL_FULLY_CHARGED_VOLTAGE                              (0.98 * CELL_NOMINAL_VOLTAGE)   /* Unit: Volts */
#define CELL_MINIMUM_CHARGE_CURRENT                             (0.05 * MAX_BATTERY_CHARGE)     /* Unit: milliamperes */
#define CELL_INITIAL_AGE_SCALAR                                 1                            /* Unit: Dimentionless (percentage) */
#define CELL_ACTIVE_EMPTY_VOLTAGE                               2.75                            /* Unit: Volts */
#define CELL_ACTIVE_EMPTY_CURRENT                               100                             /* Unit: miliamperes */
#define CELL_FULL_40_CAPACITY                                   ((uint16_t)(2* MAX_BATTERY_CHARGE * DS277XG_RSENSE_MOHMS))
#define CELL_ACTIVE_EMPTY_40_CAPACITY                           0U                               /* ppm of Full 40 capacity */
#define CELL_FULL_SLOPE_4                                       0U                              /* Unit: ppm/C° */
#define CELL_FULL_SLOPE_3                                       5002U                           /* Unit: ppm/C° */
#define CELL_FULL_SLOPE_2                                       15555U                          /* Unit: ppm/C° */
#define CELL_FULL_SLOPE_1                                       15555U                          /* Unit: ppm/C° */
#define CELL_AE_SLOPE_4                                         0U                              /* Unit: ppm/C° */
#define CELL_AE_SLOPE_3                                         8000U                           /* Unit: ppm/C° */
#define CELL_AE_SLOPE_2                                         8000U                           /* Unit: ppm/C° */
#define CELL_AE_SLOPE_1                                         5002U                           /* Unit: ppm/C° */
#define CELL_SE_SLOPE_4                                         0U                              /* Unit: ppm/C° */
#define CELL_SE_SLOPE_3                                         4000U                           /* Unit: ppm/C° */
#define CELL_SE_SLOPE_2                                         4000U                           /* Unit: ppm/C° */
#define CELL_SE_SLOPE_1                                         2501U                           /* Unit: ppm/C° */
#define CELL_TBP34                                              25U                             /* Unit: ppm/C° */
#define CELL_TBP23                                              5U                              /* Unit: ppm/C° */
#define CELL_TBP12                                              0U                              /* Unit: ppm/C° */

/**
 * \brief Parameter EEPROM configuration values
 * 
 */
#define DS277XG_CONTROL_REG_VALUE                                0x0C       /* Set undervoltage treshold to 2.60V */
#define DS277XG_ACCUMULATION_BIAS_REG_VALUE                      0x00
#define DS277XG_AGING_CAPACITY_REG_VALUE_MSB                     ((uint8_t)(((uint16_t)(MAX_BATTERY_CHARGE * DS277XG_RSENSE_MOHMS) >> 8) / DS277XG_ACCUMULATED_CURRENT_REG_RESOLUTION))
#define DS277XG_AGING_CAPACITY_REG_VALUE_LSB                     ((uint8_t)((uint16_t)((MAX_BATTERY_CHARGE * DS277XG_RSENSE_MOHMS) / DS277XG_ACCUMULATED_CURRENT_REG_RESOLUTION)))
#define DS277XG_CHARGE_VOLTAGE_REG_VALUE                         ((uint8_t)(CELL_FULLY_CHARGED_VOLTAGE / DS277XG_CHARGE_VOLTAGE_REG_RESOLUTION))
#define DS277XG_MINIMUM_CHARGE_CURRENT_REG_VALUE                 ((uint8_t)((CELL_MINIMUM_CHARGE_CURRENT * DS277XG_RSENSE_MOHMS) / DS277XG_MINIMUM_CHARGE_CURRENT_REG_RESOLUTION))
#define DS277XG_ACTIVE_EMPTY_VOLTAGE_REG_VALUE                   ((uint8_t)(CELL_ACTIVE_EMPTY_VOLTAGE / DS277XG_ACTIVE_EMPTY_VOLTAGE_REG_RESOLUTION))
#define DS277XG_ACTIVE_EMPTY_CURRENT_REG_VALUE                   ((uint8_t)(CELL_ACTIVE_EMPTY_CURRENT*DS277XG_RSENSE_MOHMS / DS277XG_ACTIVE_EMPTY_CURRENT_REG_RESOLUTION))
#define DS277XG_ACTIVE_EMPTY_40_REG_VALUE                        ((uint8_t)(CELL_ACTIVE_EMPTY_40_CAPACITY / DS277XG_ACTIVE_EMPTY_40_REG_RESOLUTION))
#define DS277XG_SENSE_RESISTOR_PRIME_REG_VALUE                   ((uint8_t)(DS277XG_RSENSE_CONDUCTANCE))
#define DS277XG_FULL_40_MSB_REG_VALUE                            ((uint8_t)((uint16_t)((CELL_FULL_40_CAPACITY >> 8) / DS277XG_FULL_40_REG_RESOLUTION)))
#define DS277XG_FULL_40_LSB_REG_VALUE                            ((uint8_t)((uint16_t)(CELL_FULL_40_CAPACITY / DS277XG_FULL_40_REG_RESOLUTION)))
#define DS277XG_FULL_SEGMENTE_4_SLOPE_REG_VALUE                  ((uint8_t)(CELL_FULL_SLOPE_4 / DS277XG_SEGMENT_SLOPE_REG_RESOLUTION))
#define DS277XG_FULL_SEGMENTE_3_SLOPE_REG_VALUE                  ((uint8_t)(CELL_FULL_SLOPE_3 / DS277XG_SEGMENT_SLOPE_REG_RESOLUTION))
#define DS277XG_FULL_SEGMENTE_2_SLOPE_REG_VALUE                  ((uint8_t)(CELL_FULL_SLOPE_2 / DS277XG_SEGMENT_SLOPE_REG_RESOLUTION))
#define DS277XG_FULL_SEGMENTE_1_SLOPE_REG_VALUE                  ((uint8_t)(CELL_FULL_SLOPE_1 / DS277XG_SEGMENT_SLOPE_REG_RESOLUTION))
#define DS277XG_AE_SEGMENTE_4_SLOPE_REG_VALUE                    ((uint8_t)(CELL_AE_SLOPE_4 / DS277XG_SEGMENT_SLOPE_REG_RESOLUTION))
#define DS277XG_AE_SEGMENTE_3_SLOPE_REG_VALUE                    ((uint8_t)(CELL_AE_SLOPE_3 / DS277XG_SEGMENT_SLOPE_REG_RESOLUTION))
#define DS277XG_AE_SEGMENTE_2_SLOPE_REG_VALUE                    ((uint8_t)(CELL_AE_SLOPE_2 / DS277XG_SEGMENT_SLOPE_REG_RESOLUTION))
#define DS277XG_AE_SEGMENTE_1_SLOPE_REG_VALUE                    ((uint8_t)(CELL_AE_SLOPE_1 / DS277XG_SEGMENT_SLOPE_REG_RESOLUTION))
#define DS277XG_SE_SEGMENTE_4_SLOPE_REG_VALUE                    ((uint8_t)(CELL_SE_SLOPE_4 / DS277XG_SEGMENT_SLOPE_REG_RESOLUTION))
#define DS277XG_SE_SEGMENTE_3_SLOPE_REG_VALUE                    ((uint8_t)(CELL_SE_SLOPE_3 / DS277XG_SEGMENT_SLOPE_REG_RESOLUTION))
#define DS277XG_SE_SEGMENTE_2_SLOPE_REG_VALUE                    ((uint8_t)(CELL_SE_SLOPE_2 / DS277XG_SEGMENT_SLOPE_REG_RESOLUTION))
#define DS277XG_SE_SEGMENTE_1_SLOPE_REG_VALUE                    ((uint8_t)(CELL_SE_SLOPE_1 / DS277XG_SEGMENT_SLOPE_REG_RESOLUTION))
#define DS277XG_SENSE_RESISTOR_GAIN_REG_VALUE_MSB                0x64       /* Factory Value */
#define DS277XG_SENSE_RESISTOR_GAIN_REG_VALUE_LSB                0x1B       /* Factory Value */
#define DS277XG_SENSE_RESISTOR_TEMPERATURE_COEFFICIENT_REG_VALUE 0x00
#define DS277XG_CURRENT_OFFSET_BIAS_REG_VALUE                    0x00
#define DS277XG_TBP34_REG_VALUE                                  (CELL_TBP34)
#define DS277XG_TBP23_REG_VALUE                                  (CELL_TBP23)
#define DS277XG_TBP12_REG_VALUE                                  (CELL_TBP12)
#define DS277XG_PROTECTOR_THRESHOLD_REG_VALUE                    0x60       /* Set overvoltage threshold to 4.248V*/
#define DS277XG_TWO_WIRE_SLAVE_ADDRESS_REG_VALUE                 (DS2777G_DEFAULT_SLAVE_ADDRESS << 1)

#define DS277XG_PARAMETER_EEPROM_ADDRESS                         0x60
#define DS277XG_PARAMETER_EEPROM_SIZE                            33

/**
 * \brief DS277XG Commands
 */
#define DS2777G_DEFAULT_SLAVE_ADDRESS                           0b1011001
#define DS2775G_SKIP_ADDRESS                                    0xCC        //Address that access any onewire device (used when there's only one device at the onewire bus)
#define DS2775G_WRITE_DATA                                      0x6C        //Command to write a data in the DS2775G+ memory
#define DS2775G_READ_DATA                                       0x69        //Command to read a data from DS2775G+ memory
#define DS2775G_COPY_DATA                                       0x48        //Command to copy data of the DS2775G+ EEPROM shadow RAM to EEPROM cells
/**
 * \brief Memory map.
 */
// Read/Write registers.
#define DS277XG_PROTECTION_REGISTER                             0x00
#define DS277XG_STATUS_REGISTER                                 0x01
#define DS277XG_ACCUMULATED_CURRENT_MSB                         0x10
#define DS277XG_ACCUMULATED_CURRENT_LSB                         0x11
#define DS277XG_AGE_SCALAR_REGISTER                             0x14
#define DS277XG_SPECIAL_FEATURE_REGISTER                        0x15
#define DS277XG_CYCLE_COUNTER_REGISTER                          0x1E
#define DS277XG_EEPROM_REGISTER                                 0x1F
// 0x20 to 0x2F <-- User EEPROM Register, Lockable, Block 0.
#define DS277XG_USER_EEPROM_BYTE_1                              0x20
#define DS277XG_USER_EEPROM_BYTE_2                              0x21
#define DS277XG_USER_EEPROM_BYTE_3                              0x22
#define DS277XG_USER_EEPROM_BYTE_4                              0x23
#define DS277XG_USER_EEPROM_BYTE_5                              0x24
#define DS277XG_USER_EEPROM_BYTE_6                              0x25
#define DS277XG_USER_EEPROM_BYTE_7                              0x26
#define DS277XG_USER_EEPROM_BYTE_8                              0x27
#define DS277XG_USER_EEPROM_BYTE_9                              0x28
#define DS277XG_USER_EEPROM_BYTE_10                             0x29
#define DS277XG_USER_EEPROM_BYTE_11                             0x2A
#define DS277XG_USER_EEPROM_BYTE_12                             0x2B
#define DS277XG_USER_EEPROM_BYTE_13                             0x2C
#define DS277XG_USER_EEPROM_BYTE_14                             0x2D
#define DS277XG_USER_EEPROM_BYTE_15                             0x2E
#define DS277XG_USER_EEPROM_BYTE_16                             0x2F
// 0x60 to 0x80 <-- Parameter EEPROM Register, Lockable, Block 1.
#define DS277XG_CONTROL_REGISTER                                0x60
#define DS277XG_ACCUMULATION_BIAS_REGISTER                      0x61
#define DS277XG_AGING_CAPACITY_REGISTER_MSB                     0x62
#define DS277XG_AGING_CAPACITY_REGISTER_LSB                     0x63
#define DS277XG_CHARGE_VOLTAGE_REGISTER                         0x64
#define DS277XG_MINIMUM_CHARGE_CURRENT_REGISTER                 0x65
#define DS277XG_ACTIVE_EMPTY_VOLTAGE_REGISTER                   0x66
#define DS277XG_ACTIVE_EMPTY_CURRENT_REGISTER                   0x67
#define DS277XG_ACTIVE_EMPTY_40_REGISTER                        0x68
#define DS277XG_SENSE_RESISTOR_PRIME_REGISTER                   0x69
#define DS277XG_FULL_40_MSB_REGISTER                            0x6A
#define DS277XG_FULL_40_LSB_REGISTER                            0x6B
#define DS277XG_FULL_SEGMENTE_4_SLOPE_REGISTER                  0x6C
#define DS277XG_FULL_SEGMENTE_3_SLOPE_REGISTER                  0x6D
#define DS277XG_FULL_SEGMENTE_2_SLOPE_REGISTER                  0x6E
#define DS277XG_FULL_SEGMENTE_1_SLOPE_REGISTER                  0x6F
#define DS277XG_AE_SEGMENTE_4_SLOPE_REGISTER                    0x70
#define DS277XG_AE_SEGMENTE_3_SLOPE_REGISTER                    0x71
#define DS277XG_AE_SEGMENTE_2_SLOPE_REGISTER                    0x72
#define DS277XG_AE_SEGMENTE_1_SLOPE_REGISTER                    0x73
#define DS277XG_SE_SEGMENTE_4_SLOPE_REGISTER                    0x74
#define DS277XG_SE_SEGMENTE_3_SLOPE_REGISTER                    0x75
#define DS277XG_SE_SEGMENTE_2_SLOPE_REGISTER                    0x76
#define DS277XG_SE_SEGMENTE_1_SLOPE_REGISTER                    0x77
#define DS277XG_SENSE_RESISTOR_GAIN_REGISTER_MSB                0x78
#define DS277XG_SENSE_RESISTOR_GAIN_REGISTER_LSB                0x79
#define DS277XG_SENSE_RESISTOR_TEMPERATURE_COEFFICIENT_REGISTER 0x7A
#define DS277XG_CURRENT_OFFSET_BIAS_REGISTER                    0x7B
#define DS277XG_TBP34_REGISTER                                  0x7C
#define DS277XG_TBP23_REGISTER                                  0x7D
#define DS277XG_TBP12_REGISTER                                  0x7E
#define DS277XG_PROTECTOR_THRESHOLD_REGISTER                    0x7F
#define DS277XG_TWO_WIRE_SLAVE_ADDRESS_REGISTER                 0x80
// Read registers.
#define DS277XG_RAAC_REGISTER_MSB                               0x02
#define DS277XG_RAAC_REGISTER_LSB                               0x03
#define DS277XG_RSAC_REGISTER_MSB                               0x04
#define DS277XG_RSAC_REGISTER_LSB                               0x05
#define DS277XG_RARC_REGISTER                                   0x06
#define DS277XG_RSRC_REGISTER                                   0x07
#define DS277XG_AVERAGE_CURRENT_REGISTER_MSB                    0x08
#define DS277XG_AVERAGE_CURRENT_REGISTER_LSB                    0x09
#define DS277XG_TEMPERATURE_REGISTER_MSB                        0x0A
#define DS277XG_TEMPERATURE_REGISTER_LSB                        0x0B
#define DS277XG_VOLTAGE_REGISTER_MSB_Vin1_Vss                   0x0C
#define DS277XG_VOLTAGE_REGISTER_LSB_Vin1_Vss                   0x0D
#define DS277XG_CURRENT_REGISTER_MSB                            0x0E
#define DS277XG_CURRENT_REGISTER_LSB                            0x0F
#define DS277XG_ACCUMULATED_CURRENT_LSB_MINUS_1                 0x12
#define DS277XG_ACCUMULATED_CURRENT_LSB_MINUS_2                 0x13
#define DS277XG_FULL_REGISTER_MSB                               0x16
#define DS277XG_FULL_REGISTER_LSB                               0x17
#define DS277XG_ACTIVE_EMPTY_REGISTER_MSB                       0x18
#define DS277XG_ACTIVE_EMPTY_REGISTER_LSB                       0x19
#define DS277XG_STANDBY_EMPTY_REGISTER_MSB                      0x1A
#define DS277XG_STANDBY_EMPTY_REGISTER_LSB                      0x1B
#define DS277XG_VOLTAGE_REGISTER_MSB_Vin2_Vin1                  0x1C
#define DS277XG_VOLTAGE_REGISTER_LSB_Vin2_Vin1                  0x1D
#define DS277XG_FACTORY_GAIN_RSGAIN_REGISTER_MSB                0xB0
#define DS277XG_FACTORY_GAIN_RSGAIN_REGISTER_LSB                0xB1
// Write registers.
#define DS277XG_TWO_WIRE_COMMAND_REGISTER                       0xFE

/**
 * \brief Function commands.
 */
#define DS277XG_COPY_DATA_USER_EEPROM                           0x42
#define DS277XG_COPY_DATA_PARAMETER_EEPROM                      0x44
#define DS277XG_RECALL_DATA_USER_EEPROM                         0xB2
#define DS277XG_RECALL_DATA_PARAMETER_EEPROM                    0xB4
#define DS277XG_LOCK_USER_EEPROM                                0x63
#define DS277XG_LOCK_PARAMETER_EEPROM                           0x66
#define DS277XG_READ_ROM_ID                                     0x39

/**
 * \brief Register specific bit mask.
 */
// Protection register.
#define DS277XG_CHARGE_CONTROL_FLAG                             (1 << 3)
#define DS277XG_DISCHARGE_CONTROL_FLAG                          (1 << 2)
#define DS277XG_CHARGE_ENABLE_BIT                               (1 << 1)
#define DS277XG_DISCHARGE_ENABLE_BIT                            (1 << 0)

typedef struct
{
#if defined(CONFIG_DRIVERS_DS277X_ONEWIRE_VERSION) && (CONFIG_DRIVERS_DS277X_ONEWIRE_VERSION == 1)
    onewire_port_t port;
#else
    i2c_port_t  port;
    i2c_slave_adr_t slave_adr;
#endif
} ds277Xg_config_t;

/**
 * \brief
 * 
 * \param[in] config DS277XG configuration parameters.
 * \return int The status/error code.
 */
int ds277Xg_init(ds277Xg_config_t *config);

/**
 * @brief Set battery configuration to initial state.
 * 
 * Run this function ONCE when a new battery is connected to reset
 * accumulated current and aging estimation to initial values.
 * 
 * @param config DS277XG configuration parameters.
 * @return int The status/error code.
 */
int ds277Xg_set_battery_to_initial_state(ds277Xg_config_t *config);

/**
 * \brief Set charge enable bit in protection register.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \return int The status/error code.
 */
int ds277Xg_enable_charge(ds277Xg_config_t *config);

/**
 * \brief Set discharge enable bit in protection register.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \return int The status/error code.
 */
int ds277Xg_enable_discharge(ds277Xg_config_t *config);

/**
 * \brief Reset charge enable bit in protection register.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \return int The status/error code.
 */
int ds277Xg_disable_charge(ds277Xg_config_t *config);

/**
 * \brief Reset discharge enable bit in protection register.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \return int The status/error code.
 */
int ds277Xg_disable_discharge(ds277Xg_config_t *config);

/**
 * \brief Get the raw voltage in two's complement form from the DS277XG.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \param[in,out] voltage_raw The raw voltage value.
 * \param[in] battery_select Must be either 1 or 2.
 * \return int The status/error code.
 */
int ds277Xg_read_voltage_raw(ds277Xg_config_t *config, int16_t *voltage_raw, uint8_t battery_select);

/**
 * \brief Convert from raw data to mV.
 * 
 * Resolution: 4.8828mV. Goes from -5000mV to 4995.1mV
 * Sign | 2^9 | 2^8 | 2^7 | 2^6 | 2^5 | 2^4 | 2^3 | 2^2 | 2^1 | 2^0 | X | X | X | X | X
 *                       MSB                      |                    LSB              
 * 
 * \param[in] raw The raw voltage value.
 * \return float Converted voltage in mV.
 */
int16_t ds277Xg_voltage_raw_to_mv(int16_t raw);

/**
 * \brief Get the voltage in mV from one of the batteries connected to the DS277XG.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \param[in,out] voltage_mv Voltage in mV.
 * \param[in] battery_select Must be either 1 or 2.
 * \return int The status/error code.
 */
int ds277Xg_read_voltage_mv(ds277Xg_config_t *config, int16_t *voltage_mv, uint8_t battery_select);

/**
 * \brief Get the raw temperature in two's complement form from the DS277XG.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \param[in,out] temp_raw The raw temperature value.
 * \return int The status/error code.
 */
int ds277Xg_read_temperature_raw(ds277Xg_config_t *config, int16_t *temp_raw);

/**
 * \brief Convert from raw data to kelvin.
 * 
 * Resolution: 0.125 degrees kelvin.
 * Sign | 2^9 | 2^8 | 2^7 | 2^6 | 2^5 | 2^4 | 2^3 | 2^2 | 2^1 | 2^0 | X | X | X | X | X
 *                       MSB                      |                    LSB              
 * 
 * \param[in] raw The raw temperature value.
 * \return uint16_t Converted temperature in kelvin.
 */
uint16_t ds277Xg_temperature_raw_to_kelvin(int16_t raw);

/**
 * \brief Get the temperature in kelvin from the DS277XG.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \param[in,out] temp_kelvin Temperature in kelvin.
 * \return int The status/error code.
 */
int ds277Xg_read_temperature_kelvin(ds277Xg_config_t *config, uint16_t *temp_kelvin);

/**
 * \brief Get the raw current in two's complement form from the DS277XG.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \param[in,out] current_raw The raw current value.
 * \param[in] read_average Whether to read the last current raw value [false] or a mean of the last eight values [true].
 * \return int The status/error code.
 */
int ds277Xg_read_current_raw(ds277Xg_config_t *config, int16_t *current_raw, bool read_average);

/**
 * \brief Convert from raw data to mA.
 * 
 * Resolution: 1.5625uV/R_sense. Goes from -51.2mV/R_sense to 51.2mV/R_sense.
 * 
 * \param[in] raw The raw current value.
 * \return int16_t Converted current in mA.
 */
int16_t ds277Xg_current_raw_to_ma(int16_t raw);

/**
 * \brief Get the current in mA from the DS277XG (instantaneous or average from last eight).
 * 
 * \param[in] config DS277XG configuration parameters.
 * \param[in,out] current_ma Current in mA.
 * \param[in] read_average Whether to read the last current raw value [false] or a mean of the last eight values [true].
 * \return int The status/error code.
 */
int ds277Xg_read_current_ma(ds277Xg_config_t *config, int16_t *current_ma, bool read_average);

/**
 * \brief Write the raw accumulated current in two's complement form to the DS277XG.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \param[in] acc_current_raw The raw accumulated current value to write.
 * \return int The status/error code.
 */
int ds277Xg_write_accumulated_current_raw(ds277Xg_config_t *config, uint16_t acc_current_raw);

/**
 * \brief Convert from mAh data to raw.
 * 
 * \param[in] mah The mAh accumulated current value.
 * \return uint16_t Converted raw accumulated current value.
 */
uint16_t ds277Xg_accumulated_current_mah_to_raw(uint16_t mah);

/**
 * \brief Write the accumulated current in mAh to the DS277XG.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \param[in] acc_current_mah Accumulated current in mAh.
 * \return int The status/error code.
 */
int ds277Xg_write_accumulated_current_mah(ds277Xg_config_t *config, uint16_t acc_current_mah);

/**
 * \brief Write the battery max charge value in mAh to the DS277XG.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \return int The status/error code.
 */
int ds277Xg_write_accumulated_current_max_value(ds277Xg_config_t *config);

/**
 * \brief Get the raw accumulated current in two's complement form from the DS277XG.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \param[in,out] acc_current_raw The raw accumulated current value.
 * \return int The status/error code.
 */
int ds277Xg_read_accumulated_current_raw(ds277Xg_config_t *config, uint16_t *acc_current_raw);

/**
 * \brief Convert from raw data to mAh.
 * 
 * Resolution: 6.25uVh/R_sense. Goes from 0 to 409.6mVh/R_sense.
 * 
 * \param[in] raw The raw accumulated current value.
 * \return uint16_t Converted accumulated current in mAh.
 */
uint16_t ds277Xg_accumulated_current_raw_to_mah(uint16_t raw);

/**
 * \brief Get the accumulated current in mAh from the DS277XG.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \param[in,out] acc_current_mah Accumulated current in mAh.
 * \return int The status/error code.
 */
int ds277Xg_read_accumulated_current_mah(ds277Xg_config_t *config, uint16_t *acc_current_mah);

/**
 * \brief Write number of cycles to the DS277XG.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \param[in] cycles The number of cycles to write. Goes from 0 to 510.
 * \return int The status/error code.
 */
int ds277Xg_write_cycle_counter(ds277Xg_config_t *config, uint16_t cycles);

/**
 * \brief Read number of cycles from the DS277XG.
 * 
 * \param[in] config DS277XG configuration parameters.
 * \param[in,out] cycles The number of cycles to write. Goes from 0 to 510.
 * \return int The status/error code.
 */
int ds277Xg_read_cycle_counter(ds277Xg_config_t *config, uint16_t *cycles);

/**
 * \brief Write-Data Protocol
 * 
 * Start SAddr MAddr Data0 Data1 ... DataN Stop
 * 
 * \param[in] config DS277XG configuration parameters.
 * \param[in] data Data to write. First byte must be target register address.
 * \param[in] len Length of the data to write, including target register.
 * \return int The status/error code.
 */
int ds277Xg_write_data(ds277Xg_config_t *config, uint8_t *data, uint16_t len);

/**
 * \brief 
 * 
 * Start SAddr MAddr StartRepeat SAddr Data0 Data1 ... DataN Stop
 * 
 * \param[in] config DS277XG configuration parameters.
 * \param[in] target_reg Target register to read from.
 * \param[in,out] data Pointer to store data read.
 * \param[in] len Length of the data do read.
 * \return int The status/error code.
 */
int ds277Xg_read_data(ds277Xg_config_t *config, uint8_t target_reg, uint8_t *data, uint16_t len);

#endif /* DS277XG_H_ */

/** \} End of ds277Xg group */
