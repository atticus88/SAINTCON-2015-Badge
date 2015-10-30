/**
* SaintCON Badge 2015 
* 
*
*
*
*
**/

#include <board.h>
#include <sysclk.h>
#include <stdio.h>
#include <string.h>
#include "asf.h"
#include "mma8451.h"
#include "max1704x.h"
#include "adc.h"
#include "powermgmt.h"
#include "adc_sensors.h"
#include "ntc_sensor.h"
#include "keyboard.h"
#include "tsl2561t.h"
#include "twi_master.h"
#include "at45dbx.h"
#include "esp8266.h"
#include "calendar.h"
#include "rtc32.h"
#include "tc.h"
#include "irda.h"
#include "pwm.h"
#include "xbootapi.h"
#include "sha1.h"
#include "buzzer.h"

/* Include applicaitons */
#include "schedule.h"
#include "credits.h"
#include "hackerchallenge.h"
#include "location.h"
#include "game.h"
#include "network.h"
#include "settings.h"
#include "battery.h"
#include "notifications.h"
/* Include bitmaps */
//#include "settings.h"
//#include "shild.h"

/* Definitions */
#define TARGET_SECTOR               0x00002
#define GFX_COLOR_LG_GRAY           GFX_COLOR(200, 200, 200)
#define GFX_COLOR_BOOT_GRAY         GFX_COLOR(96, 96, 96)
#define GFX_COLOR_SC_ORANGE			GFX_COLOR(200, 101, 18)
//#define GFX_COLOR_SC_ORANGE			GFX_COLOR(254, 154, 7)
#define FIRST_POSSIBLE_TIMESTAMP    1440478623
#define MENU_ORIENTATION            0
#define NAME_ORIENTATION            3
#define ICON_WIDTH                  75
#define ICON_HEIGHT                 75
#define ICON_PADDING                20  



#define ESP_FLASH_ADDRESS 			0x16B4
#define BADGE_INFO_ADDRESS			0x0000


/* Method definitions */
void draw_battery_level(uint8_t lvl);
void menu_mode(void);
void name_mode(void); 
void application_menu(void);

/* Power managment */
void enter_low_power(void);
void exit_low_power(void);

static void sleep_alarm(void);
// static void my_callback(void);

// static void start_buzz(uint16_t tone);
// static void stop_buzz(void);

void draw_icons(void);
void draw_application_menu(void);

void upgrade_firmware(void);


bool badge_registerd(void);
//void scrolling_test(void);
void update_badge_data(void);

