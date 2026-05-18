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
 * \author Andre M. P. de Mattos <andre.mattos@spacelab.ufsc.br>
 * 
 * \version 0.2.10
 * 
 * \date 2021/05/19
 * 
 * \addtogroup pwm
 * \{
 */

#include "pwm.h"

#include <hal/timer_a.h>
#include <hal/timer_b.h>
#include <hal/gpio.h>

#include <config/config.h>
#include <system/sys_log/sys_log.h>

int pwm_init(pwm_source_t source, pwm_port_t port, pwm_config_t config)
{
	switch(source) 
	{
		case TIMER_A0:
			#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
	            sys_log_print_event_from_module(SYS_LOG_ERROR, PWM_MODULE_NAME, "Invalid PWM source, timer reserved for system tick!");
	            sys_log_new_line();
        	#endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
			return -1;
		
		case TIMER_A1:
			Timer_A_outputPWMParam timer_a1_config;

			/* Base PWM configuration */
			timer_a1_config.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;						/* SMCLK ~ 32MHz */
			timer_a1_config.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;				/* SMCLK ~ 32MHz => base period of 0.0313us */
			timer_a1_config.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
			
			/* User PWM configuration */
			timer_a1_config.timerPeriod = config.period_us * CONVERT_CLK_PERIOD_TO_US;		/* Period in us due to previous parameters */ 
			timer_a1_config.dutyCycle = (config.duty_cycle / 100.0) * (config.period_us * CONVERT_CLK_PERIOD_TO_US);	/* Convertion from % to number of cycles in high */

			switch(port) 
			{
				case PWM_PORT_0:
					timer_a1_config.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0; 
					GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN1);
					break;
				case PWM_PORT_1:
					timer_a1_config.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
					GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN2);
					break;
				case PWM_PORT_2:
					timer_a1_config.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2; 
					GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN3);
					break;
				default:
					#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
		            	sys_log_print_event_from_module(SYS_LOG_ERROR, PWM_MODULE_NAME, "Invalid PWM port!");
		            	sys_log_new_line();
	        		#endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
		            return -1;
			}

			Timer_A_outputPWM(TIMER_A1_BASE, &timer_a1_config);
			return 0;
		
		case TIMER_A2:
			Timer_A_outputPWMParam timer_a2_config;

			/* Base PWM configuration */
			timer_a2_config.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;						/* SMCLK ~ 32MHz */
			timer_a2_config.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;				/* SMCLK ~ 32MHz => base period of 0.0313us */
			timer_a2_config.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;
			
			/* User PWM configuration */
			timer_a2_config.timerPeriod = config.period_us * CONVERT_CLK_PERIOD_TO_US;		/* Period in us due to previous parameters */ 
			timer_a2_config.dutyCycle = (config.duty_cycle / 100.0) * (config.period_us * CONVERT_CLK_PERIOD_TO_US);	/* Convertion from % to number of cycles in high */

			switch(port) 
			{
				case PWM_PORT_0:
					timer_a2_config.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_0; 
					GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN5);
					break;
				case PWM_PORT_1:
					timer_a2_config.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
					GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN6);
					break;
				case PWM_PORT_2:
					timer_a2_config.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2; 
					GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN7);
					break;
				default:
					#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
		            	sys_log_print_event_from_module(SYS_LOG_ERROR, PWM_MODULE_NAME, "Invalid PWM port!");
		            	sys_log_new_line();
	        		#endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
		            return -1;
			}

			Timer_A_outputPWM(TIMER_A2_BASE, &timer_a2_config);
			return 0;
		
		case TIMER_B0:
		    Timer_B_outputPWMParam timer_b0_config;

			/* Base PWM configuration */
			timer_b0_config.clockSource = TIMER_B_CLOCKSOURCE_SMCLK;						/* SMCLK ~ 32MHz */
			timer_b0_config.clockSourceDivider = TIMER_B_CLOCKSOURCE_DIVIDER_1;				/* SMCLK ~ 32MHz => base period of 0.0313us */
			timer_b0_config.compareOutputMode = TIMER_B_OUTPUTMODE_RESET_SET;
			
			/* User PWM configuration */
			timer_b0_config.timerPeriod = config.period_us * CONVERT_CLK_PERIOD_TO_US;		/* Period in us due to previous parameters */
			timer_b0_config.dutyCycle = (config.duty_cycle / 100.0) * (config.period_us * CONVERT_CLK_PERIOD_TO_US);	/* Convertion from % to number of cycles in high */

			switch(port) 
			{
				case PWM_PORT_0:
					timer_b0_config.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_0; 
					GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P4, GPIO_PIN0);
					break;
				case PWM_PORT_1:
					timer_b0_config.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_1;
					GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P4, GPIO_PIN1);
					break;
				case PWM_PORT_2:
					timer_b0_config.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_2; 
					GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P4, GPIO_PIN2);
					break;
				case PWM_PORT_3:
					timer_b0_config.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_3; 
					GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P4, GPIO_PIN3);
					break;
				case PWM_PORT_4:
					timer_b0_config.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_4; 
					GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P4, GPIO_PIN4);
					break;
				case PWM_PORT_5:
					timer_b0_config.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_5; 
					GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P4, GPIO_PIN5);
					break;
				case PWM_PORT_6:
					timer_b0_config.compareRegister = TIMER_B_CAPTURECOMPARE_REGISTER_6; 
					GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P4, GPIO_PIN6);
					break;
				default:
					#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
		            	sys_log_print_event_from_module(SYS_LOG_ERROR, PWM_MODULE_NAME, "Invalid PWM port!");
		            	sys_log_new_line();
	        		#endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
		            return -1;
			}

			Timer_B_outputPWM(TIMER_B0_BASE, &timer_b0_config);
			return 0;
		
		default:
			#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
	            sys_log_print_event_from_module(SYS_LOG_ERROR, PWM_MODULE_NAME, "Invalid PWM source!");
	            sys_log_new_line();
        	#endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
			return -1;
	}
}

