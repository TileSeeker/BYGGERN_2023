#include "adc_lib.h"

//int ADC_read(int channel) {
//	volatile char *adc = (char *) 0x1400; //ADC start address
//	adc[0] = 0; //Channel enable
//	_delay_ms((9 * 4 * 2) / F_CPU);
//	
//	uint8_t value;
//	for (int i=0 ; i<=channel; i++) {
//		 value = adc[0]; //8 bit value from channel
//	}
//	return value;
//}

int ADC_read(int channel) {
	volatile char *adc = (char *) 0x1400; //ADC start address
	adc[0] = (1 << 7) | channel; //Only "channel" channel is converted [table.1]
	uint8_t value;
	_delay_us(400);
	value = adc[0];
	return value;
}