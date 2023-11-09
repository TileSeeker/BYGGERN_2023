#ifndef SAM_DAC_H
#define SAM_DAC_H

#include "sam.h"
#include "stdio.h"
#include "sam_pi_controller.h"
#include <stdint.h>
#include "sam_pwm.h"

void dac_init();
void dac_write(int16_t data);
void dac_write_raw(uint16_t data);


#endif