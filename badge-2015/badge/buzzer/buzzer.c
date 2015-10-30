#include "buzzer.h"

bool play = false;

void buzzer_toggle(void) {
	if (play) {
		//LED_Toggle(LED0);
    	LED_Toggle(BUZZER_PWM);
	}
}

void start_buzz(uint16_t tone) {
	tone = 500000  / tone;
    tc_enable(&TCD0);
    tc_set_overflow_interrupt_callback(&TCD0, buzzer_toggle);
    tc_set_wgm(&TCD0, TC_WG_NORMAL);
    tc_write_period(&TCD0, tone);
    tc_set_overflow_interrupt_level(&TCD0, TC_INT_LVL_LO);
    tc_write_clock_source(&TCD0, TC_CLKSEL_DIV64_gc);
    play = true;
} 

void stop_buzz(void) {
	//tc_set_overflow_interrupt_callback(&TCD0);
	//tc_write_period(&TCD0, 0);
	play = false;
    tc_disable(&TCD0);
}