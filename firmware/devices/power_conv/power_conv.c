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
 * \authors Yan Castro de Azeredo <yan.ufsceel@gmail.com> and Vinicius Pimenta Bernardo <viniciuspibi@gmail.com>
 *
 * \version 0.1.12
 *
 * \date 2021/06/10
 *
 * \addtogroup power_conv
 * \{
 */

#include <drivers/gpio/gpio.h>

#include <system/sys_log/sys_log.h>

#include "power_conv.h"

int power_conv_init()
{
	if (tps54x0_init((tps54x0_config_t){.enable_pin = EN_3V3_OBDH_PIN}) != 0
	|| tps54x0_init((tps54x0_config_t){.enable_pin = EN_PAYLOAD_PIN}) != 0)
	{
		return -1;
	}
	return 0;
}

int enable_obdh_power()
{
	return tps54x0_enable((tps54x0_config_t){.enable_pin = EN_3V3_OBDH_PIN});
}

int disable_obdh_power()
{
	return tps54x0_disable((tps54x0_config_t){.enable_pin = EN_3V3_OBDH_PIN});
}

int enable_payload_power()
{
	return tps54x0_enable((tps54x0_config_t){.enable_pin = EN_PAYLOAD_PIN});
}

int disable_payload_power()
{
	return tps54x0_disable((tps54x0_config_t){.enable_pin = EN_PAYLOAD_PIN});
}

/** \} End of power_conv group */