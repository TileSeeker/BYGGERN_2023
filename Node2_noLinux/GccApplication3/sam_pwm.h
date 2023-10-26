#ifndef SAM_PWM_H
#define SAM_PWM_H
#include "sam.h"
#include "can_controller.h"

void pwm_init(void);
int MAP(int pos_in, int pos_in_min, int pos_in_max, int pos_out_min, int pos_out_max);
void pwm_joystick(CAN_MESSAGE* rec, int channel);

#endif