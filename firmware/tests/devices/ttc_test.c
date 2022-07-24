/*
 * ttc_test.c
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
 * \brief Unit test of the TTC device.
 *
 * \author Lucas Zacchi de Medeiros <lucas.zacchi@spacelab.ufsc.br>
 *
 * \version 0.1.0
 *
 * \date 2022/06/15
 *
 * \defgroup ttc_unit_test TTC
 * \ingroup tests
 * \{
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <float.h>
#include <cmocka.h>

#include <devices/ttc/ttc.h>
#include <drivers/uart_interrupt/uart_interrupt.h>

static void ttc_init_test(void **state)
{
    expect_value(__wrap_uart_interrupt_init, port, UART_PORT_0);
    will_return(__wrap_uart_interrupt_init, 1);

    assert_int_equal(ttc_init(), -1);

    expect_value(__wrap_uart_interrupt_init, port, UART_PORT_0);
    will_return(__wrap_uart_interrupt_init, 0);

    expect_value(__wrap_uart_interrupt_enable, port, UART_PORT_0);
    will_return(__wrap_uart_interrupt_enable, 1);

    assert_int_equal(ttc_init(), -1);

    expect_value(__wrap_uart_interrupt_init, port, UART_PORT_0);
    will_return(__wrap_uart_interrupt_init, 0);

    expect_value(__wrap_uart_interrupt_enable, port, UART_PORT_0);
    will_return(__wrap_uart_interrupt_enable, 0);

    assert_return_code(ttc_init(), 1);
}

static void ttc_decode_test(void **state)
{
    uart_received_data_size = 6;

    uart_rx_buffer[0] = 10;
    uart_rx_buffer[1] = 11;
    uart_rx_buffer[2] = 12;
    uart_rx_buffer[3] = 13;
    uart_rx_buffer[4] = 14;
    uart_rx_buffer[5] = ttc_crc8(uart_rx_buffer, uart_received_data_size - 1);

    uint32_t ret_val = ((uint32_t)uart_rx_buffer[1] << 24) |
                       ((uint32_t)uart_rx_buffer[2] << 16) |
                       ((uint32_t)uart_rx_buffer[3] << 8) |
                       ((uint32_t)uart_rx_buffer[4] << 0);

    uint8_t address = 0;
    uint32_t value = 0;
    uint8_t command = 0;

    int result = ttc_decode(&address, &value, &command);

    assert_int_equal(address, uart_rx_buffer[0]);
    assert_int_equal(value, ret_val);
    assert_int_equal(command, TTC_COMMAND_WRITE);
    assert_return_code(result, 0);
}

static void ttc_answer_test(void **state)
{
    expect_value(__wrap_uart_interrupt_write, port, UART_PORT_0);
    expect_value(__wrap_uart_interrupt_write, len, 6);
    will_return(__wrap_uart_interrupt_write, 0);

    uint8_t address = 0;
    uint32_t value = 2;

    assert_return_code(ttc_answer(address, value), 0);
}

int main(void)
{
    const struct CMUnitTest ttc_tests[] = {
        cmocka_unit_test(ttc_init_test),
        cmocka_unit_test(ttc_decode_test),
        cmocka_unit_test(ttc_answer_test),
    };

    return cmocka_run_group_tests(ttc_tests, NULL, NULL);
}

/** \} End of ttc_test group */
