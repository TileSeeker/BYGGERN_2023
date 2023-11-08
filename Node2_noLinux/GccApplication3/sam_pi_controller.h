#ifndef SAM_PI_CONTROLLER_H
#define SAM_PI_CONTROLLER_H

#include "stdio.h"
#include <stdint.h>

#define K_p 10
#define K_i 10
#define u_max 200
#define u_min 0

int16_t PI_controller(int16_t current_pos, int8_t target_pos);


#endif