#include "adc_lib.h"


int ADC_read(int channel) {
	volatile char *adc = (char *) 0x1400;	//ADC start address
	adc[0] = (1 << 7) | channel;			//Only "channel" channel is converted [table.1]
	uint8_t value;
	_delay_us(400);
	value = adc[0];
	return value;
}