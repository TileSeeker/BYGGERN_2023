#include "sam_adc.h"

void adc_init() {
	PMC->PMC_PCER1 |= PMC_PCER1_PID37;		//Enable peripheral ADC controller
	ADC->ADC_MR |= ADC_MR_FREERUN;			//Enable free run mode (never wait for any trigger)
	ADC->ADC_CHER |= ADC_CHER_CH0;			//Enable ADC channel 0 => PA2 -> AD7 -> pin 8 analog P2 
	ADC->ADC_CR |= ADC_CR_START;			//Start analog to digital conversion
}

uint16_t adc_read() {
	return ADC->ADC_CDR[0];					//Return data from ADC channel 0
}

uint16_t adc_read_last() {
	return ADC->ADC_LCDR;					//Return last converted data
}