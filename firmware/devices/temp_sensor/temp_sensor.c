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
 * \version 0.2.26
 * 
 * \date 2021/06/11
 * 
 * \addtogroup temp_sensor
 * \{
 */

#include <system/sys_log/sys_log.h>

#include <drivers/adc/adc.h>

#include "temp_sensor.h"

temp_sensor_t config;

int temp_sensor_init(void)
{
    sys_log_print_event_from_module(SYS_LOG_INFO, TEMP_SENSOR_MODULE_NAME, "Initializing internal MCU temperature sensor...");
    sys_log_new_line();

    adc_config_t temp_sense_adc_config = {0};

    if (adc_init(TEMP_SENSOR_ADC_PORT, temp_sense_adc_config) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, TEMP_SENSOR_MODULE_NAME, "Error internal MCU temperature sensor!");
        sys_log_new_line();

        return -1;
    }

    int16_t temp = 0;
    if (temp_mcu_read_c(&temp) != 0)
    {
         sys_log_print_event_from_module(SYS_LOG_ERROR, TEMP_SENSOR_MODULE_NAME, "Error reading the internal MCU temperature value!");
         sys_log_new_line();

         return -1;
     }

    sys_log_print_event_from_module(SYS_LOG_INFO, TEMP_SENSOR_MODULE_NAME, "Current MCU temperature: ");
    sys_log_print_int(temp);
    sys_log_print_msg(" oC");
    sys_log_new_line();

    sys_log_print_event_from_module(SYS_LOG_INFO, TEMP_SENSOR_MODULE_NAME, "Initializing ADS1248 device...");
    sys_log_new_line();

	config.spi_port = TEMP_SENSOR_SPI_PORT;
	config.spi_config.mode = TEMP_SENSOR_SPI_MODE;
	config.spi_config.speed_hz = TEMP_SENSOR_SPI_SPEED_HZ;
	config.start_pin = TEMP_SENSOR_START_PIN;
	config.spi_cs = TEMP_SENSOR_SPI_CS;
	config.reset_pin = TEMP_SENSOR_RESET_PIN;
	
   if(ads1248_init(&config) != 0)
   {
		sys_log_print_event_from_module(SYS_LOG_ERROR, TEMP_SENSOR_MODULE_NAME, "Error initializing ADS1248 device!");
		sys_log_new_line();

		return -1;
   }

/** TO DO: implement log for rtd measurements during initialization */

	return 0;
}

int temp_sensor_suspend(temp_sensor_t *config, temp_sensor_power_down_t mode)
{
	sys_log_print_event_from_module(SYS_LOG_INFO, TEMP_SENSOR_MODULE_NAME, "Powering down ADS1248 device...");
    sys_log_new_line();
	
	if(ads1248_set_powerdown_mode(config, mode) != 0)
   {
		sys_log_print_event_from_module(SYS_LOG_ERROR, TEMP_SENSOR_MODULE_NAME, "Error suspending the ADS1248 device!");
		sys_log_new_line();

		return -1;
   }

	return 0;
}

int temp_mcu_read_raw(uint16_t *val)
{
    int err = 0;
    
    adc_mutex_take();
    err = adc_read(TEMP_SENSOR_ADC_PORT, val);
    adc_mutex_give();

    return err;
}

int16_t temp_mcu_raw_to_c(uint16_t raw)
{
    float buf = (raw - adc_temp_get_nref())/adc_temp_get_mref();

    if (buf < (-273))
    {
        buf = (-273);
    }

    return (int16_t)buf;
}


uint16_t temp_mcu_raw_to_k(uint16_t raw)
{
    int16_t temp_c = temp_mcu_raw_to_c(raw);

    return (uint16_t)(temp_c + 273);
}

int temp_mcu_read_c(int16_t *temp)
{
    uint16_t raw_temp = 0;

    if (temp_mcu_read_raw(&raw_temp) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, TEMP_SENSOR_MODULE_NAME, "Error reading the raw internal MCU temperature value!");
        sys_log_new_line();

        return -1;
    }

    *temp = temp_mcu_raw_to_c(raw_temp);

    return 0;
}

int temp_mcu_read_k(uint16_t *temp)
{
    uint16_t raw_temp = 0;

    if (temp_mcu_read_raw(&raw_temp) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, TEMP_SENSOR_MODULE_NAME, "Error reading the raw internal MCU temperature value!");
        sys_log_new_line();

        return -1;
    }

    *temp = temp_mcu_raw_to_k(raw_temp);

    return 0;
}

int temp_rtd_read_raw(uint8_t positive_channel, uint32_t *val)
{    
    return ads1248_write_cmd(&config, ADS1248_CMD_RDATA, (uint8_t *)val, positive_channel);
}

int16_t temp_rtd_raw_to_c(uint32_t raw)
{
    float buf = TEMP_SENSOR_CONV(raw);

    if (buf < (-273))
    {
        buf = (-273);
    }

    return (int16_t)buf;
}

uint16_t temp_rtd_raw_to_k(uint32_t raw)
{
    int16_t temp_c = temp_rtd_raw_to_c(raw);

    return (uint16_t)(temp_c + 273);
}

int temp_rtd_read_c(uint8_t channel, uint16_t *temp)
{
    uint32_t raw_temp = 0;

    if (temp_rtd_read_raw(channel, &raw_temp) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, TEMP_SENSOR_MODULE_NAME, "Error reading the raw RTD temperature value!");
        sys_log_new_line();

        return -1;
    }

    *temp = temp_rtd_raw_to_c(raw_temp);

    return 0;
}

int temp_rtd_read_k(uint8_t channel, uint16_t *temp)
{
    uint32_t raw_temp = 0;

    if (temp_rtd_read_raw(channel, &raw_temp) != 0)
    {
        sys_log_print_event_from_module(SYS_LOG_ERROR, TEMP_SENSOR_MODULE_NAME, "Error reading the raw RTD temperature value!");
        sys_log_new_line();

        return -1;
    }

    *temp = temp_rtd_raw_to_k(raw_temp);

    return 0;
}

/** \} End of temp_sensor group */

