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
}

static void test_draw_circle() {
    uint16_t values[14][5] = {
        {6, 0, 12, 0, 6}, // 1
        {6, 12, 12, 12, 6}, // 12
        {3, 1, 12, 1, 9}, // 2
        {3, 11, 12, 11, 9}, // 11
        {2, 2, 12, 2, 10}, // 3
        {2, 10, 12, 10, 10}, // 10
        {1, 3, 12, 3, 11}, // 4
        {1, 9, 12, 9, 11}, // 9
        {1, 4, 12, 4, 11}, // 5
        {1, 8, 12, 8, 11}, // 8
        {1, 5, 12, 5, 11}, // 6
        {1, 7, 12, 7, 11},  // 7
        {0, 6, 12, 6, 11},
        {0, 6, 12, 6, 11}
    };
    uint8_t i;

    for (i = 0; i < 14; ++i) {
        expect_value(lcd_address_set, x1,   values[i][0]);
        expect_value(lcd_address_set, y1,   values[i][1]);
        expect_value(lcd_address_set, x2,   values[i][2]);
        expect_value(lcd_address_set, y2,   values[i][3]);
        // TODO: CORRECT COUNTS HERE
        // expect_value_count(lcd_write_data, colour, 0, values[i][4]);
    }

    lcd_draw_circle(6, 6, 6, 0);
}

int main(void)
{
	const UnitTest tests[] = {
		unit_test(test_draw_circle)
	};
	return run_tests(tests);
}
