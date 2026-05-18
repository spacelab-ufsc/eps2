TARGET_BATTERY_MONITOR=battery_monitor_unit_test
TARGET_CURRENT_SENSOR=current_sensor_unit_test
TARGET_HEATER=heater_unit_test
TARGET_LEDS=leds_unit_test
TARGET_MEDIA=media_unit_test
TARGET_MPPT=mppt_unit_test
TARGET_OBDH=obdh_unit_test
TARGET_POWER_CONV=power_conv_unit_test
TARGET_TEMP_SENSOR=temp_sensor_unit_test
TARGET_TTC=ttc_unit_test
TARGET_VOLTAGE_SENSOR=voltage_sensor_unit_test
TARGET_WATCHDOG=watchdog_unit_test

ifndef BUILD_DIR
	BUILD_DIR=$(CURDIR)
endif

CC=gcc
INC=../../
FLAGS=-fpic -std=c99 -Wall -pedantic -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes -D_UNIT_TEST_ -I$(INC) -Wl,--wrap=sys_log_print_event_from_module,--wrap=sys_log_new_line,--wrap=sys_log_print_msg,--wrap=sys_log_print_uint,--wrap=sys_log_print_int,--wrap=sys_log_print_float,--wrap=adc_init,--wrap=adc_read,--wrap=adc_temp_get_mref,--wrap=adc_temp_get_nref,--wrap=gpio_init,--wrap=gpio_set_state,--wrap=gpio_get_state,--wrap=gpio_toggle,--wrap=wdt_init,--wrap=wdt_reset,--wrap=tps382x_init,--wrap=tps382x_trigger

BATTERY_MONITOR_TEST_FLAGS=$(FLAGS),--wrap=ds277Xg_init,--wrap=ds277Xg_read_voltage_mv,--wrap=ds277Xg_read_temperature_kelvin,--wrap=ds277Xg_read_current_ma,--wrap=ds277Xg_read_data,--wrap=ds277Xg_read_accumulated_current_mah
CURRENT_SENSOR_TEST_FLAGS=$(FLAGS),--wrap=adc_init,--wrap=adc_read,--wrap=adc_temp_get_mref,--wrap=adc_temp_get_nref,--wrap=adc_mutex_give,--wrap=adc_mutex_take,--wrap=max9934_read,--wrap=max9934_init
HEATER_TEST_FLAGS=$(FLAGS),--wrap=pwm_init,--wrap=pwm_update,--wrap=pwm_stop,--wrap=pwm_disable,--wrap=temp_rtd_read_k,--wrap=temp_rtd_raw_to_k,--wrap=temp_rtd_read_raw
MEDIA_TEST_FLAGS=$(FLAGS),--wrap=flash_init,--wrap=flash_write,--wrap=flash_write_single,--wrap=flash_read_single,--wrap=flash_write_long,--wrap=flash_read_long,--wrap=flash_erase
MPPT_FLAGS=$(FLAGS),--wrap=pwm_init,--wrap=pwm_update,--wrap=current_sensor_read,--wrap=voltage_sensor_read
OBDH_TEST_FLAGS=$(FLAGS),--wrap=tca4311a_init,--wrap=tca4311a_enable,--wrap=tca4311a_disable,--wrap=tca4311a_is_ready,--wrap=i2c_slave_init,--wrap=i2c_slave_enable,--wrap=i2c_slave_disable,--wrap=i2c_slave_read,--wrap=i2c_slave_write,--wrap=i2c_init,--wrap=i2c_write,--wrap=i2c_read
TEMP_SENSOR_TEST_FLAGS=$(FLAGS),--wrap=ads1248_init,--wrap=ads1248_reset,--wrap=ads1248_config_regs,--wrap=ads1248_read_regs,--wrap=ads1248_read_data,--wrap=ads1248_write_cmd,--wrap=ads1248_set_powerdown_mode,--wrap=adc_init,--wrap=adc_read,--wrap=adc_temp_get_mref,--wrap=adc_temp_get_nref,--wrap=adc_mutex_give,--wrap=adc_mutex_take
TTC_TEST_FLAGS=$(FLAGS),--wrap=uart_interrupt_init,--wrap=uart_interrupt_enable,--wrap=uart_interrupt_disable,--wrap=uart_interrupt_write,--wrap=uart_interrupt_read
VOLTAGE_SENSOR_TEST_FLAGS=$(FLAGS),--wrap=adc_init,--wrap=adc_read,--wrap=adc_temp_get_mref,--wrap=adc_temp_get_nref,--wrap=adc_mutex_give,--wrap=adc_mutex_take
POWER_CONV_FLAGS=$(FLAGS),--wrap=tps54x0_init,--wrap=tps54x0_enable,--wrap=tps54x0_disable

