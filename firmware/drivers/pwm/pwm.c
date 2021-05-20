/*
 * pwm.c
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
 * \brief PWM driver implementation.
 * 
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * 
 * \version 0.1.4
 * 
 * \date 2021/05/19
 * 
 * \addtogroup pwm
 * \{
 */

#include <hal/timer_a.h>
#include <hal/timer_b.h>

#include <config/config.h>
#include <system/sys_log/sys_log.h>

int pwm_init()
{
    return -1;
}

int pwm_increase()
{
    return -1;
}

int pwm_decrease()
{
    return -1;
}

int pwm_disable()
{
    return -1;
}

/** \} End of pwm group */
