/*
 * adc.c
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
 * \brief ADC driver implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.20
 * 
 * \date 2021/06/11
 * 
 * \addtogroup adc
 * \{
 */

#include <stdbool.h>

#include <hal/gpio.h>
#include <hal/adc10_a.h>
#include <hal/adc12_a.h>
#include <hal/ref.h>
#include <hal/tlv.h>

#include <config/config.h>
#include <system/sys_log/sys_log.h>

#include "adc.h"

bool adc_is_ready = false;

float adc_mref = 0;
float adc_nref = 0;

uint8_t adc_cal_bytes;
struct s_TLV_ADC_Cal_Data *adc_cal_data;

int adc_init(adc_port_t port, adc_config_t config)
{
    if (adc_is_ready)
    {
    #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
        sys_log_print_event_from_module(SYS_LOG_WARNING, ADC_MODULE_NAME, "ADC driver already initialized!");
        sys_log_new_line();
    #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
        return 0;
    }

    /* Set port 6 and 7 pins as inputs */
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P7, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);

    ADC12_A_init(ADC12_A_BASE, ADC12_A_SAMPLEHOLDSOURCE_SC, ADC12_A_CLOCKSOURCE_ADC12OSC, ADC12_A_CLOCKDIVIDER_1);

    ADC12_A_enable(ADC12_A_BASE);

    ADC12_A_setupSamplingTimer(ADC12_A_BASE, ADC12_A_CYCLEHOLD_768_CYCLES, ADC12_A_CYCLEHOLD_4_CYCLES, ADC12_A_MULTIPLESAMPLESDISABLE);

    ADC12_A_configureMemoryParam param = {0};

    /* Temperature sensor */
    param.memoryBufferControlIndex          = ADC12_A_MEMORY_0;
    param.inputSourceSelect                 = ADC12_A_INPUT_TEMPSENSOR;
    param.positiveRefVoltageSourceSelect    = ADC12_A_VREFPOS_INT;
    param.negativeRefVoltageSourceSelect    = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence                     = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE, &param);

    /* Solar Panel -Y current sensor */
    param.memoryBufferControlIndex          = ADC12_A_MEMORY_1;
    param.inputSourceSelect                 = ADC12_A_INPUT_A0;
    param.positiveRefVoltageSourceSelect    = ADC12_A_VREFPOS_EXT;
    param.negativeRefVoltageSourceSelect    = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence                     = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE, &param);

    /* Solar Panel +X current sensor */
    param.memoryBufferControlIndex          = ADC12_A_MEMORY_2;
    param.inputSourceSelect                 = ADC12_A_INPUT_A1;
    param.positiveRefVoltageSourceSelect    = ADC12_A_VREFPOS_EXT;
    param.negativeRefVoltageSourceSelect    = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence                     = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE, &param);

    /* Solar Panel -X current sensor */
    param.memoryBufferControlIndex          = ADC12_A_MEMORY_3;
    param.inputSourceSelect                 = ADC12_A_INPUT_A2;
    param.positiveRefVoltageSourceSelect    = ADC12_A_VREFPOS_EXT;
    param.negativeRefVoltageSourceSelect    = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence                     = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE, &param);

    /* Solar Panel +Z current sensor */
    param.memoryBufferControlIndex          = ADC12_A_MEMORY_4;
    param.inputSourceSelect                 = ADC12_A_INPUT_A3;
    param.positiveRefVoltageSourceSelect    = ADC12_A_VREFPOS_EXT;
    param.negativeRefVoltageSourceSelect    = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence                     = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE, &param);

    /* Solar Panel -Z current sensor */
    param.memoryBufferControlIndex          = ADC12_A_MEMORY_5;
    param.inputSourceSelect                 = ADC12_A_INPUT_A4;
    param.positiveRefVoltageSourceSelect    = ADC12_A_VREFPOS_EXT;
    param.negativeRefVoltageSourceSelect    = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence                     = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE, &param);

    /* Solar Panel +Y current sensor */
    param.memoryBufferControlIndex          = ADC12_A_MEMORY_6;
    param.inputSourceSelect                 = ADC12_A_INPUT_A5;
    param.positiveRefVoltageSourceSelect    = ADC12_A_VREFPOS_EXT;
    param.negativeRefVoltageSourceSelect    = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence                     = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE, &param);

    /* TTC/EPS regulator current sensor */
    param.memoryBufferControlIndex          = ADC12_A_MEMORY_7;
    param.inputSourceSelect                 = ADC12_A_INPUT_A6;
    param.positiveRefVoltageSourceSelect    = ADC12_A_VREFPOS_EXT;
    param.negativeRefVoltageSourceSelect    = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence                     = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE, &param);

    /* Main bus voltage sensor */
    param.memoryBufferControlIndex          = ADC12_A_MEMORY_10;
    param.inputSourceSelect                 = ADC12_A_INPUT_A7;
    param.positiveRefVoltageSourceSelect    = ADC12_A_VREFPOS_EXT;
    param.negativeRefVoltageSourceSelect    = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence                     = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE, &param);

    /* Solar Panel -Y/+X voltage sensor */
    param.memoryBufferControlIndex          = ADC12_A_MEMORY_12;
    param.inputSourceSelect                 = ADC12_A_INPUT_A12;
    param.positiveRefVoltageSourceSelect    = ADC12_A_VREFPOS_EXT;
    param.negativeRefVoltageSourceSelect    = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence                     = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE, &param);

    /* Solar Panel -X/+Z voltage sensor */
    param.memoryBufferControlIndex          = ADC12_A_MEMORY_13;
    param.inputSourceSelect                 = ADC12_A_INPUT_A13;
    param.positiveRefVoltageSourceSelect    = ADC12_A_VREFPOS_EXT;
    param.negativeRefVoltageSourceSelect    = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence                     = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE, &param);

    /* Solar Panel -Z/+Y voltage sensor */
    param.memoryBufferControlIndex          = ADC12_A_MEMORY_14;
    param.inputSourceSelect                 = ADC12_A_INPUT_A14;
    param.positiveRefVoltageSourceSelect    = ADC12_A_VREFPOS_EXT;
    param.negativeRefVoltageSourceSelect    = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence                     = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE, &param);

    /* Solar Panel total voltage sensor */
    param.memoryBufferControlIndex          = ADC12_A_MEMORY_15;
    param.inputSourceSelect                 = ADC12_A_INPUT_A15;
    param.positiveRefVoltageSourceSelect    = ADC12_A_VREFPOS_EXT;
    param.negativeRefVoltageSourceSelect    = ADC12_A_VREFNEG_AVSS;
    param.endOfSequence                     = ADC12_A_NOTENDOFSEQUENCE;
    ADC12_A_configureMemory(ADC12_A_BASE, &param);

    ADC12_A_clearInterrupt(ADC12_A_BASE, ADC12_A_IFG0 | ADC12_A_IFG1 | ADC12_A_IFG2 | ADC12_A_IFG3 | ADC12_A_IFG4 | ADC12_A_IFG5 | ADC12_A_IFG6 | ADC12_A_IFG7 | ADC12_A_IFG10 | ADC12_A_IFG12 | ADC12_A_IFG13 | ADC12_A_IFG14 | ADC12_A_IFG15);

    uint8_t i = 0;
    for(i=0; i<ADC_TIMOUT_MS; i++)
    {
        if (REF_ACTIVE != Ref_isRefGenBusy(REF_BASE))
        {
            break;
        }

        adc_delay_ms(1);
    }

    Ref_setReferenceVoltage(REF_BASE, REF_VREF1_5V);

    Ref_enableReferenceVoltage(REF_BASE);

    Ref_enableTempSensor(REF_BASE);

    adc_delay_ms(10);

    /* Temperature sensor calibration data */
    TLV_getInfo(TLV_TAG_ADCCAL, 0, &adc_cal_bytes, (uint16_t **)&adc_cal_data);

    adc_mref = ((float)(adc_cal_data->adc_ref15_85_temp - adc_cal_data->adc_ref15_30_temp)) / (85 - 30);
    adc_nref = adc_cal_data->adc_ref15_85_temp - adc_mref * 85;

    /* Mutex initialization */
    adc_mutex_create();

    adc_is_ready = true;

    return 0;
}

