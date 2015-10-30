/**
 * \file
 *
 * \brief Graphic service settings for the SDT028ATFT panel using the ILI9341
 * display controller
 *
 * This files includes the correct header files for the graphics service
 *
 * Copyright (c) 2014-2015 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */

/**
 * \ingroup gfx_ili9341_sdt028atft
 * @{
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include "gfx.h"
#include "gfx_ili9341_sdt028atft.h"
#include "ili9341.h"
#include "ili9341_regs.h"
#include <ctype.h>
#include <string.h>

gfx_coord_t gfx_height, gfx_width;
gfx_coord_t gfx_min_x, gfx_min_y;
gfx_coord_t gfx_max_x, gfx_max_y;

void gfx_ili9341_set_orientation(uint8_t flags)
{
	ili9341_set_orientation(flags);

	/* Switch width and height if XY is switched. */
	if ((flags & GFX_SWITCH_XY) != 0x00) {
		gfx_width = ILI9341_SWITCH_XY_WIDTH;
		gfx_height = ILI9341_SWITCH_XY_HEIGHT;
	} else {
		gfx_width = ILI9341_DEFAULT_WIDTH;
		gfx_height = ILI9341_DEFAULT_HEIGHT;
	}

#ifdef CONF_GFX_USE_CLIPPING
	/* Reset clipping region. */
	gfx_set_clipping(0, 0, gfx_width - 1, gfx_height - 1);
#endif
}

gfx_color_t gfx_ili9341_color(uint8_t r, uint8_t g, uint8_t b)
{
	return GFX_COLOR(r, g, b);
}

gfx_color_t gfx_ili9341_get_pixel(gfx_coord_t x, gfx_coord_t y)
{
	gfx_color_t color;

#ifdef CONF_GFX_USE_CLIPPING
	if ((x < gfx_min_x) || (x > gfx_max_x) ||
			(y < gfx_min_y) || (y > gfx_max_y)) {
		return GFX_COLOR_INVALID;
	}
#endif

	/* Set up draw area and read the three bytes of pixel data. */
	gfx_set_limits(x, y, x, y);
	color = ili9341_read_gram();

	return color;
}

void gfx_ili9341_draw_pixel(gfx_coord_t x, gfx_coord_t y, gfx_color_t color)
{
#ifdef CONF_GFX_USE_CLIPPING
	if ((x < gfx_min_x) || (x > gfx_max_x) ||
			(y < gfx_min_y) || (y > gfx_max_y)) {
		return;
	}
#endif

	/* Set up draw area and write the two bytes of pixel data. */
	gfx_set_limits(x, y, x, y);
	ili9341_write_gram(color);
}

void gfx_ili9341_draw_line_pixel(gfx_coord_t x, gfx_coord_t y,
		gfx_color_t color)
{
#ifdef CONF_GFX_USE_CLIPPING
	if ((x < gfx_min_x) || (x > gfx_max_x) ||
			(y < gfx_min_y) || (y > gfx_max_y)) {
		return;
	}
#endif

	/* Set up top left corner of area and write the two bytes of */
	/* pixel data.  Bottom left corner is already set to max_x/y. */
	gfx_set_top_left_limit(x, y);
	ili9341_write_gram(color);
}

void gfx_draw_filled_triangle( int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, gfx_color_t color) {
  int16_t a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }
  if (y1 > y2) {
    swap(y2, y1); swap(x2, x1);
  }
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    gfx_draw_horizontal_line(a, y0, b-a+1, color);
    return;
  }

  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1;
  int32_t
    sa   = 0,
    sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    gfx_draw_horizontal_line(a, y, b-a+1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    gfx_draw_horizontal_line(a, y, b-a+1, color);
  }
}

