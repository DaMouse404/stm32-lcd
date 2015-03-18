#include <math.h>
#include <string.h>

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
	const uint8_t *char_maps = *(font->char_maps);

	uint8_t bytes = (char_info->width/8) + 1;
	uint16_t x, y, byte;
	uint16_t offset;
	uint8_t bit;

	lcd_address_set(
			x1, y1,
			x1 + char_info->width - 1,
			y1 + font->char_height - 1
	);

	for (y = 0; y < font->char_height; y++) {
		for (x = 0; x < char_info->width; x++) {
			byte = (uint8_t) (x / 8);
			offset = char_info->offset + (y * bytes) + byte;
			bit = x % 8;

			if (char_maps[offset] & (1 << (7-bit))) {
				lcd_write_data(colour);
			} else {
				lcd_write_data(background);
			}
		}
	}
}

void lcd_draw_font_string(
	uint16_t x1, uint16_t y1,
	const FONT_INFO *font,
	char *str,
	uint16_t colour, uint16_t background
) {
	uint16_t len = strlen(str);
	uint16_t x = 0;

	uint16_t i;

	uint8_t char_offset;
	const FONT_CHAR_INFO *char_info;

	for (i = 0; i < len; ++i) {
		if (str[i] == ' ') {
			x += font->space_width;
		} else {
			char_offset = str[i] - font->start_char;
			char_info = &font->char_info[char_offset];

			lcd_draw_font_char(x1+x, y1, font, str[i], colour, background);

			x += char_info->width;
		}
	}
}