int adc_read(adc_port_t port, uint16_t *val)
{
    uint8_t i = 0;
    for(i=0; i<ADC_TIMOUT_MS; i++)
    {
        if (!ADC12_A_isBusy(ADC12_A_BASE))
        {
            break;
        }

        adc_delay_ms(1);
    }

    *val = 0xffff;
    // Symbol 'UINT16_MAX' could not be resolved - Semantic Error
    // *val = UINT16_MAX;

    if (i == ADC_TIMOUT_MS)
    {
        return -1;  /* Timeout reached */
    }

    switch(port)
    {
        case ADC_PORT_0:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_0, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG0))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_0);

            break;
        case ADC_PORT_1:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_1, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG1))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_1);

            break;
        case ADC_PORT_2:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_2, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG2))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_2);

            break;
        case ADC_PORT_3:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_3, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG3))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_3);

            break;
        case ADC_PORT_4:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_4, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG4))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_4);

            break;
        case ADC_PORT_5:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_5, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG5))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_5);

            break;
        case ADC_PORT_6:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_6, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG6))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_6);

            break;
        case ADC_PORT_7:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_7, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG7))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_7);

            break;
        case ADC_PORT_8:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_8, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG8))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_8);

            break;
        case ADC_PORT_9:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_9, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG9))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_9);

            break;
        case ADC_PORT_10:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_10, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG10))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_10);

            break;
        case ADC_PORT_11:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_11, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG11))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_11);

            break;
        case ADC_PORT_12:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_12, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG12))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_12);

            break;
        case ADC_PORT_13:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_13, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG13))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_13);

            break;
        case ADC_PORT_14:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_14, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG14))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_14);

            break;
        case ADC_PORT_15:
            ADC12_A_startConversion(ADC12_A_BASE, ADC12_A_MEMORY_15, ADC12_A_SINGLECHANNEL);

            for(i=0; i<ADC_TIMOUT_MS; i++)
            {
                if (ADC12_A_getInterruptStatus(ADC12_A_BASE, ADC12_A_IFG15))
                {
                    break;
                }

                adc_delay_ms(1);
            }

            if (i == ADC_TIMOUT_MS)
            {
                return -1;  /* Timeout reached */
            }

            *val = ADC12_A_getResults(ADC12_A_BASE, ADC12_A_MEMORY_15);

            break;
        default:
        #if CONFIG_DRIVERS_DEBUG_ENABLED == 1
            sys_log_print_event_from_module(SYS_LOG_ERROR, ADC_MODULE_NAME, "Error reading the ADC port ");
            sys_log_print_uint(port);
            sys_log_print_msg("! Invalid port!");
            sys_log_new_line();
        #endif /* CONFIG_DRIVERS_DEBUG_ENABLED */
            return -1;
    }

    ADC12_A_clearInterrupt(ADC12_A_BASE, ADC12_A_IFG0 | ADC12_A_IFG1 | ADC12_A_IFG2 | ADC12_A_IFG3 | ADC12_A_IFG4 | ADC12_A_IFG5 | ADC12_A_IFG6 | ADC12_A_IFG7 | ADC12_A_IFG10 | ADC12_A_IFG12 | ADC12_A_IFG13 | ADC12_A_IFG14 | ADC12_A_IFG15);

    return 0;
}

float adc_temp_get_mref(void)
{
    return adc_mref;
}

float adc_temp_get_nref(void)
{
    return adc_nref;
}

/** \} End of adc group */
