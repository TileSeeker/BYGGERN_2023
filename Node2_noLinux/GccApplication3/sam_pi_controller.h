#ifndef SAM_PI_CONTROLLER_H
#define SAM_PI_CONTROLLER_H

#include "stdio.h"
#include <stdint.h>

#define K_p 2
#define K_i 0.2

#define u_max 130		//Max speed
#define u_min 0	

int16_t PI_controller(int16_t current_pos, int16_t target_pos);


#endif