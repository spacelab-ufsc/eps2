/*
 * config.h
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
 * \brief Configuration parameters definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com> and Augusto Cezar Boldori Vassoler <augustovassoler@gmail.com>
 * 
 * \version 0.1.15
 * 
 * \date 2021/01/25
 * 
 * \defgroup config Configuration
 * \{
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/* Tasks */
#define CONFIG_TASK_STARTUP_ENABLED                     1
#define CONFIG_TASK_WATCHDOG_RESET_ENABLED              1
#define CONFIG_TASK_HEARTBEAT_ENABLED					1
#define CONFIG_TASK_SYSTEM_RESET_ENABLED				0
#define CONFIG_TASK_READ_SENSORS_ENABLED                0

#define CONFIG_DRIVERS_DEBUG_ENABLED                    0

#define MAX_BATTERY_CHARGE                          2450 //[mAh]
#define BAT_MONITOR_CHARGE_VALUE                    (uint16_t)(MAX_BATTERY_CHARGE/0.625) //0.625 is a conversion factor for the  battery monitor
#define RESET_BATTERY_ACCUMULATED_CURRENT           0

#endif /* CONFIG_H_ */

/** \} End of config group */
