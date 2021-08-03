/*
 * mppt.h
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
 * \brief MPPT device definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * \author Jo�o Cl�udio <joaoclaudiobarcellos@gmail.com>
 * \author Andr� M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * 
 * \version 0.2.9
 * 
 * \date 2021/02/10
 * 
 * \defgroup mppt MPPT
 * \ingroup devices
 * \{
 */

#ifndef MPPT_H_
#define MPPT_H_

#include <stdint.h>
#include <stdbool.h>

#include <drivers/pwm/pwm.h>
#include <devices/voltage_sensor/voltage_sensor.h>
#include <devices/current_sensor/current_sensor.h>

#define MPPT_MODULE_NAME        "MPPT"

/**
 * \brief MPPT algorithm constants.
 */
#define MPPT_DUTY_CYCLE_STEP    1       /**< PWM duty cycle step in % for the MPPT algorithm. */
#define MPPT_DUTY_CYCLE_INIT    50      /**< PWM initial duty cycle in % for the MPPT algorithm. */
#define MPPT_PERIOD_INIT        4       /**< PWM period (1/f) in us for the MPPT algorithm. */

/**
 * \brief MPPT control loop channels.
 */
#define MPPT_CONTROL_LOOP_CH_SOURCE   TIMER_B0        /**< MPPT control loop channels source. */
#define MPPT_CONTROL_LOOP_CH_0        PWM_PORT_1      /**< MPPT control loop channel 0. */
#define MPPT_CONTROL_LOOP_CH_1        PWM_PORT_2      /**< MPPT control loop channel 1. */
#define MPPT_CONTROL_LOOP_CH_2        PWM_PORT_3      /**< MPPT control loop channel 2. */
#define MPPT_VOLTAGE_SENSOR_CH_0      ADC_PORT_12     /**< MPPT voltage sensor for channel 0. */
#define MPPT_VOLTAGE_SENSOR_CH_1      ADC_PORT_13     /**< MPPT voltage sensor for channel 1. */
#define MPPT_VOLTAGE_SENSOR_CH_2      ADC_PORT_14     /**< MPPT voltage sensor for channel 2. */
#define MPPT_CURRENT_SENSOR_0_CH_0    ADC_PORT_0      /**< MPPT current sensor 0 for channel 0. */
#define MPPT_CURRENT_SENSOR_1_CH_0    ADC_PORT_1      /**< MPPT current sensor 1 for channel 0. */
#define MPPT_CURRENT_SENSOR_0_CH_1    ADC_PORT_2      /**< MPPT current sensor 0 for channel 1. */
#define MPPT_CURRENT_SENSOR_1_CH_1    ADC_PORT_3      /**< MPPT current sensor 1 for channel 1. */
#define MPPT_CURRENT_SENSOR_0_CH_2    ADC_PORT_4      /**< MPPT current sensor 0 for channel 2. */
#define MPPT_CURRENT_SENSOR_1_CH_2    ADC_PORT_5      /**< MPPT current sensor 1 for channel 2. */

/**
 * \brief MPPT control loop channel type.
 */
typedef pwm_port_t mppt_channel_t;

/**
 * \brief MPPT control loop configuration type.
 */
typedef pwm_config_t mppt_config_t;

/**
 * \brief power measurements.
 */
typedef struct
{
    uint16_t previous_power;
    uint16_t power;
} power_measurement_t;

/**
 * \brief last operation.
 */
typedef struct
{
    uint8_t previous_duty_cycle;
    uint8_t duty_cycle;
} duty_cycle_measurement_t;

/**
 * \brief last operation.
 */
typedef struct
{
    uint8_t previous_duty_cycle_ch_0;
    uint8_t previous_duty_cycle_ch_1;
    uint8_t previous_duty_cycle_ch_2;
    uint16_t previous_power_ch_0;
    uint16_t previous_power_ch_1;
    uint16_t previous_power_ch_2;
} previous_values_t;

/**
 * \brief Initialization routine of the MPPT.
 *
 * \return The status/error code.
 */
int mppt_init();

/**
 * \brief Function to implement the perturb and observe maximum power point tracking algorithm.
 *
 * \param[in] channel is the control loop channel to be used.
 *
 * \return The status/error code.
 */
int mppt_algorithm(mppt_channel_t channel);


#endif /* MPPT_H_ */

/** \} End of mppt group */
