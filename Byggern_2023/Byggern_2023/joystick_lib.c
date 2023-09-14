#include "adc_lib.h"
#include <stdio.h>

volatile int x_offset = 0;
volatile int y_offset = 0;

void joystick_calibrate(void) {
	x_offset = ADC_read(channel_0);
	y_offset = ADC_read(channel_1);
}
//      173 = 0
// 01 <- x -> 255
// 01 <- y -> 255

int joystick_position_x(void) {
	int offset = x_offset - 127;
	
	int position_x = ((ADC_read(channel_0) - offset - 127) * 100) / 127;
	return position_x;
}

int joystick_position_y(void) {
	int offset = y_offset - 127;
	int position_y = ((ADC_read(channel_1) - offset - 127) * 100) / 127;
	
	return position_y;
}
