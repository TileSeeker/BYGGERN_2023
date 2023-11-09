#include "sam_solenoid.h"

void solenoid_init() {
	PMC->PMC_PCR |=  PMC_PCR_EN;
	PIOA ->PIO_PER = PIO_PER_P14;		//Pin 23 parallel input/output enable
	PIOA->PIO_OER = PIO_OER_P14;		//Pin 23 output enable
}

