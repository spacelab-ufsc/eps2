TARGET_LEDS=leds_unit_test
TARGET_CURRENT_SENSOR=current_sensor_unit_test
TARGET_TEMP_SENSOR=temp_sensor_unit_test
TARGET_VOLTAGE_SENSOR=voltage_sensor_unit_test
TARGET_OBDH=obdh_unit_test
TARGET_TTC=ttc_unit_test
TARGET_EPS_DATA=eps2_data_unit_test

ifndef BUILD_DIR
	BUILD_DIR=$(CURDIR)
endif

CC=gcc
INC=../../
FLAGS=-fpic -std=c99 -Wall -pedantic -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -I$(INC) -Wl,--wrap=sys_log_print_event_from_module,--wrap=sys_log_new_line,--wrap=sys_log_print_msg,--wrap=sys_log_print_uint,--wrap=sys_log_print_int,--wrap=sys_log_print_float,--wrap=adc_init,--wrap=adc_read,--wrap=adc_temp_get_mref,--wrap=adc_temp_get_nref,--wrap=gpio_init,--wrap=gpio_set_state,--wrap=gpio_get_state,--wrap=gpio_toggle,--wrap=wdt_init,--wrap=wdt_reset,--wrap=tps382x_init,--wrap=tps382x_trigger

CURRENT_SENSOR_TEST_FLAGS=$(FLAGS),--wrap=adc_init,--wrap=adc_read,--wrap=adc_temp_get_mref,--wrap=adc_temp_get_nref,--wrap=adc_mutex_give,--wrap=adc_mutex_take,--wrap=max9934_read,--wrap=max9934_init
VOLTAGE_SENSOR_TEST_FLAGS=$(FLAGS),--wrap=adc_init,--wrap=adc_read,--wrap=adc_temp_get_mref,--wrap=adc_temp_get_nref,--wrap=adc_mutex_give,--wrap=adc_mutex_take
TEMP_SENSOR_TEST_FLAGS=$(FLAGS),--wrap=ads1248_init,--wrap=ads1248_reset,--wrap=ads1248_config_regs,--wrap=ads1248_read_regs,--wrap=ads1248_read_data,--wrap=ads1248_write_cmd,--wrap=ads1248_set_powerdown_mode,--wrap=adc_init,--wrap=adc_read,--wrap=adc_temp_get_mref,--wrap=adc_temp_get_nref,--wrap=adc_mutex_give,--wrap=adc_mutex_take
OBDH_TEST_FLAGS=$(FLAGS),--wrap=tca4311a_init,--wrap=tca4311a_enable,--wrap=tca4311a_disable,--wrap=tca4311a_is_ready,--wrap=i2c_slave_init,--wrap=i2c_slave_enable,--wrap=i2c_slave_disable,--wrap=i2c_slave_read,--wrap=i2c_slave_write,--wrap=i2c_init,--wrap=i2c_write,--wrap=i2c_read
TTC_TEST_FLAGS=$(FLAGS),--wrap=uart_interrupt_init,--wrap=uart_interrupt_enable,--wrap=uart_interrupt_disable,--wrap=uart_interrupt_write

.PHONY: all
all: leds_test current_sensor_test temp_sensor_test voltage_sensor_test obdh_test ttc_test eps2_data_test

.PHONY: leds_test
leds_test: $(BUILD_DIR)/leds.o $(BUILD_DIR)/leds_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/gpio_wrap.o
	$(CC) $(FLAGS) $(BUILD_DIR)/leds.o $(BUILD_DIR)/leds_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/gpio_wrap.o -o $(BUILD_DIR)/$(TARGET_LEDS) -lcmocka


.PHONY: current_sensor_test
current_sensor_test: $(BUILD_DIR)/current_sensor.o $(BUILD_DIR)/current_sensor_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/adc_wrap.o $(BUILD_DIR)/max9934_wrap.o
	$(CC) $(CURRENT_SENSOR_TEST_FLAGS) $(BUILD_DIR)/current_sensor.o $(BUILD_DIR)/current_sensor_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/adc_wrap.o $(BUILD_DIR)/max9934_wrap.o -o $(BUILD_DIR)/$(TARGET_CURRENT_SENSOR) -lcmocka

.PHONY: temp_sensor_test
temp_sensor_test: $(BUILD_DIR)/temp_sensor.o $(BUILD_DIR)/temp_sensor_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/ads1248_wrap.o $(BUILD_DIR)/gpio_wrap.o $(BUILD_DIR)/adc_wrap.o
	$(CC) $(TEMP_SENSOR_TEST_FLAGS) $(BUILD_DIR)/temp_sensor.o $(BUILD_DIR)/temp_sensor_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/ads1248_wrap.o $(BUILD_DIR)/gpio_wrap.o $(BUILD_DIR)/adc_wrap.o -o $(BUILD_DIR)/$(TARGET_TEMP_SENSOR) -lcmocka

