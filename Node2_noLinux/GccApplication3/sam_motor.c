#include "sam_motor.h"

void motor_init() {
	PMC->PMC_PCER0 = (PMC_PCER0_PID13 | PMC_PCR_EN);			//Enable parallel I/O controller C
	
	PIOD->PIO_PER = (DIR | EN | NOT_OE | SEL);					//PIO enable registers
	PIOD->PIO_OER = (DIR | EN | NOT_OE | SEL);					//Output enable registers
	
	PIOC->PIO_PER = MJ2;
	PIOC->PIO_ODR = MJ2;										//Output disable register
	
	PIOD->PIO_SODR = (EN | NOT_RST);										//Motor enable and encoder reset disable
	PIOD->PIO_CODR = NOT_OE;									//Encoder output enable
			
	restart_encoder();
}

int16_t read_encoder() {
	int16_t encoder_value;
	PIOD->PIO_CODR = (NOT_OE | SEL);						//Set !OE and SEL to low
	delay_us(20);
	uint8_t higher_bytes = (PIOC->PIO_PDSR & MJ2) >> 1;		//Read higher bytes from MJ2
	PIOD->PIO_SODR = SEL;									//Set SEL high
	delay_us(20);
	uint8_t lower_bytes = (PIOC->PIO_PDSR & MJ2) >> 1;		//Read lower bytes from MJ2
	PIOD->PIO_SODR = NOT_OE;								//Set !OE high
	encoder_value = (higher_bytes << 8) + lower_bytes;
	
	return encoder_value;
}

void restart_encoder() {
	PIOD->PIO_CODR = NOT_RST;								//Enable encoder reset
	delay_us(60);
	PIOD->PIO_SODR = NOT_RST;								//Disable encoder reset
}

void motor_position_joystick(CAN_MESSAGE* rec, int channel) {
	if ((int8_t)rec->data[channel] > 5) {
		//Left
		PIOD->PIO_SODR = DIR;
		int16_t current = read_encoder();
		int16_t ref = MAP((int8_t)rec->data[channel], -100, 0, encoder_min, encoder_mid);
		int16_t u = PI_controller(current, ref);
		dac_write_raw(u);
		
	} else if ((int8_t)rec->data[channel] < -5) {
		//Right
		PIOD->PIO_CODR = DIR;
		int16_t current = read_encoder();
		int16_t ref = MAP((int8_t)rec->data[channel], 0, 100, encoder_mid, encoder_max);
		int16_t u = PI_controller(current, ref);
		dac_write_raw(u);
	}
}

void motor_middle() {
	int16_t current = read_encoder();
	int16_t u = PI_controller(current, encoder_mid);
	dac_write_raw(u);
}