.PHONY: all
all: battery_monitor_test current_sensor_test heater_test leds_test media_test mppt_test obdh_test power_conv_test temp_sensor_test ttc_test voltage_sensor_test watchdog_test

.PHONY: battery_monitor_test
battery_monitor_test: $(BUILD_DIR)/battery_monitor.o $(BUILD_DIR)/battery_monitor_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/ds277Xg_wrap.o $(BUILD_DIR)/gpio_wrap.o
	$(CC) $(BATTERY_MONITOR_TEST_FLAGS) $(BUILD_DIR)/battery_monitor.o $(BUILD_DIR)/battery_monitor_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/ds277Xg_wrap.o $(BUILD_DIR)/gpio_wrap.o -o $(BUILD_DIR)/$(TARGET_BATTERY_MONITOR) -lcmocka

.PHONY: current_sensor_test
current_sensor_test: $(BUILD_DIR)/current_sensor.o $(BUILD_DIR)/current_sensor_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/adc_wrap.o $(BUILD_DIR)/max9934_wrap.o
	$(CC) $(CURRENT_SENSOR_TEST_FLAGS) $(BUILD_DIR)/current_sensor.o $(BUILD_DIR)/current_sensor_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/adc_wrap.o $(BUILD_DIR)/max9934_wrap.o -o $(BUILD_DIR)/$(TARGET_CURRENT_SENSOR) -lcmocka

.PHONY: heater_test
heater_test: $(BUILD_DIR)/heater.o $(BUILD_DIR)/heater_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/pwm_wrap.o $(BUILD_DIR)/temp_sensor_wrap.o $(BUILD_DIR)/ads1248_wrap.o $(BUILD_DIR)/gpio_wrap.o $(BUILD_DIR)/adc_wrap.o
	$(CC) $(HEATER_TEST_FLAGS) $(BUILD_DIR)/heater.o $(BUILD_DIR)/heater_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/pwm_wrap.o $(BUILD_DIR)/temp_sensor_wrap.o $(BUILD_DIR)/ads1248_wrap.o $(BUILD_DIR)/gpio_wrap.o $(BUILD_DIR)/adc_wrap.o -o $(BUILD_DIR)/$(TARGET_HEATER) -lcmocka

.PHONY: leds_test
leds_test: $(BUILD_DIR)/leds.o $(BUILD_DIR)/leds_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/gpio_wrap.o
	$(CC) $(FLAGS) $(BUILD_DIR)/leds.o $(BUILD_DIR)/leds_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/gpio_wrap.o -o $(BUILD_DIR)/$(TARGET_LEDS) -lcmocka

.PHONY: media_test
media_test: $(BUILD_DIR)/media.o $(BUILD_DIR)/media_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/flash_wrap.o $(BUILD_DIR)/gpio_wrap.o
	$(CC) $(MEDIA_TEST_FLAGS) $(BUILD_DIR)/media.o $(BUILD_DIR)/media_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/flash_wrap.o $(BUILD_DIR)/gpio_wrap.o -o $(BUILD_DIR)/$(TARGET_MEDIA) -lcmocka

.PHONY: mppt_test
mppt_test: $(BUILD_DIR)/mppt.o $(BUILD_DIR)/mppt_test.o $(BUILD_DIR)/current_sensor_wrap.o $(BUILD_DIR)/voltage_sensor_wrap.o $(BUILD_DIR)/pwm_wrap.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/gpio_wrap.o
	$(CC) $(MPPT_FLAGS) $(BUILD_DIR)/mppt.o $(BUILD_DIR)/mppt_test.o $(BUILD_DIR)/current_sensor_wrap.o $(BUILD_DIR)/voltage_sensor_wrap.o $(BUILD_DIR)/pwm_wrap.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/gpio_wrap.o -o $(BUILD_DIR)/$(TARGET_MPPT) -lcmocka

