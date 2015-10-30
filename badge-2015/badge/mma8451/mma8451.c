#include "mma8451.h"

typedef enum {
  MMA8451_RANGE_8_G           = 0b10,   // +/- 8g
  MMA8451_RANGE_4_G           = 0b01,   // +/- 4g
  MMA8451_RANGE_2_G           = 0b00    // +/- 2g (default value)
} mma8451_range_t;

void twi_init() {
    twi_master_options_t opt = {
        .speed = MMA8451_SPEED,
        .chip  = MMA8451_ADDR
    };

    twi_master_setup(MMA8451_MASTER, &opt);
}

void mma8451_init(void) {
        motion_int = false;
        lndprt_int = false;
        mma8451_write(0x2B, 0x40);
        while (mma8451_read(0x2B) & 0x40);

        //mma8451_read(0x0C);

        mma8451_write(0x2A, 0x18);
        mma8451_write(0x15, 0xF8);
        mma8451_write(0x17, 0x15);
        mma8451_write(0x18, 0x0A);

        mma8451_write(0x2D, 0x14);
        mma8451_write(0x2E, 0x04);
        // landscape/portart stuff
        
        // WAS WORKING
        mma8451_write(0x2B, 0x02);
        mma8451_write(0x11, 0x40);
        
        //mma8451_write(0x2D, 0x01);
        //mma8451_write(0x2D, 0x01);
        //mma8451_write(0x2E, 0x01);
        
        

        // motion detection
        // interrupt
        
        mma8451_write(0x2A, 0x01);
}

uint8_t mma8451_read(uint8_t reg) {
        uint8_t data_received[1];

        twi_package_t packet = {
                .addr[0]                = reg,
                .addr_length            = sizeof(uint8_t),
                .chip                   = MMA8451_ADDR,
                .buffer                 = data_received,
                .length                 = sizeof(data_received)
        };
        while (twi_master_read(MMA8451_MASTER, &packet) != TWI_SUCCESS);
        //twi_master_read(MMA8451_MASTER, &packet);
        return data_received[0];
}

void mma8451_write(uint8_t reg, uint8_t data) {
        uint8_t buffer[] = {data};
        twi_package_t packet  = {
                .addr[0]                = reg,
                .addr_length            = sizeof(uint8_t),
                .chip                   = MMA8451_ADDR,
                .buffer                 = (void *)buffer,
                .length                 = sizeof(buffer)
        };
        while (twi_master_write(MMA8451_MASTER, &packet) != TWI_SUCCESS);
        //twi_master_write(MMA8451_MASTER, &packet);
}

 bool mma8451_clear_interrupt(void) {
    bool status = false;
    if (motion_int == true || lndprt_int == true) {
        uint8_t source = mma8451_read(0x0C);
        if  (source == 0x04) {
            mma8451_read(0x16);
            status = true;
        } else if (source == 0x10) {
            lndprt_int = false;
            status = true;
        }
        motion_int = false;
    }
    return status;
}

uint8_t mma8451_orientation(void) {
        return mma8451_read(0x10) & 7;
}


ISR(PORTF_INT1_vect) {
    lndprt_int = true;
    move_counter = 0;
}

// I cannot get i2c interface to work inside of interrupt code
// motion interrupt handler
ISR(PORTF_INT0_vect) {
    motion_int = true;
    move_counter = 0;
    //rtc_set_alarm_relative(30); // wait 1/2 an hour before sleep mode in name mode
    //exit_low_power();
}