#include <sysclk.h>
#include "twi_master.h"

#define TSL2561T_MASTER			&TWIE
#define TSL2561T_SPEED          50000
#define TSL2561T_ADDR           0x39

void tsl2561t_init(void);
uint8_t tsl2561t_read(uint8_t reg);
void tsl2561t_write(uint8_t reg, uint8_t data);

/* MODULE SPECIFIC */
double tsl2561t_light(void);
uint8_t tsl2561t_version(void);
