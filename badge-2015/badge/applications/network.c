#include "network.h"

void network_application() {
	draw_background();
    gfx_draw_filled_rect(5, 26, 310, 182, GFX_COLOR(20, 20, 20));

    if(!wifi_ready && wifi_error) {
        gfx_draw_string_aligned(SYMFONT_WIFI, gfx_get_width() / 2, 120, &symbol_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_RED, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
        gfx_draw_string_aligned("Not Connected", gfx_get_width() / 2, 155, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_RED, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    } else {
        gfx_draw_string_aligned(SYMFONT_WIFI, gfx_get_width() / 2, 120, &symbol_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_GREEN, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
        gfx_draw_string_aligned("Connected", gfx_get_width() / 2, 155, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_GREEN, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
    }

    uint8_t ram_buf[AT45DBX_SECTOR_SIZE];
    
    at45dbx_read_sector_open(0x0007);
    at45dbx_read_sector_to_ram(ram_buf);
    at45dbx_read_close();
    char mac_string[128];
    snprintf(mac_string, sizeof(mac_string), "MAC: %s", ram_buf);
    gfx_draw_string_aligned(mac_string, 11, 27, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    if (wifi_error) {
         gfx_draw_string_aligned(esp_error, 11, 47, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    }

	struct keyboard_event input;
    while(mma8451_orientation() != 6) {
        esp8266_check_buffer();

        keyboard_get_key_state(&input);
        if (input.type == KEYBOARD_RELEASE) {
            if (input.keycode == KEYBOARD_B) {
                break;
            }
        }
        if(mma8451_clear_interrupt() && is_low_power()) {
            exit_low_power();
        }
    }
}