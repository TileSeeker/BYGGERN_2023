#include "sam_pwm.h"
#include "sam.h"

void pwm_init() {
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;		//Enable peripheral clock for PWM
	PIOC->PIO_ABSR |= PIO_ABSR_P19;			//Select B peripheral register for PWM waveform output high for channel 5 for pin 44
	PIOC->PIO_PDR |= PIO_PDR_P19;			//Enables peripheral control of the pin 44
	
	//Wave period = 1 / 50Hz = (2 * CPRD * DIVA) / MCK -> 50 Hz = MCK / (2 * CPRD * DIVA) = 84MHz / (2 * 20000 * 42) = 50Hz
	PWM->PWM_CLK |= PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);					//Set PWM clock to 2MHz
	PWM->PWM_CH_NUM[5].PWM_CMR |= PWM_CMR_CALG | PWM_CMR_CPRE_CLKA;		//Set channel 5 to center aligned waveforms and clock A as source
	PWM->PWM_CH_NUM[5].PWM_CPRD |= 20000;								//Set channel 5 period to 20ms
	PWM->PWM_CH_NUM[5].PWM_CDTY |= 900;									//Set channel 5 duty cycle to 1.5ms
	PWM->PWM_ENA |= PWM_ENA_CHID5;										//Enable PWM output for channel 5	
}