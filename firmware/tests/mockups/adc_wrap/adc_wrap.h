/*
 * adc_wrap.h
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
 * \brief ADC driver wrap definition.
 *
 * \author Lucas Zacchi de Medeiros <lzacchi@pm.me>
 *
 * \version 0.1.0
 *
 * \date 2021/08/23
 *
 * \defgroup adc_wrap ADC Wrap
 * \ingroup tests
 * \{
 */

#ifndef ADC_WRAP_H
#define ADC_WRAP_H

#include <stdint.h>

#include <drivers/adc/adc.h>

int __wrap_adc_init(adc_port_t port, adc_config_t config);

int __wrap_adc_read(adc_port_t port, uint16_t *val);

void __wrap_adc_delay_ms(uint16_t ms);

float __wrap_adc_temp_get_mref(void);

float __wrap_adc_temp_get_nref(void);

bool __wrap_adc_mutex_create(void);

bool __wrap_adc_mutex_take(void);

bool __wrap_adc_mutex_give(void);

#endif /* ADC_WRAP_H_ */

/** \} End of adc_wrap group */
