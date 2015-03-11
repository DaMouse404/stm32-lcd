#include <libopencm3/stm32/gpio.h>

#define LCD_WIDTH   800
#define LCD_HEIGHT  480

#define LCD_DATA_PORT GPIOD
#define LCD_DATA_PINS GPIO_ALL

#define LCD_CTRL_PORT GPIOC
#define LCD_CTRL_PINS (GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4)
#define LCD_RD      GPIOC, GPIO0
#define LCD_WR      GPIOC, GPIO1
#define LCD_RS      GPIOC, GPIO2
#define LCD_REST    GPIOC, GPIO3
#define LCD_CS      GPIOC, GPIO4

void lcd_init(void);
void lcd_clear(uint16_t colour);

void lcd_address_set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void lcd_write_data(uint16_t colour);

