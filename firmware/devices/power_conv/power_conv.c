/*
 * power_conv.c
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
 * \brief Power converters device implementation.
 *
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 *
 * \version 0.1.11
 *
 * \date 2021/06/09
 *
 * \addtogroup power_conv
 * \{
 */

#include <drivers/gpio/gpio.h>

#include <system/sys_log/sys_log.h>

#include "power_conv.h"

int power_conv_init()
{
	return -1;
}

int enable_obdh_power()
{
	return -1;
}

int disable_obdh_power()
{
	return -1;
}

int enable_payload_power()
{
	return -1;
}

int disable_payload_power()
{
	return -1;
}

/** \} End of power_conv group */