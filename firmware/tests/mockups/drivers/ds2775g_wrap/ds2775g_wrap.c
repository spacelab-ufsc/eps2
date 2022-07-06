/*
 * ds2775g_wrap.c
 *
 * Copyright The EPS 2.0 Contributors.
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
 * \brief ds2775g driver wrap implementation.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.2.43
 *
 * \date 2022/06/15
 *
 * \defgroup ds2775g_wrap DS2775G Wrap
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include "ds2775g_wrap.h"

int __wrap_ds2775g_init(ds2775g_config_t *config)
{
    if (config != NULL)
    {
        config->protection_reg[0] = skip_address;
        config->protection_reg[1] = write_data;
        config->protection_reg[2] = protection_register;
        config->protection_reg[3] = 0x03;
        config->protector_threshold_reg[0] = skip_address;
        config->protector_threshold_reg[1] = write_data;
        config->protector_threshold_reg[2] = protector_threshold_register;
        config->protector_threshold_reg[3] = 0x61;
        config->status_reg[0] = skip_address;
        config->status_reg[1] = write_data;
        config->status_reg[2] = status_register;
        config->status_reg[3] = 0x0;
        config->control_reg[0] = skip_address;
        config->control_reg[1] = write_data;
        config->control_reg[2] = control_register;
        config->control_reg[3] = 0x0C;
        config->overcurrent_thresholds_reg[0] = skip_address;
        config->overcurrent_thresholds_reg[1] = write_data;
        config->overcurrent_thresholds_reg[2] = overcurrent_thresholds_register;
        config->overcurrent_thresholds_reg[3] = 0x24;
        config->current_gain_LSB_reg[0] = skip_address;
        config->current_gain_LSB_reg[1] = write_data;
        config->current_gain_LSB_reg[2] = current_gain_LSB_register;
        config->current_gain_LSB_reg[3] = 0x00;

        config->onewire_port = GPIO_PIN_69;
    }
    return mock_type(int);
}

int __wrap_ds2775g_write_data(onewire_port_t port, uint8_t *data, uint16_t len)
{
    check_expected(port);
    check_expected(len);

    return mock_type(int);
}

int __wrap_ds2775g_read_register(onewire_port_t port, uint8_t register_address, uint8_t *data_read)
{
    // data read out
    check_expected(port);
    check_expected(register_address);

    return mock_type(int);
}

int __wrap_write_accumulated_current_max_value(onewire_port_t port)
{
    check_expected(port);
    return mock_type(int);
}

/** \} End of ds2775g_wrap group */
