#include "asf.h"
#include "mma8451.h"
#include "at45dbx.h"
#include "keyboard.h"
#include "esp8266.h"

char macAddress[18];
char espError[512];

void network_application(void);