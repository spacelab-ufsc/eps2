/*
 * temp_sensors.c
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
 * \brief Temperature sensor device implementation.
 * 
 * \author Yan Castro de Azeredo <yan.ufsceel@gmail.com>
 * 
 * \version 0.1.1
 * 
 * \date 2021/03/18
 * 
 * \addtogroup temp_sensor
 * \{
 */

#include <drivers/ads1248/ads1248.h>

#include <system/sys_log/sys_log.h>

#include "temp_sensor.h"

temp_sensor_t *config;

int temp_sensor_init(temp_sensor_t *config)
{
	sys_log_print_event_from_module(SYS_LOG_INFO, TEMP_SENSOR_MODULE_NAME, "Initializing the temperature sensor device...");
    sys_log_new_line();
	
	config->spi_port = TEMP_SENSOR_SPI_PORT;
	config->spi_config.mode = TEMP_SENSOR_SPI_MODE;
	config->spi_config.speed_hz = TEMP_SENSOR_SPI_SPEED_HZ;
	config->start_pin = TEMP_SENSOR_START_PIN;
	config->spi_cs = TEMP_SENSOR_SPI_CS;
	config->reset_pin = TEMP_SENSOR_RESET_PIN;
	
   if(ads1248_init(config) != 0)
   {
		sys_log_print_event_from_module(SYS_LOG_ERROR, TEMP_SENSOR_MODULE_NAME, "Error initializing the temperature sensor device!");
		sys_log_new_line();

		return -1;
   }

	return 0;
}

int temp_sensor_suspend(temp_sensor_t *config, temp_sensor_power_down_t mode)
{
	sys_log_print_event_from_module(SYS_LOG_INFO, TEMP_SENSOR_MODULE_NAME, "Powering down the temperature sensor device...");
    sys_log_new_line();
	
	if(ads1248_set_powerdown_mode(config, mode) != 0)
   {
		sys_log_print_event_from_module(SYS_LOG_ERROR, TEMP_SENSOR_MODULE_NAME, "Error suspending the temperature sensor device!");
		sys_log_new_line();

		return -1;
   }

	return 0;
}

int temp_sensor_read_c(temp_sensor_t *config, uint8_t positive_channel, float *temp)
{
	uint8_t *raw_volt = 0;

    if (ads1248_write_cmd(config, ADS1248_CMD_RDATA, raw_volt, positive_channel) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, TEMP_SENSOR_MODULE_NAME, "Error reading the raw temperature value!");
        sys_log_new_line();

        return -1;
    }

    *temp = temp_sensor_convert_raw_to_c(raw_volt);

    return 0;
}

float temp_sensor_convert_raw_to_c(uint8_t *raw_volt)
{	
	float hex_volt = raw_volt [0] | (raw_volt [1] << 8) | (raw_volt [2] << 16) | (raw_volt [3] << 32);   
	
	float volt = (hex_volt*TEMP_SENSOR_REF_VOLTAGE)/ADS1248_RANGE;

	return (((volt/0.0001) - 100)/0.384);
}
