#include "max1704x.h"

void twi_max1704x_init() {
    twi_master_options_t opt = {
        .speed = MAX1704X_SPEED,
        .chip  = MAX1704X_ADDR
    };

    twi_master_setup(MAX1704X_MASTER, &opt);
}

void max1704x_init(void) {

}

uint8_t max1704x_read(uint8_t reg) {
        uint8_t data_received[1];

        twi_package_t packet = {
                .addr[0]                = reg,
                .addr_length            = sizeof(uint8_t),
                .chip                   = MAX1704X_ADDR,
                .buffer                 = data_received,
                .length                 = sizeof(data_received)
        };
        while (twi_master_read(MAX1704X_MASTER, &packet) != TWI_SUCCESS);
        //twi_master_read(MMA8451_MASTER, &packet);
        return data_received[0];
}

void max1704x_write(uint8_t reg, uint8_t data) {
        uint8_t buffer[] = {data};
        twi_package_t packet  = {
                .addr[0]                = reg,
                .addr_length            = sizeof(uint8_t),
                .chip                   = MAX1704X_ADDR,
                .buffer                 = (void *)buffer,
                .length                 = sizeof(buffer)
        };
        while (twi_master_write(MAX1704X_MASTER, &packet) != TWI_SUCCESS);
        //twi_master_write(MMA8451_MASTER, &packet);
}

uint8_t max1704x_version(void) {
    return max1704x_read(0x09); 
}

uint8_t max1704x_bat(void) {
        return max1704x_read(0x04);
}
