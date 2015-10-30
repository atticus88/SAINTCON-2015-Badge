/**
 * \file
 *
 * \brief Keyboard driver
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
#include "asf.h"
#include "xmega_a3bu_xplained.h"
#include "keyboard.h"
#include "udi_hid_kbd.h"

uint8_t konami_index = 0;
uint8_t konami_pattern[] = {KEYBOARD_UP, KEYBOARD_UP, KEYBOARD_DOWN, KEYBOARD_DOWN, KEYBOARD_LEFT, KEYBOARD_RIGHT, KEYBOARD_LEFT, KEYBOARD_RIGHT, KEYBOARD_B, KEYBOARD_A, KEYBOARD_START };

bool konami_checker(uint16_t button) {
    if (button == konami_pattern[konami_index]) {
        konami_index++;
        if (konami_index == sizeof(konami_pattern)) {
            konami_index = 0;
            return true;
        }
    } else {
        konami_index = 0;
    }
    return false;
}

static bool my_flag_autorize_keyboard_events = false;
bool my_callback_keyboard_enable(void)
{
   my_flag_autorize_keyboard_events = true;
   return true;
}

void my_callback_keyboard_disable(void)
{
   my_flag_autorize_keyboard_events = false;
}


/**
 * \brief Check the status of the keyboard
 *
 * \param keybuffer  a keyboard_event struct to store keyboard status
 */
