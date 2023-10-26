#ifndef SAM_PWM_H
#define SAM_PWM_H
#include "sam.h"
#include "can_controller.h"

void pwm_init(void);
void pwm_joystick(CAN_MESSAGE* rec, int channel);

#endif