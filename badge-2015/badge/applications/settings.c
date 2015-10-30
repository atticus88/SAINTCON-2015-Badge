#include "settings.h"



void name_preview(uint8_t config) {
    draw_background();

    char attendee_name[64];
    char attendee_fname[AT45DBX_SECTOR_SIZE];
    char attendee_lname[AT45DBX_SECTOR_SIZE];
    char attendee_handle[AT45DBX_SECTOR_SIZE];
    char attendee_company[AT45DBX_SECTOR_SIZE];

    at45dbx_read_sector_open(FNAME_SECTOR);
    at45dbx_read_sector_to_ram(attendee_fname);
    at45dbx_read_close();

    at45dbx_read_sector_open(LNAME_SECTOR);
    at45dbx_read_sector_to_ram(attendee_lname);
    at45dbx_read_close();

    at45dbx_read_sector_open(HANDLE_SECTOR);
    at45dbx_read_sector_to_ram(attendee_handle);
    at45dbx_read_close();

     at45dbx_read_sector_open(ORG_SECTOR);
    at45dbx_read_sector_to_ram(attendee_company);
    at45dbx_read_close();

    snprintf(attendee_name, sizeof(attendee_name), "%s %s", attendee_fname, attendee_lname);
    uint8_t disp_name[160];
    uint8_t numlines = word_wrap(&disp_name, attendee_name, 17);

    uint8_t disp_org[160];
    uint8_t orglines = word_wrap(&disp_org, attendee_company, 23);

    switch (config) {
        case 0:
            gfx_draw_string_aligned(disp_name, gfx_get_width() / 2, 10, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            gfx_draw_string_aligned(attendee_handle, gfx_get_width() / 2, 50 + (numlines * 20) , &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            gfx_draw_string_aligned(disp_org, gfx_get_width() / 2, 200 - (orglines* 24), &medium_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            break;
        case 1:
            gfx_draw_string_aligned(attendee_handle, gfx_get_width() / 2, 10, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            gfx_draw_string_aligned(attendee_name, gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            gfx_draw_string_aligned(disp_org, gfx_get_width() / 2, 200 - (orglines* 24), &medium_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
             break;
        case 2:
            gfx_draw_string_aligned(disp_name, gfx_get_width() / 2, 10, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            gfx_draw_string_aligned(attendee_handle, gfx_get_width() / 2, 50 + (numlines * 20) , &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            break;
        case 3:
            gfx_draw_string_aligned(attendee_handle, gfx_get_width() / 2, 10, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            gfx_draw_string_aligned(attendee_name, gfx_get_width() / 2, 50, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            break;
        case 4:
            if (attendee_handle[1] != 0x00) {
                gfx_draw_string_aligned(attendee_handle, gfx_get_width() / 2, 10, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            } else {
                gfx_draw_string_aligned(disp_name, gfx_get_width() / 2, 10, &large_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);
            }
            break;
    }
    if(config != 0) {
        gfx_draw_filled_triangle(20,  gfx_get_height()/2 - 30, 20,  gfx_get_height()/2 - 10, 10,  gfx_get_height()/2 -20, GFX_COLOR_WHITE);
    }
    if (config != 4) {
        gfx_draw_filled_triangle(300, gfx_get_height()/2 - 30, 300, gfx_get_height()/2 - 10, 310, gfx_get_height()/2 -20, GFX_COLOR_WHITE);
    }
}



void settings_application() {

    uint8_t num = 4;

    at45dbx_read_byte_open(0x0001);
    int selected_index = at45dbx_read_byte();
    at45dbx_read_close();

    name_preview(selected_index);

	struct keyboard_event input;
     while(mma8451_orientation() != 6) {
        esp8266_check_buffer();
        keyboard_get_key_state(&input);
        if (input.type == KEYBOARD_RELEASE) {
            if (input.keycode == KEYBOARD_B) {
                break;
            } else if (input.keycode == KEYBOARD_A) {

                at45dbx_write_byte_open(0x0000);
                at45dbx_write_byte(0x01);
                at45dbx_write_close();

                at45dbx_write_byte_open(0x0001);
                at45dbx_write_byte(selected_index);
                at45dbx_write_close();

                gfx_draw_filled_circle(gfx_get_width() / 2, gfx_get_height()/2, 30, GFX_COLOR_GREEN, GFX_WHOLE);
                gfx_draw_string_aligned("SAVED", gfx_get_width() / 2,  gfx_get_height()/2-9, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_BLACK, TEXT_POS_CENTER_X, TEXT_ALIGN_CENTER);


            } else if (input.keycode == KEYBOARD_LEFT) {
                selected_index--;
                if (selected_index < 0) {
                    selected_index = 0;
                }
                name_preview(selected_index);
            } else if (input.keycode == KEYBOARD_RIGHT) {
                selected_index++;
                if (selected_index > num) {
                    selected_index = num;
                }
               name_preview(selected_index);
            }
        }
        if(mma8451_clear_interrupt() && is_low_power()) {
            exit_low_power();
        }
    }
}