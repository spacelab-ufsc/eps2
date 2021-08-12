/*
 * pwm.h
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
 * \brief PWM driver definition.
 * 
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * \author Andre M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * 
 * \version 0.2.10
 * 
 * \date 2021/05/15
 * 
 * \defgroup pwm PWM
 * \ingroup drivers
 * \{
 */

#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>
#include <stdbool.h>

#define PWM_MODULE_NAME             "PWM"

#define FORCE_SCOURCE_STOP		    true
#define KEEP_SCOURCE_RUNNING	    false

#define CONVERT_CLK_PERIOD_TO_US    32

/**
 * \brief PWM source.
 */
typedef enum
{
    TIMER_A0=0,       	/**< PWM source from timer A0 (reserved for system tick). */
    TIMER_A1,         	/**< PWM source from timer A1. */
    TIMER_A2,         	/**< PWM source from timer A2. */
    TIMER_B0			/**< PWM source from timer B0. */
} pwm_sources_e;

/**
 * \brief PWM ports.
 */
typedef enum
{
    PWM_PORT_0=0,       /**< PWM output port 0. */
    PWM_PORT_1,         /**< PWM output port 1. */
    PWM_PORT_2,         /**< PWM output port 2. */
    PWM_PORT_3,         /**< PWM output port 3. */
    PWM_PORT_4,         /**< PWM output port 4. */
    PWM_PORT_5,         /**< PWM output port 4. */
    PWM_PORT_6         	/**< PWM output port 4. */
} pwm_ports_e;

/**
 * \brief PWM source type.
 */
typedef uint8_t pwm_source_t;

/**
 * \brief PWM port type.
 */
typedef uint8_t pwm_port_t;

/**
 * \brief PWM configuration parameters.
 */
typedef struct
{
	uint32_t period_us;		/**< Period in microseconds. */
	uint8_t duty_cycle; 	/**< Duty cycle in % (from 0 to 100). */
} pwm_config_t;

/**
 * \brief PWM initialization.
 *
 * \param[in] source is the PWM timer source. It can be:
 * \parblock
 *      -\b TIMER_A0
 *      -\b TIMER_A1
 *      -\b TIMER_A2
 *      -\b TIMER_B0
 *      .
 * \endparblock
 *
 * \param[in] port is the output PWM port. It can be:
 * \parblock
 *      -\b PWM_PORT_0
 *      -\b PWM_PORT_1
 *      -\b PWM_PORT_2
 *      -\b PWM_PORT_3
 *      -\b PWM_PORT_4
 *      -\b PWM_PORT_5
 *      -\b PWM_PORT_6
 *      .
 * \endparblock
 *
 * \param[in] config is a structure for the PWM period and duty cycle parameters.
 *
 * \return The status/error code.
 */
int pwm_init(pwm_source_t source, pwm_port_t port, pwm_config_t config);

/**
 * \brief Updates PWM parameters.
 *
 * \param[in] source is the PWM timer source. It can be:
 * \parblock
 *      -\b TIMER_A0
 *      -\b TIMER_A1
 *      -\b TIMER_A2
 *      -\b TIMER_B0
 *      .
 * \endparblock
 *
 * \param[in] port is the output PWM port. It can be:
 * \parblock
 *      -\b PWM_PORT_0
 *      -\b PWM_PORT_1
 *      -\b PWM_PORT_2
 *      -\b PWM_PORT_3
 *      -\b PWM_PORT_4
 *      -\b PWM_PORT_5
 *      -\b PWM_PORT_6
 *      .
 * \endparblock
 *
 * \param[in] config is a structure for the PWM period and duty cycle parameters.
 *
 * \return The status/error code.
 */
int pwm_update(pwm_source_t source, pwm_port_t port, pwm_config_t config);

/**
 * \brief Stops a PWM port and keep its output at a low state.
 *
 * \param[in] source is the PWM timer source. It can be:
 * \parblock
 *      -\b TIMER_A0
 *      -\b TIMER_A1
 *      -\b TIMER_A2
 *      -\b TIMER_B0
 *      .
 * \endparblock
 *
 * \param[in] port is the output PWM port. It can be:
 * \parblock
 *      -\b PWM_PORT_0
 *      -\b PWM_PORT_1
 *      -\b PWM_PORT_2
 *      -\b PWM_PORT_3
 *      -\b PWM_PORT_4
 *      -\b PWM_PORT_5
 *      -\b PWM_PORT_6
 *      .
 * \endparblock
 *
 * \param[in] config is a structure for the PWM period and duty cycle parameters.
 *
 * \return The status/error code.
 */
int pwm_stop(pwm_source_t source, pwm_port_t port, pwm_config_t config);

/**
 * \brief Disbales the PWM source (a clean disable can be achieved with pwm_stop() to set used ports to zero).
 *
 * \param[in] source is the PWM timer source. It can be:
 * \parblock
 *      -\b TIMER_A0
 *      -\b TIMER_A1
 *      -\b TIMER_A2
 *      -\b TIMER_B0
 *      .
 * \endparblock
 *
 * \return The status/error code.
 */
int pwm_disable(pwm_source_t source);

#endif /* PWM_H_ */

/** \} End of pwm group */
