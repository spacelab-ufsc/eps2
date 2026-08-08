/*
 * heater.h
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
 * \brief Heater device definition.
 *
 * \author Jo�o Cl�udio <joaoclaudiobarcellos@gmail.com>
 * \author Andr� M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 *
 * \version 0.2.11
 *
 * \date 2021/08/04
 *
 * \defgroup heater Heater
 * \ingroup devices
 * \{
 */

#ifndef HEATER_H_
#define HEATER_H_

#include <stdint.h>
#include <stdbool.h>

#include <devices/temp_sensor/temp_sensor.h>
#include <drivers/pwm/pwm.h>

#define HEATER_MODULE_NAME        "HEATER"

/**
 * \brief Heater PI controller constants.
 */
#define HEATER_PI_KP                            1.0f        /**< Kp: Proportional gain (provisional, not hardware-tuned). */
#define HEATER_PI_KI                            0.1f        /**< Ki: Integral gain (provisional, not hardware-tuned). */
#define HEATER_SAMPLE_TIME_S                    2.0f        /**< Controller sample time in seconds. */
#define HEATER_OUTPUT_MINIMUM                   0.0f        /**< Minimum actuator output limit. */
#define HEATER_OUTPUT_MAXIMUM                   100.0f      /**< Maximum actuator output limit. */

/**
 * \brief PWM constants.
 */
#define HEATER_PERIOD_INIT        1000      /**< PWM period (1/f) in us for the heater device. */
#define HEATER_DUTY_CYCLE_INIT    50      /**< PWM initial duty cycle in % for the heater device. */

/**
 * \brief Heater control loop channels.
 */
#define HEATER_CONTROL_LOOP_CH_SOURCE   TIMER_A1                /**< MPPT control loop channels source. */             
#define HEATER_CONTROL_LOOP_CH_0        0                       /**< MPPT control loop channel 0. */
#define HEATER_CONTROL_LOOP_CH_1        1                       /**< MPPT voltage sensor for channel 0. */
#define HEATER_ACTUATOR_CH_0            PWM_PORT_1
#define HEATER_ACTUATOR_CH_1            PWM_PORT_2
#define HEATER_SENSOR_CH_0              TEMP_SENSOR_RTD_CH_6
#define HEATER_SENSOR_CH_1              TEMP_SENSOR_RTD_CH_2
#define HEATER_SENSOR_BOARD             TEMP_SENSOR_RTD_CH_3

/**
 * \brief Heater control loop channel type.
 */
typedef pwm_port_t heater_channel_t;

/**
 * \brief Heater control loop configuration type.
 */
typedef pwm_config_t heater_config_t;

/**
 * \brief Temperature variable type.
 */
typedef uint16_t temperature_t;

/**
 * \brief Heater PI controller state.
 */
typedef struct
{
    float integral;     /**< Integral accumulator. */
} heater_pi_t;


/**
 * \brief Initialization routine of the heater device.
 *
 * \param[in] channel is the channel to be used.
 *
 * \return The status/error code.
 */
int heater_init(heater_channel_t channel);

/**
 * \brief Function to implement the heater PI controller algorithm.
 *
 * \param[in] channel is the heater channel to control.
 *
 * \param[in] setpoint is the desired temperature value.
 *
 * \param[in] measurement is the actual current temperature value.
 *
 * \return The control loop output value.
 */
float heater_algorithm(heater_channel_t channel, float setpoint, float measurement);

/**
 * \brief Gets the temperature sensor value in kelvin.
 *
 * \param[in] channel is the channel to be used.
 *
 * \param[in] temp is the read temperature value.
 *
 * \return The status/error code.
 */
int heater_get_sensor(heater_channel_t channel, temperature_t *temp);

/**
 * \brief Sets the PWM actuator duty cycle.
 *
 * \param[in] channel is the channel to be used.
 *
 * \param[in] pid_output is the value to set the duty cycle in %.
 *
 * \return The status/error code.
 */
int heater_set_actuator(heater_channel_t channel, float pid_output);


#endif /* HEATER_H_ */

/** \} End of heater group */
