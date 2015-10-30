#include "notifications.h"

uint16_t type_index = 0;
void show_messages() {
    gfx_draw_filled_rect(5, 26, 310, 182, GFX_COLOR(8, 8, 8));
    if (type_index == 0) {
        if (strlen(esp_pmsg)) {
            char disp_msg[160];
            word_wrap(&disp_msg, esp_pmsg, 32);
            gfx_draw_string_aligned(disp_msg, 10, 30, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        }
    } else {
        if (strlen(esp_bmsg)) {
            char disp_msg[160];
            word_wrap(&disp_msg, esp_bmsg, 32);
            gfx_draw_string_aligned(disp_msg, 10, 30, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        }
    }

}

//The quick brown fox jumped over the lazy dog, the quck brown fox jumped over the lazy dog, the quick brown fox jumped of the they lasy dog.


void note_draw_menu() {
    draw_background();
    uint8_t x = 40;
    uint8_t y = 210;
    uint8_t width = 240;
    gfx_draw_rect(x, y, width, 20, GFX_COLOR_WHITE);
    esp_received_pmsg = false;
    esp_received_bmsg = false;
    gfx_draw_string_aligned("Messages", gfx_get_width() / 2, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
    if (type_index == 0) {
        gfx_draw_filled_rect(x, y, 120, 20, GFX_COLOR_WHITE);
        gfx_draw_string_aligned("Private", x+30, y-1, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned("Broadcast", x+width/2+20, y-1, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    } else {
        gfx_draw_filled_rect(x+width/2, y, 120, 20, GFX_COLOR_WHITE);
        gfx_draw_string_aligned("Private", x+30, y-1, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned("Broadcast", x+width/2+20, y-1, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    }

    show_messages();
}



void notifications_application() {
    draw_background();
    note_draw_menu();

	struct keyboard_event input;
    while(mma8451_orientation() != 6) {
        esp8266_check_buffer();

        keyboard_get_key_state(&input);
        if (input.type == KEYBOARD_RELEASE) {
            if (input.keycode == KEYBOARD_B) {
                break;
            } else if (input.keycode == KEYBOARD_LEFT) {
                type_index--;
                if (type_index < 0) {
                    type_index = 0;
                }
                note_draw_menu();

            } else if (input.keycode == KEYBOARD_RIGHT) {
                type_index++;
                if (type_index > 1) {
                    type_index = 1;
                }
                note_draw_menu();
                
            }

        }
        if(mma8451_clear_interrupt() && is_low_power()) {
            exit_low_power();
        }
    }
}