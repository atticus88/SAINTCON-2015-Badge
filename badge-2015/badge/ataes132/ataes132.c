#include "ataes132.h"

void ataes132_init(void) {

}

uint8_t ataes132_read(uint8_t reg) {
        uint8_t data_received[1];

        twi_package_t packet = {
                .addr[0]                = reg,
                .addr_length            = sizeof(uint8_t),
                .chip                   = ATAES132_ADDR,
                .buffer                 = data_received,
                .length                 = sizeof(data_received)
        };
        while (twi_master_read(ATAES132_MASTER, &packet) != TWI_SUCCESS);
        //twi_master_read(MMA8451_MASTER, &packet);
        return data_received[0];
}

void ataes132_write(uint8_t reg, uint8_t data) {
        uint8_t buffer[] = {data};
        twi_package_t packet  = {
                .addr[0]                = reg,
                .addr_length            = sizeof(uint8_t),
                .chip                   = ATAES132_ADDR,
                .buffer                 = (void *)buffer,
                .length                 = sizeof(buffer)
        };
        while (twi_master_write(ATAES132_MASTER, &packet) != TWI_SUCCESS);

        //ataes132_read()
        //twi_master_write(MMA8451_MASTER, &packet);
}

uint8_t ataes132_version(void) {
    return ataes132_read(0x0C); 
}

uint8_t ataes132_light(void) {

}
