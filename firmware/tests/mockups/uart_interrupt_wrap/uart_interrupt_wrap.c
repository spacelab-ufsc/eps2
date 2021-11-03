/*
 * uart_interrupt_wrap.c
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
 * \brief UART Interrupt wrap implementation.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2021/09/15
 *
 * \defgroup uart_interrupt_wrap UART INTERRUPT Wrap
 * \ingroup tests
 * \{
 */

#include "uart_interrupt_wrap.h"

uint8_t uart_rx_buffer[UART_RX_BUFFER_MAX_SIZE];
uint8_t uart_received_data_size = 0;
uint8_t uart_buffer_index = 0;

int __wrap_uart_interrupt_init(uart_interrupt_port_t port, uart_interrupt_config_t config) {
    return 0;
}
int __wrap_uart_interrupt_enable(uart_interrupt_port_t port) {
    return 0;
}

int __wrap_uart_interrupt_disable(uart_interrupt_port_t port) {
    return 0;
}

int __wrap_uart_interrupt_write(uart_interrupt_port_t port, uint8_t *data, uint16_t len) {
    return 0;
}


/** \} End of uart_interrupt_wrap group */
