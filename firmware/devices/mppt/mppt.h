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
 * \author João Cláudio <joaoclaudiobarcellos@gmail.com>
 * 
 * \version 0.1.3
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

#define MPPT_MODULE_NAME        "MPPT"

/**
 * \brief constants.
 */
#define K 1

/**
 * \brief power measurements.
 */
typedef struct
{
    uint16_t previous_power;
    uint16_t current_power;
}power_measurement_t;

power_measurement_t power_measurement;

/**
 * \brief last operation.
 */
typedef struct
{
    uint8_t previous_duty_cycle;
    uint8_t current_duty_cycle;
}duty_cycle_measurement_t;

duty_cycle_measurement_t duty_cycle_measurement;

/**
 * \brief Initialization routine of the MPPT.
 *
 * \return The status/error code.
 */
int mppt_init();

int get_power(uint16_t current, uint16_t voltage);
void increase_duty_cycle(pwm_config_t config, pwm_port_t port);
void decrease_duty_cycle(pwm_config_t config, pwm_port_t port);
int update_duty_cycle(pwm_port_t port, pwm_config_t config);


#endif /* MPPT_H_ */

/** \} End of mppt group */
