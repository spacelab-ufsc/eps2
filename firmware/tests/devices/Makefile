TARGET_LEDS=leds_unit_test

ifndef BUILD_DIR
	BUILD_DIR=$(CURDIR)
endif

CC=gcc
INC=../../
FLAGS=-fpic -std=c99 -Wall -pedantic -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -I$(INC) -Wl,--wrap=sys_log_print_event_from_module,--wrap=sys_log_new_line,--wrap=sys_log_print_msg,--wrap=sys_log_print_uint,--wrap=sys_log_print_int,--wrap=sys_log_print_float,--wrap=adc_init,--wrap=adc_read,--wrap=adc_temp_get_mref,--wrap=adc_temp_get_nref,--wrap=gpio_init,--wrap=gpio_set_state,--wrap=gpio_get_state,--wrap=gpio_toggle,--wrap=wdt_init,--wrap=wdt_reset,--wrap=tps382x_init,--wrap=tps382x_trigger

.PHONY: all
all: leds_test

.PHONY: leds_test
leds_test: $(BUILD_DIR)/leds.o $(BUILD_DIR)/leds_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/gpio_wrap.o
	$(CC) $(FLAGS) $(BUILD_DIR)/leds.o $(BUILD_DIR)/leds_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/gpio_wrap.o -o $(BUILD_DIR)/$(TARGET_LEDS) -lcmocka

$(BUILD_DIR)/leds.o: ../../devices/leds/leds.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/leds_test.o: leds_test.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/sys_log_wrap.o: ../mockups/sys_log_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/gpio_wrap.o: ../mockups/gpio_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm $(BUILD_DIR)/$(TARGET_LEDS) $(BUILD_DIR)/*.o