uint8_t word_wrap (char* buffer, char* string, int line_width) {
    uint8_t line_num = 0;
    int i = 0;
    int k, counter;
 
    while(i < strlen( string ) ) 
    {
        // copy string until the end of the line is reached
        for ( counter = 1; counter <= line_width; counter++ ) 
        {
            // check if end of string reached
            if ( i == strlen( string ) ) 
            {
                buffer[ i ] = 0;
                return line_num;
            }
            buffer[ i ] = string[ i ];
            // check for newlines embedded in the original input 
            // and reset the index
            if ( buffer[ i ] == '\n' )
            {
                line_num++;
                counter = 1; 
            }
            i++;
        }
        // check for whitespace
        if ( isspace( string[ i ] ) ) 
        {
            buffer[i] = '\n';
            line_num++;
            i++;
        } else {
            // check for nearest whitespace back in string
            for ( k = i; k > 0; k--) 
            {
                if ( isspace( string[ k ] ) ) 
                {
                    buffer[ k ] = '\n';
                    line_num++;
                    i = k + 1;
                    break;
                }
            }
        }
    }
    buffer[ i ] = 0;
    return line_num;
}

void draw_background(void) { // random texture background
    uint8_t s = 24;
    uint16_t mindex = 0; 
    // PASSWORD:CIUGLUWIEXIEPLAXIUKLEPQBHY
    //  280 bits on screen
    uint8_t message[] = { 0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,0,1,1,0,1,0,1,
                          0,0,1,1,0,1,0,1,0,1,1,1,0,1,0,0,1,1,1,1,0,1,0,1,0,0,1,0,
                          0,1,0,0,0,1,0,0,0,0,1,1,1,0,1,0,0,1,0,0,0,0,1,1,0,1,0,0,
                          1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,1,1,0,1,0,0,1,1,0,0,
                          0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,0,1,0,0,1,0,1,0,0,
                          0,1,0,1,0,1,0,1,1,0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,0,1,0,1,
                          0,1,0,1,0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,1,0,1,0,1,
                          1,0,0,0,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,1,
                          0,1,0,0,1,1,0,0,0,1,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,
                          0,0,0,1,0,1,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,1,1,0,0,1
                      };
    for (uint16_t y = 0; y < gfx_get_height(); y=y+s) {
        for (uint16_t x = 0; x < gfx_get_width(); x=x+s) {
            // uint8_t sq = rand() % 80;
            // uint8_t tr = rand() % 80;
            // gfx_draw_filled_rect(x, y, s, s, GFX_COLOR(sq, sq, sq));
            // gfx_draw_filled_triangle(x, y, x+s, y, x+s, y+s, GFX_COLOR(tr,tr,tr));

            if (message[mindex] == 1) {
                //uint8_t sq = 255;
                uint8_t sq = (rand() % 20) + 20;
                gfx_draw_filled_rect(x, y, s, s, GFX_COLOR(sq, sq, sq));
                mindex++;
            } else {
                //uint8_t sq = 0;
                uint8_t sq = rand() % 20;
                gfx_draw_filled_rect(x, y, s, s, GFX_COLOR(sq, sq, sq));
                mindex++;
            }
            if (message[mindex] == 1) {
                //uint8_t tr = 255;
                uint8_t tr = (rand() % 20) + 20;
                gfx_draw_filled_triangle(x, y, x+s, y, x+s, y+s, GFX_COLOR(tr,tr,tr));
                mindex++;
            } else {
                //uint8_t tr = 0;
                uint8_t tr = rand() % 20;
                gfx_draw_filled_triangle(x, y, x+s, y, x+s, y+s, GFX_COLOR(tr,tr,tr));
                mindex++;
            }
        }
    }
}

void gfx_ili9341_init(void)
{
	/* initialize globals */
	gfx_width = ILI9341_DEFAULT_WIDTH;
	gfx_height = ILI9341_DEFAULT_HEIGHT;

	ili9341_init();
	ili9341_backlight_on();

	/* Set clipping area to whole screen initially */
	gfx_set_clipping(0, 0, gfx_width, gfx_height);

	gfx_draw_filled_rect(0, 0, gfx_width, gfx_height,
			GFX_COLOR_BLACK);
}

/**
 *@}
 */
