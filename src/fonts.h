#ifndef FONTS_H
#define FONTS_H

typedef struct FONT_CHAR_INFO {
	uint8_t width;
	uint16_t offset;
} FONT_CHAR_INFO;

typedef struct FONT_INFO {
	uint8_t char_height;
	uint8_t start_char;
	uint8_t end_char;
	uint8_t space_width;
	const FONT_CHAR_INFO *char_info;
	const uint8_t *char_maps[];
} FONT_INFO;

#endif
