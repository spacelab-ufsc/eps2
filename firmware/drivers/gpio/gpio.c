/*
 * gpio.c
 * 
 * Copyright (C) 2019, SpaceLab.
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
 * \brief GPIO driver implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.1.0
 * 
 * \date 2020/10/24
 * 
 * \addtogroup gpio
 * \{
 */

#include <hal/gpio.h>

#include <config/config.h>
#include <system/sys_log/sys_log.h>

#include "gpio.h"

int gpio_init(gpio_pin_t pin, gpio_config_t config)
{
    uint8_t msp_port;
    uint16_t msp_pin;

    switch(pin)
    {
        case GPIO_PIN_0:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_1:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_2:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_3:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_4:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_5:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_6:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_7:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_8:    msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_9:    msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_10:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_11:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_12:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_13:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_14:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_15:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_16:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_17:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_18:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_19:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_20:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_21:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_22:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_23:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_24:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_25:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_26:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_27:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_28:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_29:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_30:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_31:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_32:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_33:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_34:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_35:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_36:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_37:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_38:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_39:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_40:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_41:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_42:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_43:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_44:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_45:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_46:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_47:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_48:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_49:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_50:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_51:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_52:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_53:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_54:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_55:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_56:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_57:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_58:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_59:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_60:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_61:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_62:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_63:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_64:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_65:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_66:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_67:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_68:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_69:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN7;    break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, GPIO_MODULE_NAME, "Invalid pin to initialize!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;  /* Invalid GPIO pin */
    }

    if (config.mode == GPIO_MODE_OUTPUT)
    {
        GPIO_setAsOutputPin(msp_port, msp_pin);
    }
    else if (config.mode == GPIO_MODE_INPUT)
    {
        GPIO_setAsInputPin(msp_port, msp_pin);
    }
    else
    {
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_ERROR, GPIO_MODULE_NAME, "Invalid mode during the initialization!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return -1;  /* Invalid mode */
    }

    return 0;
}

int gpio_set_state(gpio_pin_t pin, bool level)
{
    uint8_t msp_port;
    uint16_t msp_pin;

    switch(pin)
    {
        case GPIO_PIN_0:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_1:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_2:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_3:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_4:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_5:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_6:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_7:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_8:    msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_9:    msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_10:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_11:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_12:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_13:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_14:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_15:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_16:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_17:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_18:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_19:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_20:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_21:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_22:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_23:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_24:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_25:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_26:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_27:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_28:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_29:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_30:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_31:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_32:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_33:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_34:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_35:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_36:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_37:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_38:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_39:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_40:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_41:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_42:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_43:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_44:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_45:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_46:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_47:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_48:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_49:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_50:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_51:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_52:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_53:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_54:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_55:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_56:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_57:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_58:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_59:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_60:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_61:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_62:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_63:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_64:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_65:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_66:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_67:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_68:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_69:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN7;    break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, GPIO_MODULE_NAME, "Invalid pin to set!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;  /* Invalid GPIO pin */
    }

    if (level)
    {
        GPIO_setOutputHighOnPin(msp_port, msp_pin);
    }
    else
    {
        GPIO_setOutputLowOnPin(msp_port, msp_pin);
    }

    return 0;
}

int gpio_get_state(gpio_pin_t pin)
{
    uint8_t msp_port;
    uint16_t msp_pin;

    switch(pin)
    {
        case GPIO_PIN_0:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_1:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_2:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_3:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_4:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_5:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_6:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_7:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_8:    msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_9:    msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_10:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_11:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_12:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_13:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_14:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_15:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_16:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_17:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_18:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_19:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_20:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_21:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_22:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_23:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_24:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_25:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_26:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_27:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_28:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_29:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_30:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_31:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_32:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_33:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_34:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_35:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_36:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_37:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_38:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_39:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_40:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_41:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_42:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_43:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_44:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_45:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_46:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_47:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_48:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_49:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_50:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_51:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_52:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_53:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_54:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_55:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_56:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_57:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_58:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_59:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_60:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_61:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_62:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_63:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_64:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_65:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_66:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_67:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_68:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_69:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN7;    break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, GPIO_MODULE_NAME, "Invalid pin to read!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;  /* Invalid GPIO pin */
    }

    if (GPIO_getInputPinValue(msp_port, msp_pin) == GPIO_INPUT_PIN_HIGH)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int gpio_toggle(gpio_pin_t pin)
{
    uint8_t msp_port;
    uint16_t msp_pin;

    switch(pin)
    {
        case GPIO_PIN_0:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_1:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_2:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_3:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_4:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_5:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_6:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_7:    msp_port = GPIO_PORT_P1;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_8:    msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_9:    msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_10:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_11:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_12:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_13:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_14:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_15:   msp_port = GPIO_PORT_P2;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_16:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_17:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_18:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_19:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_20:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_21:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_22:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_23:   msp_port = GPIO_PORT_P3;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_24:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_25:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_26:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_27:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_28:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_29:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_30:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_31:   msp_port = GPIO_PORT_P4;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_32:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_33:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_34:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_35:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_36:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_37:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_38:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_39:   msp_port = GPIO_PORT_P5;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_40:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_41:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_42:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_43:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_44:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_45:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_46:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_47:   msp_port = GPIO_PORT_P6;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_48:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_49:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_50:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_51:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_52:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_53:   msp_port = GPIO_PORT_P7;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_54:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_55:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_56:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_57:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_58:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_59:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_60:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_61:   msp_port = GPIO_PORT_P8;    msp_pin = GPIO_PIN7;    break;
        case GPIO_PIN_62:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN0;    break;
        case GPIO_PIN_63:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN1;    break;
        case GPIO_PIN_64:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN2;    break;
        case GPIO_PIN_65:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN3;    break;
        case GPIO_PIN_66:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN4;    break;
        case GPIO_PIN_67:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN5;    break;
        case GPIO_PIN_68:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN6;    break;
        case GPIO_PIN_69:   msp_port = GPIO_PORT_P9;    msp_pin = GPIO_PIN7;    break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, GPIO_MODULE_NAME, "Invalid pin to toggle!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;  /* Invalid GPIO pin */
    }

    GPIO_toggleOutputOnPin(msp_port, msp_pin);

    return 0;
}

/** \} End of gpio group */
