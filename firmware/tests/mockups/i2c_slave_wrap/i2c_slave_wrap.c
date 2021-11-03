/*
 * i2c_slave_wrap.c
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
 * \brief i2c_slave driver wrap implementation.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2021/09/28
 *
 * \defgroup i2c_slave_wrap I2C SLAVE Wrap
 * \ingroup tests
 * \{
 */

#include <stdint.h>
#include <drivers/i2c_slave/i2c_slave.h>

uint8_t i2c_rx_buffer[I2C_RX_BUFFER_MAX_SIZE];
uint8_t i2c_received_data_size = 0;

int __wrap_i2c_slave_init(i2c_slave_port_t port) {
    return 0;
}

int __wrap_i2c_slave_set_mode(i2c_slave_port_t port, i2c_mode_t mode) {
    return 0;
}

int __wrap_i2c_slave_enable(i2c_slave_port_t port) {
    return 0;
}

int __wrap_i2c_slave_disable(i2c_slave_port_t port) {
    return 0;
}

int __wrap_i2c_slave_write(i2c_slave_port_t port, uint8_t *data, uint16_t len) {
    return 0;
}

/** \} End of i2c_slave_wrap group */
