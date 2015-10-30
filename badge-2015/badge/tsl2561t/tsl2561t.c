#include "tsl2561t.h"
#include "math.h"
#include "asf.h"

void tsl2561t_init(void) {
     tsl2561t_write(0x80, 0x03); 
     tsl2561t_write(0x81, 0x01);
     tsl2561t_write(0x86, 0x00);
     delay_ms(402);
}

uint8_t tsl2561t_read(uint8_t reg) {
        uint8_t data_received[1];

        twi_package_t packet = {
                .addr[0]                = reg,
                .addr_length            = sizeof(uint8_t),
                .chip                   = TSL2561T_ADDR,
                .buffer                 = data_received,
                .length                 = sizeof(data_received)
        };
        while (twi_master_read(TSL2561T_MASTER, &packet) != TWI_SUCCESS);
        //twi_master_read(MMA8451_MASTER, &packet);
        return data_received[0];
}

uint16_t tsl2561t_read_word(uint8_t reg) {
    uint16_t data_received[1];

        twi_package_t packet = {
                .addr[0]                = reg,
                .addr_length            = sizeof(uint16_t),
                .chip                   = TSL2561T_ADDR,
                .buffer                 = data_received,
                .length                 = sizeof(data_received)
        };
        while (twi_master_read(TSL2561T_MASTER, &packet) != TWI_SUCCESS);
        //twi_master_read(MMA8451_MASTER, &packet);
        return data_received[0];
}

void tsl2561t_write(uint8_t reg, uint8_t data) {
        uint8_t buffer[] = {data};
        twi_package_t packet  = {
                .addr[0]                = reg,
                .addr_length            = sizeof(uint8_t),
                .chip                   = TSL2561T_ADDR,
                .buffer                 = (void *)buffer,
                .length                 = sizeof(buffer)
        };
        while (twi_master_write(TSL2561T_MASTER, &packet) != TWI_SUCCESS);
        //twi_master_write(MMA8451_MASTER, &packet);
}

uint8_t tsl2561t_version(void) {
    return tsl2561t_read(0x0A) & 0xF; 
}

double tsl2561t_light(void) {

    // uint16_t d0 = tsl2561t_read_word(0x0C);
    // uint16_t d1 = tsl2561t_read_word(0x0E);

    uint8_t d0low = tsl2561t_read(0x8C);
    uint8_t d0high = tsl2561t_read(0x8D);
    uint16_t d1 = ((uint16_t)d0high << 8) | d0low;

    uint8_t d1low = tsl2561t_read(0x8E);
    uint8_t d1high = tsl2561t_read(0x8F);
    uint16_t d0 = ((uint16_t)d1high << 8) | d1low;

    
    //return 1.234;
    double ratio = 1.0;
    if (d1 != 0 ) {
        ratio = d0 / d1;
    }

    //return ratio;
    d0 *= (402.0/5);
    d1 *= (402.0/5);


    if (ratio < 0.5)
    {
        return 0.0304 * d0 - 0.062 * d0 * pow(ratio,1.4);
    }

    if (ratio < 0.61)
    {
        return 0.0224 * d0 - 0.031 * d1;
    }

    if (ratio < 0.80)
    {
        return 0.0128 * d0 - 0.0153 * d1;
    }

    if (ratio < 1.30)
    {
        return 0.00146 * d0 - 0.00112 * d1;
    }

    // if (ratio > 1.30)
    return 0.0;
}
