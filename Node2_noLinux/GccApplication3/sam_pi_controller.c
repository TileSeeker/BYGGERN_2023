#include "sam_pi_controller.h"

volatile int16_t error_sum = 0;

int16_t PI_controller(int16_t current_pos, int16_t target_pos) {
	int16_t error = abs(target_pos - current_pos);
	//printf("Error: %d \r\n", error);
	error_sum += error;
	int16_t p = K_p * error;
	int16_t i = K_i * error_sum * 0.00001;
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