.PHONY: voltage_sensor_test
voltage_sensor_test: $(BUILD_DIR)/voltage_sensor.o $(BUILD_DIR)/voltage_sensor_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/adc_wrap.o
	$(CC) $(VOLTAGE_SENSOR_TEST_FLAGS) $(BUILD_DIR)/voltage_sensor.o $(BUILD_DIR)/voltage_sensor_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/adc_wrap.o -o $(BUILD_DIR)/$(TARGET_VOLTAGE_SENSOR) -lcmocka

.PHONY: obdh_test
obdh_test: $(BUILD_DIR)/obdh.o $(BUILD_DIR)/obdh_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/tca4311a_wrap.o $(BUILD_DIR)/i2c_slave_wrap.o $(BUILD_DIR)/i2c_wrap.o
	$(CC) $(OBDH_TEST_FLAGS) $(BUILD_DIR)/obdh.o $(BUILD_DIR)/obdh_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/tca4311a_wrap.o $(BUILD_DIR)/i2c_slave_wrap.o $(BUILD_DIR)/i2c_wrap.o -o $(BUILD_DIR)/$(TARGET_OBDH) -lcmocka

.PHONY: ttc_test
ttc_test: $(BUILD_DIR)/ttc.o $(BUILD_DIR)/ttc_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/uart_interrupt_wrap.o
	$(CC) $(TTC_TEST_FLAGS) $(BUILD_DIR)/ttc.o $(BUILD_DIR)/ttc_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/uart_interrupt_wrap.o -o $(BUILD_DIR)/$(TARGET_TTC) -lcmocka

.PHONY: eps2_data_test
eps2_data_test: $(BUILD_DIR)/eps2_data.o $(BUILD_DIR)/eps2_data_test.o $(BUILD_DIR)/sys_log_wrap.o
	$(CC) $(TTC_TEST_FLAGS) $(BUILD_DIR)/eps2_data.o $(BUILD_DIR)/eps2_data_test.o $(BUILD_DIR)/sys_log_wrap.o -o $(BUILD_DIR)/$(TARGET_EPS_DATA) -lcmocka



# Devices
$(BUILD_DIR)/leds.o: ../../devices/leds/leds.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/current_sensor.o: ../../devices/current_sensor/current_sensor.c
	$(CC) $(CURRENT_SENSOR_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/temp_sensor.o: ../../devices/temp_sensor/temp_sensor.c
	$(CC) $(TEMP_SENSOR_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/voltage_sensor.o: ../../devices/voltage_sensor/voltage_sensor.c
	$(CC) $(VOLTAGE_SENSOR_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/obdh.o: ../../devices/obdh/obdh.c
	$(CC) $(OBDH_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/ttc.o: ../../devices/ttc/ttc.c
	$(CC) $(TTC_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/eps2_data.o: ../../app/structs/eps2_data.c
	$(CC) $(FLAGS) -c $< -o $@

# Tests
$(BUILD_DIR)/current_sensor_test.o: current_sensor_test.c
	$(CC) $(CURRENT_SENSOR_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/leds_test.o: leds_test.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/temp_sensor_test.o: temp_sensor_test.c
	$(CC) $(TEMP_SENSOR_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/voltage_sensor_test.o: voltage_sensor_test.c
	$(CC) $(VOLTAGE_SENSOR_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/obdh_test.o: obdh_test.c
	$(CC) $(OBDH_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/ttc_test.o: ttc_test.c
	$(CC) $(TTC_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/eps2_data_test.o: eps2_data_test.c
	$(CC) $(FLAGS) -c $< -o $@

# Mockups
$(BUILD_DIR)/sys_log_wrap.o: ../mockups/sys_log_wrap/sys_log_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/gpio_wrap.o: ../mockups/gpio_wrap/gpio_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/adc_wrap.o: ../mockups/adc_wrap/adc_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/max9934_wrap.o: ../mockups/max9934_wrap/max9934_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/ads1248_wrap.o: ../mockups/ads1248_wrap/ads1248_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/tca4311a_wrap.o: ../mockups/tca4311a_wrap/tca4311a_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/i2c_wrap.o: ../mockups/i2c_wrap/i2c_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/i2c_slave_wrap.o: ../mockups/i2c_slave_wrap/i2c_slave_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/uart_interrupt_wrap.o: ../mockups/uart_interrupt_wrap/uart_interrupt_wrap.c
	$(CC) $(FLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm $(BUILD_DIR)/$(TARGET_LEDS) $(BUILD_DIR)/$(TARGET_CURRENT_SENSOR) $(BUILD_DIR)/$(TARGET_TEMP_SENSOR) $(BUILD_DIR)/$(TARGET_VOLTAGE_SENSOR) $(BUILD_DIR)/$(TARGET_OBDH) $(BUILD_DIR)/$(TARGET_TTC) $(BUILD_DIR)/$(TARGET_EPS_DATA) $(BUILD_DIR)/*.o