void keyboard_get_key_state(struct keyboard_event *keybuffer)
{
	// Variable to hold the key mask
	static uint8_t key_state;
	char key;

	if ((gpio_pin_is_low(GPIO_PUSH_BUTTON_UP)) && !(key_state & KEYBOARD_UP_MASK)) {
                // Key pressed
                key_state |= KEYBOARD_UP_MASK;
                keybuffer->keycode = KEYBOARD_UP;
                keybuffer->type = KEYBOARD_PRESS;
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_down(HID_UP);
                }
        } else if ((gpio_pin_is_high(GPIO_PUSH_BUTTON_UP)) && (key_state & KEYBOARD_UP_MASK)) {
                // Key released
                key_state &= ~KEYBOARD_UP_MASK;
                keybuffer->keycode = KEYBOARD_UP;
                keybuffer->type = KEYBOARD_RELEASE;
                keybuffer->konami = konami_checker(KEYBOARD_UP);
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_up(HID_UP);
                }
        } else if ((gpio_pin_is_low(GPIO_PUSH_BUTTON_DOWN)) && !(key_state & KEYBOARD_DOWN_MASK)) {
                // Key pressed
                key_state |= KEYBOARD_DOWN_MASK;
                keybuffer->keycode = KEYBOARD_DOWN;
                keybuffer->type = KEYBOARD_PRESS;
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_down(HID_DOWN);
                }
        } else if ((gpio_pin_is_high(GPIO_PUSH_BUTTON_DOWN)) && (key_state & KEYBOARD_DOWN_MASK)) {
                // Key released
                key_state &= ~KEYBOARD_DOWN_MASK;
                keybuffer->keycode = KEYBOARD_DOWN;
                keybuffer->type = KEYBOARD_RELEASE;
                keybuffer->konami = konami_checker(KEYBOARD_DOWN);
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_up(HID_DOWN);
                }
        } else if ((gpio_pin_is_low(GPIO_PUSH_BUTTON_LEFT)) && !(key_state & KEYBOARD_LEFT_MASK)) {
                // Key pressed
                key_state |= KEYBOARD_LEFT_MASK;
                keybuffer->keycode = KEYBOARD_LEFT;
                keybuffer->type = KEYBOARD_PRESS;
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_down(HID_LEFT);
                }
        } else if ((gpio_pin_is_high(GPIO_PUSH_BUTTON_LEFT)) && (key_state & KEYBOARD_LEFT_MASK)) {
                // Key released
                key_state &= ~KEYBOARD_LEFT_MASK;
                keybuffer->keycode = KEYBOARD_LEFT;
                keybuffer->type = KEYBOARD_RELEASE;
                keybuffer->konami = konami_checker(KEYBOARD_LEFT);
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_up(HID_LEFT);
                }
        } else if ((gpio_pin_is_low(GPIO_PUSH_BUTTON_RIGHT)) && !(key_state & KEYBOARD_RIGHT_MASK)) {
                // Key pressed
                key_state |= KEYBOARD_RIGHT_MASK;
                keybuffer->keycode = KEYBOARD_RIGHT;
                keybuffer->type = KEYBOARD_PRESS;
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_down(HID_RIGHT);
                }
        } else if ((gpio_pin_is_high(GPIO_PUSH_BUTTON_RIGHT)) && (key_state & KEYBOARD_RIGHT_MASK)) {
                // Key released
                key_state &= ~KEYBOARD_RIGHT_MASK;
                keybuffer->keycode = KEYBOARD_RIGHT;
                keybuffer->type = KEYBOARD_RELEASE;
                keybuffer->konami = konami_checker(KEYBOARD_RIGHT);
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_up(HID_RIGHT);
                }
        } else if ((gpio_pin_is_low(GPIO_PUSH_BUTTON_START)) && !(key_state & KEYBOARD_START_MASK)) {
                // Key pressed
                key_state |= KEYBOARD_START_MASK;
                keybuffer->keycode = KEYBOARD_START;
                keybuffer->type = KEYBOARD_PRESS;
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_down(HID_ENTER);
                }
        } else if ((gpio_pin_is_high(GPIO_PUSH_BUTTON_START)) && (key_state & KEYBOARD_START_MASK)) {
                // Key released
                key_state &= ~KEYBOARD_START_MASK;
                keybuffer->keycode = KEYBOARD_START;
                keybuffer->type = KEYBOARD_RELEASE;
                keybuffer->konami = konami_checker(KEYBOARD_START);
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_up(HID_ENTER);
                }

        } else if ((gpio_pin_is_low(GPIO_PUSH_BUTTON_SELECT)) && !(key_state & KEYBOARD_SELECT_MASK)) {
                // Key pressed
                key_state |= KEYBOARD_SELECT_MASK;
                keybuffer->keycode = KEYBOARD_SELECT;
                keybuffer->type = KEYBOARD_PRESS;
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_down(HID_SPACEBAR);
                }
        } else if ((gpio_pin_is_high(GPIO_PUSH_BUTTON_SELECT)) && (key_state & KEYBOARD_SELECT_MASK)) {
                // Key released
                key_state &= ~KEYBOARD_SELECT_MASK;
                keybuffer->keycode = KEYBOARD_SELECT;
                keybuffer->type = KEYBOARD_RELEASE;
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_up(HID_SPACEBAR);
                }
        } else if ((gpio_pin_is_low(GPIO_PUSH_BUTTON_A)) && !(key_state & KEYBOARD_A_MASK)) {
                // Key pressed
                key_state |= KEYBOARD_A_MASK;
                keybuffer->keycode = KEYBOARD_A;
                keybuffer->type = KEYBOARD_PRESS;
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_down(HID_A);
                }
        } else if ((gpio_pin_is_high(GPIO_PUSH_BUTTON_A)) && (key_state & KEYBOARD_A_MASK)) {
                // Key released
                key_state &= ~KEYBOARD_A_MASK;
                keybuffer->keycode = KEYBOARD_A;
                keybuffer->type = KEYBOARD_RELEASE;
                keybuffer->konami = konami_checker(KEYBOARD_A);
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_up(HID_A);
                }
        } else if ((gpio_pin_is_low(GPIO_PUSH_BUTTON_B)) && !(key_state & KEYBOARD_B_MASK)) {
                // Key pressed
                key_state |= KEYBOARD_B_MASK;
                keybuffer->keycode = KEYBOARD_B;
                keybuffer->type = KEYBOARD_PRESS;
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_down(HID_B);
                }
        } else if ((gpio_pin_is_high(GPIO_PUSH_BUTTON_B)) && (key_state & KEYBOARD_B_MASK)) {
                // Key released
                key_state &= ~KEYBOARD_B_MASK;
                keybuffer->keycode = KEYBOARD_B;
                keybuffer->type = KEYBOARD_RELEASE;
                keybuffer->konami = konami_checker(KEYBOARD_B);
                if (my_flag_autorize_keyboard_events) {
                    udi_hid_kbd_up(HID_B);
                }
        // } else if ((key = cdc_getkey()) != KEYBOARD_NO_KEY) {
        //         keybuffer->keycode = key;
        //         keybuffer->type = KEYBOARD_RELEASE;
        } else {
		keybuffer->keycode = KEYBOARD_NO_KEY;
		keybuffer->type = KEYBOARD_NO_EVENT;
	}
}

/*  KEYBOARD CODE
        while (true) {
        keyboard_get_key_state(&input);
        if (input.type == KEYBOARD_RELEASE) {
                        if (input.keycode == KEYBOARD_B) {
                                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                        gfx_draw_string_aligned("B", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
                        } else if (input.keycode == KEYBOARD_A) {
                                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                        gfx_draw_string_aligned("A", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);            
                        } else if (input.keycode == KEYBOARD_SELECT) {
                                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                        gfx_draw_string_aligned("SELECT", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);       
                        } else if (input.keycode == KEYBOARD_START) {
                                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                        gfx_draw_string_aligned("START", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);        
                        } else if (input.keycode == KEYBOARD_UP) {
                                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                        gfx_draw_string_aligned("UP", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);   
                        } else if (input.keycode == KEYBOARD_DOWN) {
                                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                        gfx_draw_string_aligned("DOWN", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT); 
                        } else if (input.keycode == KEYBOARD_LEFT) {
                                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                        gfx_draw_string_aligned("LEFT", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT); 
                        } else if (input.keycode == KEYBOARD_RIGHT) {
                                gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
                        gfx_draw_string_aligned("RIGHT", gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);        
                        }
        }
    }
        */
