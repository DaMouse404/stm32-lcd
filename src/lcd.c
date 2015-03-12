#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "lcd.h"

/*
 * 64Mhz clock / 64000 = 1000 = 1kHz :D
 * TODO: Hook up to real timers for more accurate timing
 */
static inline void delay_1ms(void)
{
	uint16_t i;

	for (i = 0; i < 64000; i++) {
		__asm__("nop");
	}
}

static void lcd_write_bus(uint16_t data)
{
	gpio_port_write(LCD_DATA_PORT, data);

	gpio_clear(LCD_WR);
	gpio_set(LCD_WR);
}

static void lcd_write_register(uint16_t data)
{
	gpio_clear(LCD_RS);

	lcd_write_bus(data);
}

void lcd_write_data(uint16_t data)
{
	gpio_set(LCD_RS);

	lcd_write_bus(data);
}

void lcd_init(void)
{
	rcc_periph_clock_enable(RCC_GPIOD);
	rcc_periph_clock_enable(RCC_GPIOC);

	gpio_mode_setup(
			LCD_DATA_PORT,
			GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
			LCD_DATA_PINS
	);
	gpio_mode_setup(
			LCD_CTRL_PORT,
			GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
			LCD_CTRL_PINS
	);

	gpio_set(LCD_CS);
	gpio_set(LCD_RD);
	gpio_set(LCD_WR);
	gpio_clear(LCD_REST);

	delay_1ms();
	gpio_set(LCD_REST);

	delay_1ms();
	gpio_clear(LCD_CS);

	lcd_write_register(0x01);
	lcd_write_data(16);
}

void lcd_address_set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	lcd_write_register(0x02);
	lcd_write_data(y1);
	lcd_write_register(0x03);
	lcd_write_data(x1);
	lcd_write_register(0x06);
	lcd_write_data(y2);
	lcd_write_register(0x07);
	lcd_write_data(x2);
	lcd_write_register(0x0f);
}

void lcd_clear(uint16_t color)
{
	uint16_t i, j;

	lcd_address_set(0, 0, LCD_WIDTH-1, LCD_HEIGHT-1);

	for (i = 0; i < LCD_WIDTH; i++) {
		for (j = 0; j < LCD_HEIGHT; j++) {
			lcd_write_data(color);
		}
	}
}
