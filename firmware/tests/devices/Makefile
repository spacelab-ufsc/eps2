TARGET_LEDS=leds_unit_test
TARGET_CURRENT_SENSOR=current_sensor_unit_test
TARGET_TEMP_SENSOR=temp_sensor_unit_test
TARGET_VOLTAGE_SENSOR=voltage_sensor_unit_test
TARGET_OBDH=obdh_unit_test
TARGET_TTC=ttc_unit_test
TARGET_HEATER=heater_unit_test
TARGET_BAT_MANAGER=bat_manager_unit_test
TARGET_MEDIA=media_unit_test

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
HEATER_TEST_FLAGS=$(FLAGS),--wrap=pwm_init,--wrap=pwm_update,--wrap=pwm_stop,--wrap=pwm_disable,--wrap=temp_rtd_read_k,--wrap=temp_rtd_raw_to_k,--wrap=temp_rtd_read_raw
BAT_MANAGER_TEST_FLAGS=$(FLAGS),--wrap=ds2775g_init,__wrap=ds2775g_write_data,__wrap=ds2775g_read_register,__wrap=write_accumulated_current_max_value
MEDIA_TEST_FLAGS=$(FLAGS),--wrap=flash_init,--wrap=flash_write,--wrap=flash_write_single,--wrap=flash_read_single,--wrap=flash_write_long,--wrap=flash_read_long,--wrap=flash_erase

.PHONY: all
all: leds_test current_sensor_test temp_sensor_test voltage_sensor_test obdh_test ttc_test heater_test media_test

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

.PHONY: heater_test
heater_test: $(BUILD_DIR)/heater.o $(BUILD_DIR)/heater_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/pwm_wrap.o $(BUILD_DIR)/temp_sensor_wrap.o $(BUILD_DIR)/ads1248_wrap.o $(BUILD_DIR)/gpio_wrap.o $(BUILD_DIR)/adc_wrap.o
	$(CC) $(HEATER_TEST_FLAGS) $(BUILD_DIR)/heater.o $(BUILD_DIR)/heater_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/pwm_wrap.o $(BUILD_DIR)/temp_sensor_wrap.o $(BUILD_DIR)/ads1248_wrap.o $(BUILD_DIR)/gpio_wrap.o $(BUILD_DIR)/adc_wrap.o -o $(BUILD_DIR)/$(TARGET_HEATER) -lcmocka

.PHONY: bat_manager_test
bat_manager_test: $(BUILD_DIR)/bat_manager.o $(BUILD_DIR)/bat_manager_test.o $(BUILD_DIR)/ds2775g_wrap.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/gpio_wrap.o
	$(CC) $(BAT_MANAGER_TEST_FLAGS) $(BUILD_DIR)/bat_manager.o $(BUILD_DIR)/bat_manager_test.o $(BUILD_DIR)/ds2775g_wrap.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/gpio_wrap.o -o $(BUILD_DIR)/$(TARGET_BAT_MANAGER) -lcmocka

.PHONY: media_test
media_test: $(BUILD_DIR)/media.o $(BUILD_DIR)/media_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/flash_wrap.o $(BUILD_DIR)/gpio_wrap.o
	$(CC) $(MEDIA_TEST_FLAGS) $(BUILD_DIR)/media.o $(BUILD_DIR)/media_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/flash_wrap.o $(BUILD_DIR)/gpio_wrap.o -o $(BUILD_DIR)/$(TARGET_MEDIA) -lcmocka


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

$(BUILD_DIR)/heater.o: ../../devices/heater/heater.c
	$(CC) $(HEATER_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/bat_manager.o: ../../devices/bat_manager/bat_manager.c
	$(CC) $(BAT_MANAGER_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/media.o: ../../devices/media/media.c
	$(CC) $(MEDIA_TEST_FLAGS) -c $< -o $@

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

$(BUILD_DIR)/heater_test.o: heater_test.c
	$(CC) $(HEATER_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/bat_manager_test.o: bat_manager_test.c
	$(CC) $(BAT_MANAGER_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/media_test.o: media_test.c
	$(CC) $(MEDIA_TEST_FLAGS) -c $< -o $@


# Mockups
# Drivers
$(BUILD_DIR)/sys_log_wrap.o: ../mockups/sys_log_wrap/sys_log_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/gpio_wrap.o: ../mockups/drivers/gpio_wrap/gpio_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/adc_wrap.o: ../mockups/drivers/adc_wrap/adc_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/max9934_wrap.o: ../mockups/drivers/max9934_wrap/max9934_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/ads1248_wrap.o: ../mockups/drivers/ads1248_wrap/ads1248_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/tca4311a_wrap.o: ../mockups/drivers/tca4311a_wrap/tca4311a_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/i2c_wrap.o: ../mockups/drivers/i2c_wrap/i2c_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/i2c_slave_wrap.o: ../mockups/drivers/i2c_slave_wrap/i2c_slave_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/uart_interrupt_wrap.o: ../mockups/drivers/uart_interrupt_wrap/uart_interrupt_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/pwm_wrap.o: ../mockups/drivers/pwm_wrap/pwm_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/ds2775g_wrap.o: ../mockups/drivers/ds2775g_wrap/ds2775g_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/flash_wrap.o: ../mockups/drivers/flash_wrap/flash_wrap.c
	$(CC) $(FLAGS) -c $< -o $@


# Devices
$(BUILD_DIR)/temp_sensor_wrap.o: ../mockups/devices/temp_sensor_wrap/temp_sensor_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm $(BUILD_DIR)/$(TARGET_LEDS) $(BUILD_DIR)/$(TARGET_CURRENT_SENSOR) $(BUILD_DIR)/$(TARGET_TEMP_SENSOR) $(BUILD_DIR)/$(TARGET_VOLTAGE_SENSOR) $(BUILD_DIR)/$(TARGET_OBDH) $(BUILD_DIR)/$(TARGET_TTC) $(BUILD_DIR)/$(TARGET_HEATER) $(BUILD_DIR)/$(TARGET_BAT_MANAGER) $(BUILD_DIR)/$(TARGET_MEDIA) $(BUILD_DIR)/*.o
