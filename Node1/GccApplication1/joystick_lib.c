#include "joystick_lib.h"
#include <avr/io.h>
#include "MCP2515_lib.h"

void joystick_calibrate(void) {
	x_middle_position = ADC_read(channel_0);
	y_middle_position = ADC_read(channel_1);
}

//https://deepbluembedded.com/map-function-embedded-c/
int MAP(int pos_in, int pos_in_min, int pos_in_max, int pos_out_min, int pos_out_max) {
	return ((((pos_in - pos_in_min) * (pos_out_max - pos_out_min)) / (pos_in_max - pos_in_min)) + pos_out_min);
}

joystick_position joystick_position_read(void) {
	joystick_position position;
	
	//X position of joystick
	int x_pos = ADC_read(channel_0);
	if (x_pos < x_middle_position) {
		position.x_pos = MAP(x_pos, xy_position_min, x_middle_position, -100, 0);
	} else {
		position.x_pos = MAP(x_pos, x_middle_position, xy_position_max, 0, 100);
	}
	//Y position of joystick
	int y_pos = ADC_read(channel_1);
	if (y_pos < y_middle_position) {
		position.y_pos = MAP(y_pos, xy_position_min, y_middle_position, -100, 0);
		} else {
		position.y_pos = MAP(y_pos, y_middle_position, xy_position_max, 0, 100);
	}
	return position;
}

joystick_direction joystick_direction_read(void) {
	joystick_direction direction = {X_MID, Y_MID};
	joystick_position position = joystick_position_read();
	
	//X direction of joystick
	if (position.x_pos < -direction_sensitivity && position.x_pos >= -100) {
		direction.x_dir = LEFT;
	} else if (position.x_pos > direction_sensitivity && position.x_pos <= 100) {
		direction.x_dir = RIGHT;
	} else {
		direction.x_dir = X_MID;
	}
	
	//Y direction of joystick
	if (position.y_pos > direction_sensitivity && position.y_pos <= 100) {
		direction.y_dir = UP;
	} else if (position.y_pos < -direction_sensitivity && position.y_pos >= -100) {
		direction.y_dir = DOWN;
	} else {
		direction.y_dir = Y_MID;
	}
	return direction;
}

void init_joystick_button(void) {
	DDRB	&= ~(1 << DDB1); //Set pin to INPUT
	PORTB	|= (1 << PB1);	 //Enable internal pull-up
}

void can_send_joystick() {
	joystick_position pos = joystick_position_read();
	
	can_message_t joy_pos = {
		.id = 0,
		.length = 2,
		.data[0] = (uint8_t)pos.x_pos,
		.data[1] = (uint8_t)pos.y_pos
	};
	
	can_send_message(&joy_pos);
}