.PHONY: obdh_test
obdh_test: $(BUILD_DIR)/obdh.o $(BUILD_DIR)/obdh_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/tca4311a_wrap.o $(BUILD_DIR)/i2c_slave_wrap.o $(BUILD_DIR)/i2c_wrap.o
	$(CC) $(OBDH_TEST_FLAGS) $(BUILD_DIR)/obdh.o $(BUILD_DIR)/obdh_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/tca4311a_wrap.o $(BUILD_DIR)/i2c_slave_wrap.o $(BUILD_DIR)/i2c_wrap.o -o $(BUILD_DIR)/$(TARGET_OBDH) -lcmocka

.PHONY: power_conv_test
power_conv_test: $(BUILD_DIR)/power_conv.o $(BUILD_DIR)/power_conv_test.o $(BUILD_DIR)/tps54x0_wrap.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/gpio_wrap.o
	$(CC) $(POWER_CONV_FLAGS) $(BUILD_DIR)/power_conv.o $(BUILD_DIR)/power_conv_test.o $(BUILD_DIR)/tps54x0_wrap.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/gpio_wrap.o -o $(BUILD_DIR)/$(TARGET_POWER_CONV) -lcmocka

.PHONY: temp_sensor_test
temp_sensor_test: $(BUILD_DIR)/temp_sensor.o $(BUILD_DIR)/temp_sensor_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/ads1248_wrap.o $(BUILD_DIR)/gpio_wrap.o $(BUILD_DIR)/adc_wrap.o
	$(CC) $(TEMP_SENSOR_TEST_FLAGS) $(BUILD_DIR)/temp_sensor.o $(BUILD_DIR)/temp_sensor_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/ads1248_wrap.o $(BUILD_DIR)/gpio_wrap.o $(BUILD_DIR)/adc_wrap.o -o $(BUILD_DIR)/$(TARGET_TEMP_SENSOR) -lcmocka

.PHONY: ttc_test
ttc_test: $(BUILD_DIR)/ttc.o $(BUILD_DIR)/ttc_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/uart_interrupt_wrap.o
	$(CC) $(TTC_TEST_FLAGS) $(BUILD_DIR)/ttc.o $(BUILD_DIR)/ttc_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/uart_interrupt_wrap.o -o $(BUILD_DIR)/$(TARGET_TTC) -lcmocka

.PHONY: voltage_sensor_test
voltage_sensor_test: $(BUILD_DIR)/voltage_sensor.o $(BUILD_DIR)/voltage_sensor_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/adc_wrap.o
	$(CC) $(VOLTAGE_SENSOR_TEST_FLAGS) $(BUILD_DIR)/voltage_sensor.o $(BUILD_DIR)/voltage_sensor_test.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/adc_wrap.o -o $(BUILD_DIR)/$(TARGET_VOLTAGE_SENSOR) -lcmocka

.PHONY: watchdog_test
watchdog_test: $(BUILD_DIR)/watchdog.o $(BUILD_DIR)/watchdog_test.o $(BUILD_DIR)/wdt_wrap.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/gpio_wrap.o
	$(CC) $(FLAGS) $(BUILD_DIR)/watchdog.o $(BUILD_DIR)/watchdog_test.o $(BUILD_DIR)/wdt_wrap.o $(BUILD_DIR)/sys_log_wrap.o $(BUILD_DIR)/gpio_wrap.o -o $(BUILD_DIR)/$(TARGET_WATCHDOG) -lcmocka



