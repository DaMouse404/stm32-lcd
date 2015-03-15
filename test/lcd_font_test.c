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

	/* @5 'I' (13 pixels wide) */
	0xFF, 0xF8, // #############
	0x07, 0x00, //      ###
	0x07, 0x00, //      ###
	0x07, 0x00, //      ###
	0xFF, 0xF8, // #############
};

/* Character descriptors for Monospac821 BT 12pt */
/* { [Char width in bits], [Offset into testCharBitmaps in bytes] } */
static const FONT_CHAR_INFO testDescriptors[] =
{
	{7, 0}, 		/* H */
	{13, 5}			/* I */
};

/* Font information for Monospac821 BT 12pt */
static const FONT_INFO testFontInfo =
{
	5, /*  Character height */
	'H', /*  Start character */
	'I', /*  End character */
	10, /*  Width, in pixels, of space character */
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

static void expect_H() {
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
}

static void expect_I() {
	expect_value_count(lcd_write_data, colour, 0xF0, 13);

	expect_value_count(lcd_write_data, colour, 0x0F, 5);
	expect_value_count(lcd_write_data, colour, 0xF0, 3);
	expect_value_count(lcd_write_data, colour, 0x0F, 5);

	expect_value_count(lcd_write_data, colour, 0x0F, 5);
	expect_value_count(lcd_write_data, colour, 0xF0, 3);
	expect_value_count(lcd_write_data, colour, 0x0F, 5);

	expect_value_count(lcd_write_data, colour, 0x0F, 5);
	expect_value_count(lcd_write_data, colour, 0xF0, 3);
	expect_value_count(lcd_write_data, colour, 0x0F, 5);

	expect_value_count(lcd_write_data, colour, 0xF0, 13);
}

static void test_draw_string_HI() {
	expect_value(lcd_address_set, x1, 10);
	expect_value(lcd_address_set, y1, 10);
	expect_value(lcd_address_set, x2, 16);
	expect_value(lcd_address_set, y2, 14);

	expect_H();

	expect_value(lcd_address_set, x1, 27);
	expect_value(lcd_address_set, y1, 10);
	expect_value(lcd_address_set, x2, 39);
	expect_value(lcd_address_set, y2, 14);

	expect_I();

	lcd_draw_font_string(10, 10, &testFontInfo, "H I", 0xF0, 0x0F);
}

static void test_draw_string_HI_with_space() {
	expect_value(lcd_address_set, x1, 10);
	expect_value(lcd_address_set, y1, 10);
	expect_value(lcd_address_set, x2, 16);
	expect_value(lcd_address_set, y2, 14);

	expect_H();

	expect_value(lcd_address_set, x1, 17);
	expect_value(lcd_address_set, y1, 10);
	expect_value(lcd_address_set, x2, 29);
	expect_value(lcd_address_set, y2, 14);

	expect_I();

	lcd_draw_font_string(10, 10, &testFontInfo, "HI", 0xF0, 0x0F);
}

static void test_draw_char_I() {
	expect_value(lcd_address_set, x1, 10);
	expect_value(lcd_address_set, y1, 10);
	expect_value(lcd_address_set, x2, 22);
	expect_value(lcd_address_set, y2, 14);

	expect_I();

	lcd_draw_font_char(10, 10, &testFontInfo, 'I', 0xF0, 0x0F);
}

static void test_draw_char_H() {
	expect_value(lcd_address_set, x1, 10);
	expect_value(lcd_address_set, y1, 10);
	expect_value(lcd_address_set, x2, 16);
	expect_value(lcd_address_set, y2, 14);

	expect_H();

	lcd_draw_font_char(10, 10, &testFontInfo, 'H', 0xF0, 0x0F);
}

int main(void)
{
	const UnitTest tests[] = {
		unit_test(test_draw_char_H),
		unit_test(test_draw_char_I),
		unit_test(test_draw_string_HI)
	};
	return run_tests(tests);
}
