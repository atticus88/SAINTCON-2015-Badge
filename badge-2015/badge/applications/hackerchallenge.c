#include "hackerchallenge.h"

int selected_index = 0;

void draw_menu() {
    draw_background();
    uint8_t x = 40;
    uint8_t y = 210;
    uint8_t width = 240;
    gfx_draw_rect(x, y, width, 20, GFX_COLOR_WHITE);

    if (selected_index == 0) {
        gfx_draw_filled_rect(x, y, 120, 20, GFX_COLOR_WHITE);
        gfx_draw_string_aligned("My Rank", x+30, y-1, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned("Top 10", x+width/2+30, y-1, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    } else {
        gfx_draw_filled_rect(x+width/2, y, 120, 20, GFX_COLOR_WHITE);
        gfx_draw_string_aligned("My Rank", x+30, y-1, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned("Top 10", x+width/2+30, y-1, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    }

    if (selected_index == 0) {
        gfx_draw_string_aligned("Hackers Challenge Standings", gfx_get_width() / 2, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        if (strlen(esp_hcrank)) {
            char rank_string[128];
            snprintf(rank_string, sizeof(rank_string), "#%s - %s", esp_hcrank, esp_hcscore);
            gfx_draw_string_aligned(rank_string, gfx_get_width() / 2, 40, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        } else {

            uint8_t rank[AT45DBX_SECTOR_SIZE];
            at45dbx_read_sector_open(0x000A);
            at45dbx_read_sector_to_ram(rank);
            at45dbx_read_close();

            uint8_t score[AT45DBX_SECTOR_SIZE];
            at45dbx_read_sector_open(0x000B);
            at45dbx_read_sector_to_ram(score);
            at45dbx_read_close();

            if(rank[0] != 0x00 && score[0] != 0x00) {
                char rank_string[128];
                snprintf(rank_string, sizeof(rank_string), "#%s - %s", rank, score);
                gfx_draw_string_aligned(rank_string, gfx_get_width() / 2, 40, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
            } else {
                gfx_draw_string_aligned("No Data", gfx_get_width() / 2, 40, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
            }
        }
    } else {

        uint8_t topten[AT45DBX_SECTOR_SIZE];
        at45dbx_read_sector_open(0x000F);
        at45dbx_read_sector_to_ram(topten);
        at45dbx_read_close();

        char *array[12];
        uint8_t i = 0;
        array[i] = strtok(topten,",");
        while(array[i] != NULL) {
            array[++i] = strtok(NULL, ",");
        }


        // might become list of codes that badge has unlocked
        gfx_draw_string_aligned("Hackers Challenge Standings", gfx_get_width() / 2, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned(array[0], gfx_get_width() / 2, 30, &medium_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned(array[1], gfx_get_width() / 2, 52, &medium_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned(array[2], gfx_get_width() / 2, 75, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned(array[3], gfx_get_width() / 2, 90, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned(array[4], gfx_get_width() / 2, 105, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned(array[5], gfx_get_width() / 2, 120, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned(array[6], gfx_get_width() / 2, 135, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned(array[7], gfx_get_width() / 2, 150, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned(array[8], gfx_get_width() / 2, 165, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned(array[9], gfx_get_width() / 2, 180, &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
    }

}

uint16_t last_temp = 0;


float last_lux = 0.0;
void get_light(void) {
    char lux_string[16];
    float lux = tsl2561t_light();

    if (lux != last_lux) {
        dtostrf(lux, 4, 0, lux_string);
        gfx_draw_string_aligned(lux_string, 280, 216, &sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        last_lux = lux;
    }
}

void hackerchallenge_application() {
    draw_menu();
	//gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_RED);
	struct keyboard_event input;

   
    while(mma8451_orientation() != 6) {
        //get_temp();
        //get_light();
        esp8266_check_buffer();
        if(mma8451_clear_interrupt() && is_low_power()) {
            exit_low_power();
        }

        keyboard_get_key_state(&input);
        if (input.type == KEYBOARD_RELEASE) {
            if (input.keycode == KEYBOARD_B) {
                break;
            } else if (input.keycode == KEYBOARD_A) {
               
            } else if (input.keycode == KEYBOARD_LEFT) {
                selected_index--;
                if (selected_index < 0) {
                    selected_index = 0;
                }
                draw_menu();
            } else if (input.keycode == KEYBOARD_RIGHT) {
                selected_index++;
                if (selected_index > 1) {
                    selected_index = 1;
                }
                draw_menu();
            }
        }
    }
}
