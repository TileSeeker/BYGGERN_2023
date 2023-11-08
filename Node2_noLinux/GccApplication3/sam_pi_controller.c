#include "sam_pi_controller.h"

volatile uint8_t error_sum = 0;

int16_t PI_controller(int16_t current_pos, int8_t target_pos) {
	int16_t error = target_pos - current_pos;
	error_sum += error;
	int16_t p = K_p * error;
	int16_t i = K_i * error_sum;
	int16_t u = p + i;
	
	//Need to set/find max and min value
	if (u > u_max) {
		return u_max;
	} else if (u < u_min) {
		return u_min;
	} else {
		return u;
	}
}
