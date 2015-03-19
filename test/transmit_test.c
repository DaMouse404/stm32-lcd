#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/rcc.h>

void rcc_periph_clock_enable(enum rcc_periph_clken clken) {}
void gpio_mode_setup(uint32_t gpioport, uint8_t mode, uint8_t pull_up_down, uint16_t pin) {}
void gpio_set_af(uint32_t gpioport, uint8_t alt_func_num, uint16_t gpios) {}
void usart_set_baudrate(uint32_t usart, uint32_t baud) {}
void usart_set_databits(uint32_t usart, uint32_t bits) {}
void usart_set_stopbits(uint32_t usart, uint32_t stopbits) {}
void usart_set_mode(uint32_t usart, uint32_t mode) {}
void usart_set_parity(uint32_t usart, uint32_t parity) {}
void usart_set_flow_control(uint32_t usart, uint32_t flowcontrol) {}
void usart_enable(uint32_t usart) {}
void usart_send_blocking(uint32_t usart, uint16_t data) {
	check_expected(usart);
	check_expected(data);
}

void test_transmit() {
	expect_value(usart_send_blocking, usart, USART2);
	expect_value(usart_send_blocking, data, 'F');

	transmit('F');
}

int main(void)
{
	const UnitTest tests[] = {
		unit_test(test_transmit)
	};
	return run_tests(tests);
}
