#include "sam_pwm.h"
#include "sam.h"

void pwm_init() {
	PMC->PMC_PCER1 |= PMC_PCER1_PID36;		//Enable peripheral PWM controller
	PIOC->PIO_ABSR |= PIO_ABSR_P19;			//Select B peripheral register for PWM waveform output high for channel 5 for PC19 -> pin 44
	PIOC->PIO_PDR |= PIO_PDR_P19;			//Enables peripheral control of the PC19
	
	//Wave period = 1 / 50Hz = (2 * CPRD * DIVA) / MCK -> 50 Hz = MCK / (2 * CPRD * DIVA) = 84MHz / (2 * 20000 * 42) = 50Hz
	PWM->PWM_CLK |= PWM_CLK_PREA(0) | PWM_CLK_DIVA(42);									//Set PWM clock to 2MHz
	PWM->PWM_CH_NUM[5].PWM_CMR |= PWM_CMR_CALG | PWM_CMR_CPRE_CLKA | PWM_CMR_CPOL;		//Set channel 5 to center aligned waveforms, clock A as source and channel polarity to start high
	PWM->PWM_CH_NUM[5].PWM_CPRD |= 20000;												//Set channel 5 period to 20ms
	PWM->PWM_CH_NUM[5].PWM_CDTY |= 1500;												//Set channel 5 duty cycle to 1.5ms (center position)
	PWM->PWM_ENA |= PWM_ENA_CHID5;														//Enable PWM output for channel 5	
}

int MAP(int pos_in, int pos_in_min, int pos_in_max, int pos_out_min, int pos_out_max) {
	return ((((pos_in - pos_in_min) * (pos_out_max - pos_out_min)) / (pos_in_max - pos_in_min)) + pos_out_min);
}

void pwm_joystick(CAN_MESSAGE* rec, int channel) {
	if ((int8_t)rec->data[channel] > 5) {
		int right = MAP((int8_t)rec->data[channel], 0, 100, 1500, 2100);
		if (right > 2100) {
			PWM->PWM_CH_NUM[5].PWM_CDTY = 2100;
		} else {
			PWM->PWM_CH_NUM[5].PWM_CDTY = right;
		}
	} else if ((int8_t)rec->data[channel] < -5) {
		int left = MAP((int8_t)rec->data[channel], -100, 0, 900, 1500);
		if (left < 900) {
			PWM->PWM_CH_NUM[5].PWM_CDTY = 900;
		} else {
			PWM->PWM_CH_NUM[5].PWM_CDTY =left;
		}
	} else {
	PWM->PWM_CH_NUM[5].PWM_CDTY = 1500;
	}
}