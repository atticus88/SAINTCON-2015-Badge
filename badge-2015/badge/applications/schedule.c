#include "schedule.h"

int event_index = 0;
int event_track = 0;

void draw_time() {
    unsigned long ts = rtc_get_time();
    struct calendar_date rtc_date;
    uint8_t hour[] = {12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    // might need to build in something for daylight savings time
    calendar_timestamp_to_date_tz(ts, -6, 0, &rtc_date);
    char string_buf[15];

    snprintf(string_buf, sizeof(string_buf),"%d:%.2d", hour[rtc_date.hour], rtc_date.minute);
    gfx_draw_string_aligned(string_buf, gfx_get_width()-35, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_CENTER_X, TEXT_ALIGN_LEFT);
}

void draw_button_hints() {
    gfx_draw_filled_triangle((gfx_get_width()/2) - 30, 225, (gfx_get_width()/2) - 10, 225, (gfx_get_width()/2) - 20, 225-10, GFX_COLOR_WHITE);
    gfx_draw_filled_triangle((gfx_get_width()/2) + 10, 215, (gfx_get_width()/2) + 30, 215, (gfx_get_width()/2) + 20, 215+10, GFX_COLOR_WHITE);
    gfx_draw_filled_triangle(20,  gfx_get_height() - 30, 20,  gfx_get_height() - 10, 10,  gfx_get_height()-20, GFX_COLOR_WHITE);
    gfx_draw_filled_triangle(300, gfx_get_height() - 30, 300, gfx_get_height() - 10, 310, gfx_get_height()-20, GFX_COLOR_WHITE);
}

void draw_event() {
    draw_background();
    draw_time();
    gfx_draw_filled_rect(5, 26, 310, 182, GFX_COLOR(8, 8, 8));
    draw_button_hints();

    switch(event_track) {
        case 0:
            gfx_draw_string_aligned("Schedule - KEYNOTES",    11, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_YELLOW, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
            break;
        case 1:
            gfx_draw_string_aligned("Schedule - TRACK 1",    11, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_YELLOW, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
            break;
        case 2:
            gfx_draw_string_aligned("Schedule - TRACK 2",    11, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_YELLOW, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
            break;
        case 3:
            gfx_draw_string_aligned("Schedule - TRACK 3",    11, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_YELLOW, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
            break;
        case 4:
            gfx_draw_string_aligned("Schedule - TRACK 4",    11, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_YELLOW, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
            break;
        case 5:
            gfx_draw_string_aligned("Schedule - TRACK 5",    11, 2, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_YELLOW, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
            break;
    }
    
    uint16_t keynote = 0x0100;
    uint16_t track1 = 0x0200;
    uint16_t track2 = 0x0300;
    uint16_t track3 = 0x0400;
    uint16_t track4 = 0x0500;
    uint16_t track5 = 0x0600;

    uint16_t addresses[] = {keynote, track1, track2, track3, track4, track5};
    //uint16_t max_event[] = {5, 22, 22, 15, 23};

    uint8_t ram_buf[AT45DBX_SECTOR_SIZE];
    at45dbx_read_sector_open(addresses[event_track] + event_index);
    at45dbx_read_sector_to_ram(ram_buf);
    at45dbx_read_close();

    char *array[6];
    uint8_t i = 0;
    array[i] = strtok(ram_buf,";");
    while(array[i] != NULL) {
        array[++i] = strtok(NULL, ";");
    }

    char *title[256];
    uint8_t a = word_wrap(&title, array[0], 30);

    gfx_draw_string_aligned(title, 11, 27, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

    char event_time[36];
    snprintf(event_time, sizeof(event_time),"%s - %s", array[1], array[2]);
        
    char *names[256];
    uint8_t n = word_wrap(&names, array[3], 33);

        gfx_draw_string_aligned(names, 11, 60+(a*20), &small_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_RED, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);

        gfx_draw_string_aligned(array[4], 11, 85+(a*20)+(n*20), &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_YELLOW, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        gfx_draw_string_aligned(event_time, 11, 100+(a*20)+(n*20), &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
        
        
    // }
}

void schedule_application() {
    unsigned long now = rtc_get_time();

    if (now < 1445990399) {
        // day 1

    } else if (now > 1445990399 && now < 1446076799) {
        // day 2

    } else if (now > 1446076799 && now < 1446163199) {
        // day 3

    } else {
        // day 4

    }

    uint16_t max_event[] = {5, 26, 25, 18, 26, 13};
    
    
    //write_data();
	//gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
    draw_background();
    //gfx_draw_filled_rect(0, 0, 320, 182, GFX_COLOR(20, 20, 20));

    draw_time();
    // gfx_draw_string_aligned("Schedule - Keynotes",    11, 2, &sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    // gfx_draw_string_aligned("Schedule - Track 1",    11, 2, &sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    // gfx_draw_string_aligned("Schedule - Track 2",    11, 2, &sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    // gfx_draw_string_aligned("Schedule - Track 3",    11, 2, &sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
    // gfx_draw_string_aligned("Schedule - Track 4",    11, 2, &sysfont, GFX_COLOR_BLACK, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);






   
    event_index = 0;
    event_track = 0;
    

    draw_event();



    // Presentors
    // Location and time
    // Description

	struct keyboard_event input;
    while(mma8451_orientation() != 6) {
        esp8266_check_buffer();

        keyboard_get_key_state(&input);
        if (input.type == KEYBOARD_RELEASE) {
            if (input.keycode == KEYBOARD_B) {
                break;
            } else if (input.keycode == KEYBOARD_A) {
               
            } else if (input.keycode == KEYBOARD_UP) {
               event_index--;
               if (event_index < 0) {
                    event_index = 0;
               }
               draw_event();
            } else if (input.keycode == KEYBOARD_DOWN) {
               event_index++;
               if (event_index > max_event[event_track]) {
                    event_index = max_event[event_track];
               }
               draw_event();
            } else if (input.keycode == KEYBOARD_RIGHT) {
               event_index = 0;
               event_track++;
               if (event_track > 5) {
                    event_track = 0;
               }
               draw_event();
            } else if (input.keycode == KEYBOARD_LEFT) {
               event_index = 0;
               event_track--;
                if (event_track < 0) {
                    event_track = 5;
               }
               draw_event();
            }
        }
        if(mma8451_clear_interrupt() && is_low_power()) {
            exit_low_power();
        }
    }
}


// struct event {
//     char *title;
//     char *presentor;
//     char *location;
//     char *description;
//     unsigned long start;
//     unsigned long end;
// };

// struct event events_track1[8];

// uint16_t event_index = 0;


// void scrolling_test() {
//     events_track1[0].title = "Soemthing Awesome 1";
//     events_track1[0].presentor = "Klint Holmes";
//     events_track1[0].location = "UB230";
//     events_track1[0].description = "This is a class on how to use a bus\npirate.";
//     events_track1[0].start = 1440478623;
//     events_track1[0].end = 1440479623;
//     events_track1[1].title = "Soemthing Awesome 2";
//     events_track1[1].presentor = "Klint Holmes";
//     events_track1[1].location = "UB231";
//     events_track1[1].description = "This is a class on how to use a bus\npirate.";
//     events_track1[1].start = 1440478623;
//     events_track1[1].end = 1440479623;
//     events_track1[2].title = "Soemthing Awesome 3";
//     events_track1[2].presentor = "Klint Holmes";
//     events_track1[2].location = "UB230";
//     events_track1[2].description = "This is a class on how to use a bus\npirate.";
//     events_track1[2].start = 1440478623;
//     events_track1[2].end = 1440479623;
//     events_track1[3].title = "Soemthing Awesome 4";
//     events_track1[3].presentor = "Klint Holmes";
//     events_track1[3].location = "UB230";
//     events_track1[3].description = "This is a class on how to use a bus\npirate.";
//     events_track1[3].start = 1440478623;
//     events_track1[3].end = 1440479623;
//     events_track1[4].title = "Soemthing Awesome 5";
//     events_track1[4].presentor = "Klint Holmes";
//     events_track1[4].location = "UB230";
//     events_track1[4].description = "This is a class on how to use a bus\npirate.";
//     events_track1[4].start = 1440478623;
//     events_track1[4].end = 1440479623;
//     events_track1[5].title = "Soemthing Awesome 6";
//     events_track1[5].presentor = "Klint Holmes";
//     events_track1[5].location = "UB230";
//     events_track1[5].description = "This is a class on how to use a bus\npirate.";
//     events_track1[5].start = 1440478623;
//     events_track1[5].end = 1440479623;
//     events_track1[6].title = "Soemthing Awesome 7";
//     events_track1[6].presentor = "Klint Holmes";
//     events_track1[6].location = "UB230";
//     events_track1[6].description = "This is a class on how to use a bus\npirate.";
//     events_track1[6].start = 1440478623;
//     events_track1[6].end = 1440479623;

//     irqflags_t flags = cpu_irq_save();
//     gfx_draw_filled_rect(0, 0, gfx_get_width(), gfx_get_height(), GFX_COLOR_BLACK);
//     gfx_draw_string(events_track1[event_index].title, 4, 4, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE);
//     //gfx_draw_string_aligned(e.title, 4, 4, &sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
//     gfx_draw_string_aligned(events_track1[event_index].presentor, 4, 24, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
//     gfx_draw_string_aligned(events_track1[event_index].location, 4, 44, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
//     gfx_draw_string_aligned(events_track1[event_index].description, 0, 60, &tiny_sysfont, GFX_COLOR_TRANSPARENT, GFX_COLOR_WHITE, TEXT_POS_LEFT, TEXT_ALIGN_LEFT);
//     cpu_irq_restore(flags);
//     event_index++;
// }
