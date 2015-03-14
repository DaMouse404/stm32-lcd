#include "lcd.h"
#include "lcd_shapes.h"
#include "colours.h"

static inline uint16_t sqr(int16_t x)
{
	return x * x;
}

void lcd_draw_rect(
	uint16_t x1, uint16_t y1,
	uint16_t x2, uint16_t y2,
	uint16_t colour
)
{
	uint16_t x, y;

	lcd_address_set(x1, y1, x2, y2);

	for (y = y1; y < y2; ++y) {
		for (x = x1; x < x2; ++x) {
			lcd_write_data(colour);
		}
	}
}

void lcd_draw_line_horiz(
	uint16_t x1, uint16_t y1,
	uint16_t l,
	uint16_t colour
)
{
	uint16_t x;

	l += (x1 - 1);

	lcd_address_set(x1, y1, l, y1);

	for (x = x1; x <= l; ++x) {
		lcd_write_data(colour);
	}
}

void lcd_draw_circle(
	uint16_t x1, uint16_t y1,
	uint16_t r,
	uint16_t colour
)
{
	int16_t x, y;
	int16_t rSqr = sqr(r);

	/*
	 * Renders both top and bottom in parrallel
	 * Start at r and decrement towards 0
	 * by iterating up to the point where
	 * (sqr(x) + sqr(y)) > sqr(r) or 1/2 the square
	 */
	for (y = r; y >= 0; --y) {
		for (x = r; x > 0; --x) {
			if ((sqr(x) + sqr(y)) <= rSqr) {
				/*
				 * Draw  line from centre-x to centre+x
				 * length is thus 2 * x
				 */
				lcd_draw_line_horiz(x1 - x, y1 - y, (2 * x), colour);
				lcd_draw_line_horiz(x1 - x, y1 + y, (2 * x), colour);

				break;
			}
		}
	}
}
