/*
 * wdt_wrap.h
 *
 * Copyright (C) 2022, SpaceLab.
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
 * \brief WDT driver wrap definition.
 *
 * \author Lucas Zacchi <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2022/07/12
 *
 * \defgroup wdt_wrap WDT Wrap
 * \ingroup tests
 * \{
 */

#ifndef WDT_WRAP_H_
#define WDT_WRAP_H_

#include <stdint.h>

#include <drivers/wdt/wdt.h>

int __wrap_wdt_init(wdt_config_t config);

void __wrap_wdt_reset(void);

#endif /* WDT_WRAP_H_ */

/** \} End of wdt group */
