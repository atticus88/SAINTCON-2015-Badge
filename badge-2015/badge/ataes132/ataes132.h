#include <sysclk.h>
#include "twi_master.h"

#define ATAES132_MASTER			&TWIE
#define ATAES132_SPEED          50000
#define ATAES132_ADDR           0xA1

void ataes132_init(void);
uint8_t ataes132_read(uint8_t reg);
void ataes132_write(uint8_t reg, uint8_t data);

/* MODULE SPECIFIC */
uint8_t ataes132_light(void);
uint8_t ataes132_version(void);
