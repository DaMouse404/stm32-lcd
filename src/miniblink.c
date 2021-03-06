/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2009 Uwe Hermann <uwe@hermann-uwe.de>
 * Copyright (C) 2011 Stephen Caudle <scaudle@doceme.com>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "led.h"
#include "lcd.h"
#include "lcd_shapes.h"
#include "lcd_font.h"
#include "colours.h"
#include "cpu.h"

#include "fonts/monospace.h"

#ifdef UNIT_TESTING
#define main test_main
#define loop 0
#else
#define loop 1
#endif

int main(void)
{
	cpu_init();

	lcd_init();
	lcd_clear(GRAY);
	lcd_draw_circle(50,  50,  25, RED);
	lcd_draw_circle(50,  100, 25, WHITE);
	lcd_draw_circle(100, 50,  25, RED);
	lcd_draw_circle(100, 100, 25, WHITE);

	lcd_draw_font_char(100, 50, &monospac821BT_11ptFontInfo, 'H', WHITE, BLACK);
	lcd_draw_font_char(109, 50, &monospac821BT_11ptFontInfo, 'I', WHITE, BLACK);

	lcd_draw_font_string(50, 50, &monospac821BT_11ptFontInfo, "Start Machine", WHITE, BLACK);

	do {} while (loop);

	return 0;
}
