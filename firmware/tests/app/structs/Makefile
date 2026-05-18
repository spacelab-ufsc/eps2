TARGET_EPS_DATA=eps2_data_unit_test

ifndef BUILD_DIR
	BUILD_DIR=$(CURDIR)
endif

CC=gcc
INC=../../../
FLAGS=-fpic -std=c99 -Wall -pedantic -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -I$(INC) -Wl,--wrap=sys_log_print_event_from_module,--wrap=sys_log_new_line,--wrap=sys_log_print_msg,--wrap=sys_log_print_uint,--wrap=sys_log_print_int,--wrap=sys_log_print_float,--wrap=adc_init,--wrap=adc_read,--wrap=adc_temp_get_mref,--wrap=adc_temp_get_nref,--wrap=gpio_init,--wrap=gpio_set_state,--wrap=gpio_get_state,--wrap=gpio_toggle,--wrap=wdt_init,--wrap=wdt_reset,--wrap=tps382x_init,--wrap=tps382x_trigger
TTC_TEST_FLAGS=$(FLAGS),--wrap=uart_interrupt_init,--wrap=uart_interrupt_enable,--wrap=uart_interrupt_disable,--wrap=uart_interrupt_write

.PHONY: all
all: eps2_data_test

.PHONY: eps2_data_test
eps2_data_test: $(BUILD_DIR)/eps2_data.o $(BUILD_DIR)/eps2_data_test.o $(BUILD_DIR)/sys_log_wrap.o
	$(CC) $(TTC_TEST_FLAGS) $(BUILD_DIR)/eps2_data.o $(BUILD_DIR)/eps2_data_test.o $(BUILD_DIR)/sys_log_wrap.o -o $(BUILD_DIR)/$(TARGET_EPS_DATA) -lcmocka



# Structs
$(BUILD_DIR)/eps2_data.o: ../../../app/structs/eps2_data.c
	$(CC) $(FLAGS) -c $< -o $@

# Tests
$(BUILD_DIR)/eps2_data_test.o: eps2_data_test.c
	$(CC) $(FLAGS) -c $< -o $@

# Mockups
$(BUILD_DIR)/sys_log_wrap.o: ../../mockups/sys_log_wrap/sys_log_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/gpio_wrap.o: ../../mockups/drivers/gpio_wrap/gpio_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/adc_wrap.o: ../../mockups/drivers/adc_wrap/adc_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/max9934_wrap.o: ../../mockups/drivers/max9934_wrap/max9934_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/ads1248_wrap.o: ../../mockups/drivers/ads1248_wrap/ads1248_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/tca4311a_wrap.o: ../../mockups/drivers/tca4311a_wrap/tca4311a_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/i2c_wrap.o: ../../mockups/drivers/i2c_wrap/i2c_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/i2c_slave_wrap.o: ../../mockups/drivers/i2c_slave_wrap/i2c_slave_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/uart_interrupt_wrap.o: ../../mockups/drivers/uart_interrupt_wrap/uart_interrupt_wrap.c
	$(CC) $(FLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm $(BUILD_DIR)/$(TARGET_EPS_DATA) $(BUILD_DIR)/*.o
