#include "sam_motor.h"

#define  encoder_max 1403
#define encoder_min 0

void motor_init() {
	PMC->PMC_PCER0 = (PMC_PCER0_PID13 | PMC_PCR_EN);			//Enable parallel I/O controller C
	
	PIOD->PIO_PER = (DIR | EN | NOT_OE | SEL | NOT_RST);					//PIO enable registers
	PIOD->PIO_OER = (DIR | EN | NOT_OE | SEL | NOT_RST);					//Output enable registers
	
	PIOC->PIO_PER = MJ2;
	PIOC->PIO_ODR = MJ2;										//Output disable register
	
	PIOD->PIO_SODR = (EN | NOT_RST);										//Motor enable and encoder reset disable
	PIOD->PIO_CODR = NOT_OE;									//Encoder output enable
			
	//Calibrate
	PIOD->PIO_SODR = DIR;
	dac_write_raw(0xFF);
	delay_us(90000);
	delay_us(90000);
	delay_us(90000);
	delay_us(90000);
	dac_write_raw(0);
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
	delay_us(20);
	PIOD->PIO_SODR = NOT_RST;								//Disable encoder reset
}

void motor_position_joystick(CAN_MESSAGE* rec, int channel) {
	int16_t current = read_encoder();
	int16_t ref = MAP((int8_t)rec->data[channel], 100, -100, encoder_min, encoder_max);
	int16_t u = PI_controller(current, ref);
	if (current > ref) {
		//Left
		PIOD->PIO_SODR = DIR;
	} else {
		//Right
		PIOD->PIO_CODR = DIR;
	}
	dac_write_raw(u);
}

