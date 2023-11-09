#ifndef SAM_MOTOR_H
#define SAM_MOTOR_H

#include "sam.h"
#include "sam_delay.h"
#include "sam_dac.h"
#include "sam_pi_controller.h"
#include "can_controller.h"

#define DIR PIO_PD10
#define EN PIO_PD9
#define SEL PIO_PD2
#define NOT_OE PIO_PD0
#define NOT_RST PIO_PD1
#define MJ2 (PIO_PC1 | PIO_PC2 | PIO_PC3 | PIO_PC4 | PIO_PC5 | PIO_PC6 | PIO_PC7 | PIO_PC8)

void motor_init(void);
int16_t read_encoder(void);
void restart_encoder(void);
void motor_position_joystick(CAN_MESSAGE* rec, int channel);
void motor_calib();

#endif