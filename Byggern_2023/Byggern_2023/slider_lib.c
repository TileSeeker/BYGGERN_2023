#include "slider_lib.h"

int read_slider_position(int channel) {
	return ADC_read(channel);
}