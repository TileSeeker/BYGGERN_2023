#include "sam_adc.h"
#include "sam.h"

void adc_init() {
	PMC->PMC_PCER1 |= PMC_PCER1_PID37;		//Enable ADC controller
	//ADC->ADC_ACR |= ADC_CHER_CH4

}