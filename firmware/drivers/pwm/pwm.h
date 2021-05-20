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
 * 
 * \version 0.1.4
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

#define PWM_MODULE_NAME         "PWM"

/**
 * \brief PWM ports.
 */
typedef enum
{
    PWM_PORT_1=0,       /**< PWM port 0. */
    PWM_PORT_3,         /**< PWM port 1. */
    PWM_PORT_4,         /**< PWM port 4. */
    PWM_PORT_8,         /**< PWM port 8. */
} pwm_ports_e;

/**
 * \brief PWM port type.
 */
typedef uint8_t pwm_port_t;

/**
 * \brief PWM mode type.
 */
typedef uint8_t pwm_mode_t;

/**
 * \brief PWM configuration parameters.
 */
typedef struct
{
uint16_t clock_source;
uint16_t clock_source_divider;
uint16_t period_ms;
uint16_t compare_reg;
uint16_t pwm_mode;
uint16_t duty_cycle;
} pwm_config_t;

/**
 * \brief PWM initialization.
 */
int pwm_init();

/**
 * \brief PWM duty cycle increase.
 */
int pwm_increase();

/**
 * \brief PWM duty cycle decrease.
 */
int pwm_decrease();

/**
 * \brief Disbales PWM.
 */
int pwm_disable();

#endif /* PWM_H_ */

/** \} End of pwm group */
