#include "asf.h"
#include "rtc32.h"
#include "esp8266.h"

void powermgmt_init(unsigned long ts);
unsigned long time_sleep(void);
unsigned long get_time_sleep(void);
unsigned long get_time_awake(void);
void enter_low_power(void);
void exit_low_power(void);
bool is_low_power(void);
