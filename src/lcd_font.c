#include <math.h>

#include "lcd.h"
#include "lcd_font.h"
#include "colours.h"
#include "fonts.h"

/*
 * lcd_draw_char(10, 10, &font, 'H', RED, BLACK);
 */
void lcd_draw_font_char(
		uint16_t x1, uint16_t y1,
		const FONT_INFO *font,
		char character,
		uint16_t colour, uint16_t background
) {
	uint8_t char_offset = character - font->start_char;
	const FONT_CHAR_INFO *char_info = &font->char_info[char_offset];
	const uint8_t *char_map = font->char_maps[char_info->offset];

	uint16_t x, y, i, byte;

	lcd_address_set(
			x1, y1,
			x1 + char_info->width - 1,
			y1 + font->char_height - 1
	);

	for (y = 0; y < font->char_height; y++) {
		for (x = 0; x < char_info->width; x++) {
			byte = (uint8_t) (x / 8);

			if (char_map[y + byte] & (1 << (7-x))) {
				lcd_write_data(colour);
			} else {
				lcd_write_data(background);
			}
		}
	}
}