int pwm_update(pwm_source_t source, pwm_port_t port, pwm_config_t config)
{
    return pwm_init(source, port, config);
}

int pwm_stop(pwm_source_t source, pwm_port_t port, pwm_config_t config)
{
	switch(source) 
	{
		case TIMER_A0:
			#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
	            sys_log_print_event_from_module(SYS_LOG_ERROR, PWM_MODULE_NAME, "Invalid PWM source, timer reserved for system tick!");
	            sys_log_new_line();
        	#endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
			return -1;
		case TIMER_A1:
			/* Keeps source running and hold low only the selected port */
			config.duty_cycle = 0;
			pwm_update(TIMER_A1, port, config);

			switch(port) 
			{
				case PWM_PORT_0:
					GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN1);
					GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN1);
					break;
				case PWM_PORT_1:
					GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN2);
					GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN2);
					break;
				case PWM_PORT_2:
					GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN3);
					GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN3);
					break;
				default:
					#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
		            	sys_log_print_event_from_module(SYS_LOG_ERROR, PWM_MODULE_NAME, "Invalid PWM port!");
		            	sys_log_new_line();
	        		#endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
		            return -1;
			}
			return 0;
		case TIMER_A2:
			/* Keeps source running and hold low only the selected port */
			config.duty_cycle = 0;
			pwm_update(TIMER_A2, port, config);

			switch(port) 
			{
				case PWM_PORT_0:
					GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN5);
					GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN5);
					break;
				case PWM_PORT_1:
					GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN6);
					GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN6);
					break;
				case PWM_PORT_2:
					GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN7);
					GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN7);
					break;
				default:
					#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
		            	sys_log_print_event_from_module(SYS_LOG_ERROR, PWM_MODULE_NAME, "Invalid PWM port!");
		            	sys_log_new_line();
	        		#endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
		            return -1;
			}
			return 0;
		case TIMER_B0:
			/* Keeps source running and hold low only the selected port */
			config.duty_cycle = 0;
			pwm_update(TIMER_B0, port, config);

			switch(port) 
			{
				case PWM_PORT_0:
					GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
					GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
					break;
				case PWM_PORT_1:
					GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN1);
					GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
					break;
				case PWM_PORT_2:
					GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);
					GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
					break;
				case PWM_PORT_3:
					GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN3);
					GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN3);
					break;
				case PWM_PORT_4:
					GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);
					GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
					break;
				case PWM_PORT_5:
					GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);
					GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
					break;
				case PWM_PORT_6:
					GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN6);
					GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN6);
					break;
				default:
					#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
		            	sys_log_print_event_from_module(SYS_LOG_ERROR, PWM_MODULE_NAME, "Invalid PWM port!");
		            	sys_log_new_line();
	        		#endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
		            return -1;
			}
			return 0;
		default:
			#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
	            sys_log_print_event_from_module(SYS_LOG_ERROR, PWM_MODULE_NAME, "Invalid PWM source!");
	            sys_log_new_line();
        	#endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
			return -1;
	}
}

int pwm_disable(pwm_source_t source)
{
    switch(source) 
	{
		case TIMER_A0:
			#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
	            sys_log_print_event_from_module(SYS_LOG_ERROR, PWM_MODULE_NAME, "Invalid PWM source, timer reserved for system tick!");
	            sys_log_new_line();
        	#endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
			return -1;
		case TIMER_A1:
			/* Stops the timer source */	
			Timer_A_stop(TIMER_A1_BASE);
			return 0;
		case TIMER_A2:
			/* Stops the timer source */	
			Timer_A_stop(TIMER_A2_BASE);
			return 0;
		case TIMER_B0:
			/* Stops the timer source */	
			Timer_B_stop(TIMER_B0_BASE);
			return 0;
		default:
			#if CONFIG_DRIVERS_DEBUG_ENABLED == 1
	            sys_log_print_event_from_module(SYS_LOG_ERROR, PWM_MODULE_NAME, "Invalid PWM source!");
	            sys_log_new_line();
        	#endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
			return -1;
	}
}

/** \} End of pwm group */
