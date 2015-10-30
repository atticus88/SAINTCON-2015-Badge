/**
 * \file
 *
 * \brief Graphical font support
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
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>

#include "conf_sysfont.h"

#include "gfx.h"
#include "sysfont.h"

/* Use macro from conf_sysfont.h to define font glyph data. */
SYSFONT_DEFINE_GLYPHS
SYSFONT_DEFINE_TINY_GLYPHS
SYSFONT_DEFINE_SMALL_GLYPHS
SYSFONT_DEFINE_MEDIUM_GLYPHS
SYSFONT_DEFINE_LARGE_GLYPHS
SYSFONT_DEFINE_SYMBOL_GLYPHS

/**
 * \brief Initialize a basic system font
 *
 * This initializes a basic system font globally usable by the application.
 */
struct font sysfont = {
	.type           = FONT_LOC_PROGMEM,
	.width          = SYSFONT_WIDTH,
	.height         = SYSFONT_HEIGHT,
	.first_char     = SYSFONT_FIRSTCHAR,
	.last_char      = SYSFONT_LASTCHAR,
	.data           = {
		.progmem        = sysfont_glyphs,
	},
};

struct font small_sysfont = {
	.type           = FONT_LOC_PROGMEM,
	.width          = SYSFONT_SMALL_WIDTH,
	.height         = SYSFONT_SMALL_HEIGHT,
	.first_char     = SYSFONT_FIRSTCHAR,
	.last_char      = SYSFONT_LASTCHAR,
	.data           = {
		.progmem        = sysfont_small_glyphs,
	},
};

struct font tiny_sysfont = {
	.type           = FONT_LOC_PROGMEM,
	.width          = SYSFONT_TINY_WIDTH,
	.height         = SYSFONT_TINY_HEIGHT,
	.first_char     = SYSFONT_FIRSTCHAR,
	.last_char      = SYSFONT_LASTCHAR,
	.data           = {
		.progmem        = sysfont_tiny_glyphs,
	},
};

struct font medium_sysfont = {
	.type           = FONT_LOC_PROGMEM,
	.width          = SYSFONT_MEDIUM_WIDTH,
	.height         = SYSFONT_MEDIUM_HEIGHT,
	.first_char     = SYSFONT_FIRSTCHAR,
	.last_char      = SYSFONT_LASTCHAR,
	.data           = {
		.progmem        = sysfont_medium_glyphs,
	},
};

struct font large_sysfont = {
	.type           = FONT_LOC_PROGMEM,
	.width          = SYSFONT_LARGE_WIDTH,
	.height         = SYSFONT_LARGE_HEIGHT,
	.first_char     = SYSFONT_FIRSTCHAR,
	.last_char      = SYSFONT_LASTCHAR,
	.data           = {
		.progmem        = sysfont_large_glyphs,
	},
};

struct font symbol_sysfont = {
	.type           = FONT_LOC_PROGMEM,
	.width          = SYSFONT_SYMBOL_WIDTH,
	.height         = SYSFONT_SYMBOL_HEIGHT,
	.first_char     = SYSFONT_FIRSTCHAR,
	.last_char      = '%',
	.data           = {
		.progmem        = sysfont_symbol_glyphs,
	},
};

/** @} */
