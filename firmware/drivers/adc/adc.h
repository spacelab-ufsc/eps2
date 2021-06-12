/*
 * adc.h
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
 * \brief ADC driver definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.12
 * 
 * \date 2021/06/11
 * 
 * \defgroup adc ADC
 * \ingroup drivers
 * \{
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

#define ADC_MODULE_NAME     "ADC"

#define ADC_VREF_V          (2.5)       /**< ADC reference voltage in Volts. */
#define ADC_VREF_MV         (2500UL)    /**< ADC reference voltage in millivolts. */
#define ADC_RANGE           (4095UL)    /**< ADC resolution (12-bits) */

#define ADC_TIMOUT_MS       100         /**< Timeout in milliseconds. */

/**
 * \brief ADC ports.
 */
typedef enum
{
    ADC_PORT_0=0,       /**< ADC port 0 (10-bits). */
    ADC_PORT_1,         /**< ADC port 1 (12-bits). */
    ADC_PORT_2,         /**< ADC port 2 (12-bits). */
    ADC_PORT_3,         /**< ADC port 3 (12-bits). */
    ADC_PORT_4,         /**< ADC port 4 (12-bits). */
    ADC_PORT_5,         /**< ADC port 5 (12-bits). */
    ADC_PORT_6,         /**< ADC port 6 (12-bits). */
    ADC_PORT_7,         /**< ADC port 7 (12-bits). */
    ADC_PORT_8,         /**< ADC port 8 (12-bits). */
    ADC_PORT_9,         /**< ADC port 9 (12-bits). */
    ADC_PORT_10,        /**< ADC port 10 (12-bits). */
    ADC_PORT_11,        /**< ADC port 11 (12-bits). */
    ADC_PORT_12,        /**< ADC port 12 (12-bits). */
    ADC_PORT_13,        /**< ADC port 13 (12-bits). */
    ADC_PORT_14,        /**< ADC port 14 (12-bits). */
    ADC_PORT_15         /**< ADC port 15 (12-bits). */
} adc_port_e;

/**
 * \brief ADC peripheral configuration parameters.
 */
typedef struct
{
    uint16_t sh_src;    /**< Sample-and-Hold signal source. */
    uint8_t clk_src;    /**< Clock source. */
    uint16_t clk_div;   /**< Clock source divider. */
} adc_config_t;

/**
 * \brief ADC port.
 */
typedef uint8_t adc_port_t;

/**
 * \brief ADC interface initialization.
 *
 * \param[in] port is the ADC port to initialize. It can be:
 * \parblock
 *      -\b ADC_PORT_0
 *      -\b ADC_PORT_1
 * \endparblock
 *
 * \param[in] config is the configuration of the ADC port.
 *
 * \return The status/error code.
 */
int adc_init(adc_port_t port, adc_config_t config);

/**
 * \brief Reads data from a given ADC port.
 *
 * \param[in] port is the ADC port to read. It can be:
 * \parblock
 *      -\b ADC_PORT_0
 *      -\b ADC_PORT_1
 *      -\b ADC_PORT_2
 *      -\b ADC_PORT_3
 *      -\b ADC_PORT_4
 *      -\b ADC_PORT_5
 *      -\b ADC_PORT_6
 *      -\b ADC_PORT_7
 *      -\b ADC_PORT_8
 *      -\b ADC_PORT_9
 *      -\b ADC_PORT_10
 *      -\b ADC_PORT_11
 *      -\b ADC_PORT_12
 *      -\b ADC_PORT_13
 *      -\b ADC_PORT_14
 *      -\b ADC_PORT_15
 *      .
 * \endparblock
 *
 * \param[in] val is a pointer to store the read value.
 *
 * \return The status/error code.
 */
int adc_read(adc_port_t port, uint16_t *val);

/**
 * \brief Milliseconds delay.
 *
 * \param[in] ms is the delay period in milliseconds.
 *
 * \return None.
 */
void adc_delay_ms(uint16_t ms);

/**
 * \brief Gets the mref value used to calibrate the sensor temperature.
 *
 * \return The mref value.
 */
float adc_temp_get_mref(void);

/**
 * \brief Gets the nref value used to calibrate the sensor temperature.
 *
 * \return The nref value.
 */
float adc_temp_get_nref(void);

#endif /* ADC_H_ */

/** \} End of adc group */
