#include "irda.h"


void irda_init(void) {

    // Setup Timer for IrDA RX
    tc_enable(&TCC1);
    tc_set_overflow_interrupt_callback(&TCC1, irda_decoder);
    tc_set_wgm(&TCC1, TC_WG_NORMAL);
    tc_write_period(&TCC1, 3100);
    tc_set_overflow_interrupt_level(&TCC1, TC_INT_LVL_LO);
    tc_write_clock_source(&TCC1, TC_CLKSEL_DIV1_gc);
    
    //  Setup PWM for IrDA TX
    
}

int  MATCH       (int measured, int desired) {
    return ((measured >= TICKS_LOW(desired)) && (measured <= TICKS_HIGH(desired)));
}
int  MATCH_MARK  (int measured_ticks, int desired_us) {
    return ((measured_ticks >= TICKS_LOW (desired_us + MARK_EXCESS)) && (measured_ticks <= TICKS_HIGH(desired_us + MARK_EXCESS)));
}
int  MATCH_SPACE (int measured_ticks, int desired_us) {
    return ((measured_ticks >= TICKS_LOW (desired_us - MARK_EXCESS)) && (measured_ticks <= TICKS_HIGH(desired_us - MARK_EXCESS)));
}

void mark(uint16_t time) {
    //LED_On(LED0);
    pwm_set_duty_cycle_percent(&pwm_cfg, 50);
    
    if (time > 0) { 
        delay_us(time /2);
    }
    pwm_set_duty_cycle_percent(&pwm_cfg, 0);
    //pwm_stop(&pwm_cfg);
    //pwm_timer_reset(&pwm_cfg);
    //ioport_set_pin_level(IRTX, false);
}

void space(uint16_t time) {
    pwm_set_duty_cycle_percent(&pwm_cfg, 0);
    if (time > 0) { 
        delay_us(time /2 );
    }
    //ioport_set_pin_level(IRTX, false);
    //pwm_timer_reset(&pwm_cfg);
}

void irda_send(uint32_t data, uint8_t nbits) {
    pwm_init(&pwm_cfg, PWM_TCC0, PWM_CH_D, 38000);
    pwm_start(&pwm_cfg, 0);
    // stop listening when send
    //LED_Toggle(LED0);

    //tc_disable(&TCC1);
    // Header
   // irqflags_t flags = cpu_irq_save();
    mark(SONY_HDR_MARK);
    space(SONY_HDR_SPACE);

    // Data
    for (unsigned long  mask = 1UL << (nbits - 1);  mask;  mask >>= 1) {
        if (data & mask) {
            mark(SONY_ONE_MARK);
            space(SONY_HDR_SPACE);
        } else {
            mark(SONY_ZERO_MARK);
            space(SONY_HDR_SPACE);
        }
    }

    pwm_set_duty_cycle_percent(&pwm_cfg, 0);
    pwm_disable(&pwm_cfg);
}

void irda_decoder(void) {
    //LED_On(LED0);
    //irqflags_t flags = cpu_irq_save();
    bool irdata = ioport_get_pin_level(IRRX);
    //irdata = !irdata;
    irparams.timer++;
    if (irparams.rawlen >= 101) {
        irparams.rcvstate = STATE_OVERFLOW;
    }

    switch(irparams.rcvstate) {
        case STATE_IDLE:
            if (!irdata) {
                if (irparams.timer < 100) {
                    irparams.timer = 0;
                } else {
                    irparams.overflow                   = false;
                    irparams.rawlen                     = 0;
                    irparams.rawbuf[irparams.rawlen++]  = irparams.timer;
                    irparams.timer                      = 0;
                    irparams.rcvstate                   = STATE_MARK;
                }
            }
            break;
        case STATE_MARK:
            if (irdata) {
                irparams.rawbuf[irparams.rawlen++]      = irparams.timer;
                irparams.timer                          = 0;
                irparams.rcvstate                       = STATE_SPACE;
            }
            break;
        case STATE_SPACE:
            if (!irdata) {
                irparams.rawbuf[irparams.rawlen++] = irparams.timer;
                irparams.timer                     = 0;
                irparams.rcvstate                  = STATE_MARK;
            } else if (irparams.timer > 100) {
                irparams.rcvstate = STATE_STOP;
            }
            break;
        case STATE_STOP:
            if (!irdata) {
                irparams.timer = 0;
            }
            break;
        case STATE_OVERFLOW:
            irparams.overflow = true;
            irparams.rcvstate = STATE_STOP;
            break;
    }
    //LED_Off(LED0);
    // ioport_set_pin_level(LED0, irdata);
    //cpu_irq_restore(flags);
    //decode();
}

int compare (unsigned int oldval,  unsigned int newval) {
    if      (newval < oldval * .8)  return 0 ;
    else if (oldval < newval * .8)  return 2 ;
    else                            return 1 ;
}

bool decode(decode_results *results) {

    results->rawbuf   = irparams.rawbuf;
    results->rawlen   = irparams.rawlen;

    results->overflow = irparams.overflow;

    long  data   = 0;
    int   offset = 0;  // Dont skip first space, check its size

    if (irparams.rawlen < (2 * SONY_BITS) + 2)  return false ;

    // Some Sony's deliver repeats fast after first
    // unfortunately can't spot difference from of repeat from two fast clicks
    if (results->rawbuf[offset] < SONY_DOUBLE_SPACE_USECS - 250) { // seems to get stuck in here but still working on badge test code? 
        // Serial.print("IR Gap found: ");
        results->bits = 0;
        results->value = REPEAT;
        results->decode_type = SONY;

        return true;
    }
    offset++;

    // Initial mark
    if (!MATCH_MARK(results->rawbuf[offset++], SONY_HDR_MARK))  return false ;

    while (offset + 1 < irparams.rawlen) {
        if (!MATCH_SPACE(results->rawbuf[offset++], SONY_HDR_SPACE))  break ;

        if      (MATCH_MARK(results->rawbuf[offset], SONY_ONE_MARK))   data = (data << 1) | 1 ;
        else if (MATCH_MARK(results->rawbuf[offset], SONY_ZERO_MARK))  data = (data << 1) | 0 ;
        else                                                           return false ;
        offset++;
    }

    // Success
    results->bits = (offset - 1) / 2;
    if (results->bits < 12) {
        results->bits = 0;
        return false;
    }
    results->value       = data;
    results->decode_type = SONY;
    return true;



    // //// RAW

    // long  hash = FNV_BASIS_32;

    // // Require at least 6 samples to prevent triggering on noise
    // if (results->rawlen < 6)  return false ;

    // for (int i = 1;  (i + 2) < results->rawlen;  i++) {
    //     int value =  compare(results->rawbuf[i], results->rawbuf[i+2]);
    //     // Add value into the hash
    //     hash = (hash * FNV_PRIME_32) ^ value;
    // }

    // results->value       = hash;
    // results->bits        = 32;
    // results->decode_type = UNKNOWN;

    // return true;
}