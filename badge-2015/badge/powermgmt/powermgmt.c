#include "powermgmt.h"

bool low_power = false;
bool did_sleep = false;
unsigned long  awake_ts = 0;
unsigned long  sleep_ts = 0;
unsigned long awake = 0;
unsigned long sleep = 0;

void powermgmt_init(unsigned long ts) {
	awake_ts = ts;
}

void enter_low_power(void) {
	if (!low_power) {
    	ili9341_backlight_off();
    	ili9341_enter_standby();
    	get_time_awake();
    	low_power = true;
    	did_sleep = true;
    	sleep_ts = rtc_get_time();
	}
 }

void exit_low_power(void) {
    ili9341_exit_standby();
    ili9341_backlight_on();
    esp8266_exit_standby();
    low_power = false;
    awake_ts = rtc_get_time();
    time_sleep();
    //LED_Toggle(LED0);

    //time_awake();
    esp8266_exit_standby();
}

uint32_t time_sleep() {
	if (sleep_ts != 0) {
		sleep += awake_ts - sleep_ts;
	}
	return sleep;
}

unsigned long get_time_sleep(){
	return sleep;
}


unsigned long get_time_awake() {
	unsigned long tmp = rtc_get_time();
	awake += tmp - awake_ts;
	awake_ts = tmp;
	return awake;
	// tmp = tmp - awake_ts;
	// awake_ts = tmp;
	// if (did_sleep) {
	// 	did_sleep = false;
	// 	awake += tmp - sleep;
	// } else {
	// 	awake += tmp;
	// }
	// return awake;
}

bool is_low_power(void) {
	return low_power;
}