#ifndef JOYSTICK_LIB_H
#define JOYSTICK_LIB_H

#include "adc_lib.h"
#include <stdio.h>

volatile int x_middle_position;
volatile int y_middle_position;

#define xy_position_max 255
#define xy_position_min 1

#define direction_sensitivity 10

typedef enum {
	X_MID,
	LEFT,
	RIGHT
} x_direction;

typedef enum {
	Y_MID,
	UP,
	DOWN
} y_direction;

typedef struct {
	char x_dir;
	char y_dir;
} joystick_direction;
	
typedef struct {
	int x_pos;
	int y_pos;
} joystick_position;
	
void joystick_calibrate(void);
int MAP(int pos_in, int pos_in_min, int pos_in_max, int pos_out_min, int pos_out_max);
joystick_position joystick_position_read(void);
joystick_direction joystick_direction_read(void);
void init_joystick_button(void);

#endif