# Devices
$(BUILD_DIR)/battery_monitor.o: ../../devices/battery_monitor/battery_monitor.c
	$(CC) $(BATTERY_MONITOR_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/current_sensor.o: ../../devices/current_sensor/current_sensor.c
	$(CC) $(CURRENT_SENSOR_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/heater.o: ../../devices/heater/heater.c
	$(CC) $(HEATER_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/leds.o: ../../devices/leds/leds.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/media.o: ../../devices/media/media.c
	$(CC) $(MEDIA_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/mppt.o: ../../devices/mppt/mppt.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/obdh.o: ../../devices/obdh/obdh.c
	$(CC) $(OBDH_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/power_conv.o: ../../devices/power_conv/power_conv.c
	$(CC) $(POWER_CONV_FLAGS) -c $< -o $@

$(BUILD_DIR)/temp_sensor.o: ../../devices/temp_sensor/temp_sensor.c
	$(CC) $(TEMP_SENSOR_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/ttc.o: ../../devices/ttc/ttc.c
	$(CC) $(TTC_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/voltage_sensor.o: ../../devices/voltage_sensor/voltage_sensor.c
	$(CC) $(VOLTAGE_SENSOR_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/watchdog.o: ../../devices/watchdog/watchdog.c
	$(CC) $(FLAGS) -c $< -o $@

# Tests
$(BUILD_DIR)/battery_monitor_test.o: battery_monitor_test.c
	$(CC) $(BATTERY_MONITOR_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/current_sensor_test.o: current_sensor_test.c
	$(CC) $(CURRENT_SENSOR_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/heater_test.o: heater_test.c
	$(CC) $(HEATER_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/leds_test.o: leds_test.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/media_test.o: media_test.c
	$(CC) $(MEDIA_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/mppt_test.o: mppt_test.c
	$(CC) $(MPPT_FLAGS) -c $< -o $@

$(BUILD_DIR)/obdh_test.o: obdh_test.c
	$(CC) $(OBDH_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/power_conv_test.o: power_conv_test.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/temp_sensor_test.o: temp_sensor_test.c
	$(CC) $(TEMP_SENSOR_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/ttc_test.o: ttc_test.c
	$(CC) $(TTC_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/voltage_sensor_test.o: voltage_sensor_test.c
	$(CC) $(VOLTAGE_SENSOR_TEST_FLAGS) -c $< -o $@

$(BUILD_DIR)/watchdog_test.o: watchdog_test.c
	$(CC) $(FLAGS) -c $< -o $@

# Mockups
# Drivers
$(BUILD_DIR)/adc_wrap.o: ../mockups/drivers/adc_wrap/adc_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/ads1248_wrap.o: ../mockups/drivers/ads1248_wrap/ads1248_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/ds277Xg_wrap.o: ../mockups/drivers/ds277Xg_wrap/ds277Xg_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/flash_wrap.o: ../mockups/drivers/flash_wrap/flash_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/gpio_wrap.o: ../mockups/drivers/gpio_wrap/gpio_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/i2c_wrap.o: ../mockups/drivers/i2c_wrap/i2c_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/i2c_slave_wrap.o: ../mockups/drivers/i2c_slave_wrap/i2c_slave_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/max9934_wrap.o: ../mockups/drivers/max9934_wrap/max9934_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/pwm_wrap.o: ../mockups/drivers/pwm_wrap/pwm_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/sys_log_wrap.o: ../mockups/sys_log_wrap/sys_log_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/tca4311a_wrap.o: ../mockups/drivers/tca4311a_wrap/tca4311a_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/tps54x0_wrap.o: ../mockups/drivers/tps54x0_wrap/tps54x0_wrap.c
	$(CC) $(POWER_CONV_FLAGS) -c $< -o $@

$(BUILD_DIR)/uart_interrupt_wrap.o: ../mockups/drivers/uart_interrupt_wrap/uart_interrupt_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/wdt_wrap.o: ../mockups/drivers/wdt_wrap/wdt_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

# Devices
$(BUILD_DIR)/current_sensor_wrap.o: ../mockups/devices/current_sensor_wrap/current_sensor_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/temp_sensor_wrap.o: ../mockups/devices/temp_sensor_wrap/temp_sensor_wrap.c
	$(CC) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/voltage_sensor_wrap.o: ../mockups/devices/voltage_sensor_wrap/voltage_sensor_wrap.c
	$(CC) $(FLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm $(BUILD_DIR)/$(TARGET_BATTERY_MONITOR) $(BUILD_DIR)/$(TARGET_CURRENT_SENSOR) $(BUILD_DIR)/$(TARGET_HEATER) $(BUILD_DIR)/$(TARGET_LEDS) $(BUILD_DIR)/$(TARGET_MEDIA) $(BUILD_DIR)/$(TARGET_MPPT) $(BUILD_DIR)/$(TARGET_OBDH) $(BUILD_DIR)/$(TARGET_POWER_CONV) $(BUILD_DIR)/$(TARGET_TEMP_SENSOR) $(BUILD_DIR)/$(TARGET_TTC) $(BUILD_DIR)/$(TARGET_VOLTAGE_SENSOR) $(BUILD_DIR)/$(TARGET_WATCHDOG) $(BUILD_DIR)/*.o
