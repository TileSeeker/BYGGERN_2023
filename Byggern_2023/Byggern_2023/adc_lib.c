#include "adc_lib.h"
#define F_CPU 4915200UL //4.9152MHz
#include <util/delay.h>


int ADC_read(int channel) {
	volatile char *adc = (char *) 0x1400; //ADC start address
	adc[0] = 0; //Channel enable
	_delay_us(200);
	
	uint8_t value;
	for (int i=0 ; i<=channel; i++) {
		 value = adc[0]; //8 bit value from channel
	}
	return value;
}