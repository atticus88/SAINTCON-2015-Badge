#include <sysclk.h>
#include "twi_master.h"
#include "powermgmt.h"

#define MMA8451_MASTER			&TWIE
#define MMA8451_SPEED          	50000
#define MMA8451_ADDR            0x1C

volatile bool motion_int;
volatile bool lndprt_int;
volatile uint8_t move_counter;

void twi_init(void);
void mma8451_init(void);
uint8_t mma8451_read(uint8_t reg);
void mma8451_write(uint8_t reg, uint8_t data);
uint8_t mma8451_orientation(void);
bool mma8451_clear_interrupt(void);
