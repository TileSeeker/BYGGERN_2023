#include "sam_solenoid.h"

void solenoid_init() {
	PMC->PMC_PCR |=  PMC_PCR_EN;
	PIOA ->PIO_PER = PIO_PER_P14;		//Pin 23 parallel input/output enable
	PIOA->PIO_OER = PIO_OER_P14;		//Pin 23 output enable
}

void solenoid_hit_bal() {
		PIOA->PIO_CODR = PIO_SODR_P14;	//Set pin 23 high
		delay_us(900000);
		delay_us(900000);
		PIOA->PIO_SODR = PIO_CODR_P14;	//Set pin 23 low 
}
