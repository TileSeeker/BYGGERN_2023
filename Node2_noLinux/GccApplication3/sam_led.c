#include "sam_led.h"
#include "sam.h"

//Led D1 -> pin42 -> PA19
//Led D2 -> pin43 -> PA20

void led_init() {
	//Enable peripheral control register
	PMC->PMC_PCR |=  PMC_PCR_EN;
	//Parallel input/output enable for led D1 and D2
	PIOA ->PIO_PER = (PIO_PER_P19 | PIO_PER_P20);
	//Output enable
	PIOA->PIO_OER = (PIO_OER_P19 | PIO_OER_P20);
	//Clear output data register
	PIOA->PIO_CODR = (PIO_CODR_P19 | PIO_CODR_P20);
	//Set output register
	PIOA->PIO_SODR = (PIO_SODR_P19 | PIO_SODR_P20);
}