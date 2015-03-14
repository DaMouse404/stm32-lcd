#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/fonts.h"

/* Character bitmaps for Monospac821 BT 12pt */
static const uint8_t testBitmaps[] =
{
	/* @0 'H' (7 pixels wide) */
	0x82, // #     #
	0x82, // #     #
	0xFE, // #######
	0x82, // #     #
	0x82, // #     #
};

/* Character descriptors for Monospac821 BT 12pt */
/* { [Char width in bits], [Offset into testCharBitmaps in bytes] } */
static const FONT_CHAR_INFO testDescriptors[] =
{
	{7, 0}, 		/* H */
};

/* Font information for Monospac821 BT 12pt */
static const FONT_INFO testFontInfo =
{
	5, /*  Character height */
	'H', /*  Start character */
	'H', /*  End character */
	2, /*  Width, in pixels, of space character */
	testDescriptors, /*  Character descriptor array */
	testBitmaps, /*  Character bitmap array */
};

void lcd_address_set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
    check_expected(x1);
    check_expected(y1);
    check_expected(x2);
    check_expected(y2);
}

void lcd_write_data(uint16_t colour) {
	check_expected(colour);
}

static void test_draw_char_H() {
	expect_value(lcd_address_set, x1, 10);
	expect_value(lcd_address_set, y1, 10);
	expect_value(lcd_address_set, x2, 16);
	expect_value(lcd_address_set, y2, 14);

	expect_value_count(lcd_write_data, colour, 0xF0, 1);
	expect_value_count(lcd_write_data, colour, 0x0F, 5);
	expect_value_count(lcd_write_data, colour, 0xF0, 1);

	expect_value_count(lcd_write_data, colour, 0xF0, 1);
	expect_value_count(lcd_write_data, colour, 0x0F, 5);
	expect_value_count(lcd_write_data, colour, 0xF0, 1);

	expect_value_count(lcd_write_data, colour, 0xF0, 7);

	expect_value_count(lcd_write_data, colour, 0xF0, 1);
	expect_value_count(lcd_write_data, colour, 0x0F, 5);
	expect_value_count(lcd_write_data, colour, 0xF0, 1);

	expect_value_count(lcd_write_data, colour, 0xF0, 1);
	expect_value_count(lcd_write_data, colour, 0x0F, 5);
	expect_value_count(lcd_write_data, colour, 0xF0, 1);

	lcd_draw_font_char(10, 10, &testFontInfo, 'H', 0xF0, 0x0F);
}

int main(void)
{
	const UnitTest tests[] = {
		unit_test(test_draw_char_H),
	};
	return run_tests(tests);
}
