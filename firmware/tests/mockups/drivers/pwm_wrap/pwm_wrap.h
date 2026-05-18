/*
 * pwm_wrap.h
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
 * \brief PWM driver wrap definition.
 *
 * \authors Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2022/05/09
 *
 * \defgroup pwm_wrap PWM Wrap
 * \ingroup tests
 * \{
 */

#ifndef PWM_WRAP_H
#define PWM_WRAP_H

#include <stdint.h>
#include <stdbool.h>

#include <drivers/pwm/pwm.h>

int __wrap_pwm_init(pwm_source_t source, pwm_port_t port, pwm_config_t config);

int __wrap_pwm_update(pwm_source_t source, pwm_port_t port, pwm_config_t config);

int __wrap_pwm_stop(pwm_source_t source, pwm_port_t port, pwm_config_t config);

int __wrap_pwm_disable(pwm_source_t source);

#endif /* ADC_WRAP_H_ */

/** \} End of pwm_wrap group */
