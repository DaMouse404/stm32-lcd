#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

void lcd_address_set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    check_expected(x1);
    check_expected(y1);
    check_expected(x2);
    check_expected(y2);
}

void lcd_write_data(uint16_t colour) {
	check_expected(colour);
}

static void test_draw_rect() {
	expect_value(lcd_address_set, x1, 5);
	expect_value(lcd_address_set, y1, 5);
	expect_value(lcd_address_set, x2, 10);
	expect_value(lcd_address_set, y2, 10);
	expect_value_count(lcd_write_data, colour, 0xF, 25);

	lcd_draw_rect(5, 5, 10, 10, 0xF);
}

static void test_draw_line_horiz() {
	expect_value(lcd_address_set, x1,   4);
	expect_value(lcd_address_set, y1,   5);
	expect_value(lcd_address_set, x2,   9);
	expect_value(lcd_address_set, y2,   5);
	expect_value_count(lcd_write_data, colour, 0xF, 6);

	lcd_draw_line_horiz(4, 5, 6, 0xF);
}

static void test_draw_circle() {
    uint16_t values[14][5] = {
        {3, 1,  8,  1,   6}, // 2
        {3, 11, 8,  11,  6}, // 11
        {2, 2,  9,  2,   8}, // 3
        {2, 10, 9,  10,  8}, // 10
        {1, 3,  10, 3,  10}, // 4
        {1, 9,  10, 9,  10}, // 9
        {1, 4,  10, 4,  10}, // 5
        {1, 8,  10, 8,  10}, // 8
        {1, 5,  10, 5,  10}, // 6
        {1, 7,  10, 7,  10},  // 7
        {0, 6,  11, 6,  12},
        {0, 6,  11, 6,  12}
    };
    uint8_t i;

    for (i = 0; i < 12; ++i) {
		expect_value(lcd_address_set, x1,   values[i][0]);
        expect_value(lcd_address_set, y1,   values[i][1]);
        expect_value(lcd_address_set, x2,   values[i][2]);
        expect_value(lcd_address_set, y2,   values[i][3]);
        expect_value_count(lcd_write_data, colour, 0xF, values[i][4]);
    }

    lcd_draw_circle(6, 6, 6, 0xF);
}

int main(void)
{
	const UnitTest tests[] = {
		unit_test(test_draw_rect),
		unit_test(test_draw_line_horiz),
		unit_test(test_draw_circle)
	};
	return run_tests(tests);
}
