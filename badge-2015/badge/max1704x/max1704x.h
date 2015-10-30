#include <sysclk.h>
#include "twi_master.h"

#define MAX1704X_MASTER			&TWIE
#define MAX1704X_SPEED          50000
#define MAX1704X_ADDR           0x36

void twi_max1704x_init(void);
void max1704x_init(void);
uint8_t max1704x_read(uint8_t reg);
void max1704x_write(uint8_t reg, uint8_t data);

/* MODULE SPECIFIC */
uint8_t max1704x_bat(void);
uint8_t max1704x_version(void);
