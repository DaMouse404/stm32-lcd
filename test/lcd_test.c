#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void gpio_port_write(uint32_t gpioport, uint16_t data) {}
void gpio_set(uint32_t gpioport, uint16_t gpios) {}
void gpio_clear(uint32_t gpioport, uint16_t gpios) {}
void gpio_mode_setup(uint32_t gpioport, uint8_t mode, uint8_t pull_up_down, uint16_t pins) {}
void rcc_periph_clock_enable(enum rcc_periph_clken clken) {}

static void test_lcd_clear() {}
static void test_lcd_address_set() {}
static void test_lcd_write_data() {}
static void test_lcd_init() {}

int main(void)
{
	const UnitTest tests[] = {
        unit_test(test_lcd_clear),
        unit_test(test_lcd_address_set),
		unit_test(test_lcd_write_data),
		unit_test(test_lcd_init)
	};
	return run_tests(tests);
}
