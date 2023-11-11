#include "sam.h"
#include "sam_led.h"
#include "uart.h"
#include "can_controller.h"
#include "printf-stdarg.h"
#include "sam_pwm.h"
#include "sam_adc.h"
#include <stdlib.h>
#include <stdbool.h>
#include "sam_dac.h"
#include "sam_motor.h"
#include "sam_solenoid.h"


//MCK = 84MHz & CAN baud rate = 125kbit/s
//16 time quanta | bit time = 1 / 125kbit/S = 8us | Tcsc = bit time / 16 = 500ns | BRP = (Tcsc * MCK) - 1 = (500ns * 84MHz) - 1 = 42 - 1 = 41
//SMP = SAMPLE_1X = 0 | BRP = 41 | SJW = 1 - 1 = 0 | PROPSEG = 2 - 1 = 1 | PS1 = 7 - 1 = 6 | PS2 = 6 - 1 = 5 | 
// -> 0b 00000000 00101001 00000001 01100101 -> 0x290165
#define CAN_BAUDRATE 0x0290165

#define goal_threshold_falling 1000
#define goal_threshold_rising 2000
volatile uint8_t score = 0;
volatile uint16_t adc_last_data;
volatile uint16_t adc_data;
volatile bool score_toggle;


int main(void)
{
	SystemInit();					//Initialize the SAM system
	WDT->WDT_MR |= WDT_MR_WDDIS;	//Disable watchdog timer
	PMC->PMC_WPMR &= ~(0x1);		//WPEN bit clear for PIO write protect mode register 					
	configure_uart();				//Baudrate = master clock / (16 * clock divider) = 84MHz / (16 * 547) = 9600
	
	led_init();
	pwm_init();
	adc_init();
	dac_init();
	sysTick_init();
	motor_init();
	solenoid_init();
	
	
	//CAN
	can_init_def_tx_rx_mb(CAN_BAUDRATE);
	CAN_MESSAGE rec;
	char msg_str[10];
	
	score_toggle = 0;
    while (1) {
		//Receive CAN message
		can_receive(&rec, 0);
				
		//Control duty cycle with joystick
		pwm_joystick(&rec, 1);
		
		//Control motor with joystick
		motor_position_joystick(&rec, 0);
		
		//ADC
		adc_last_data= adc_data;
		adc_data = adc_read();
		//printf("ADC: %d \r\n", adc_data);
		
		//Goal
		if ((adc_data < goal_threshold_falling)  && score_toggle==0) {
			score += 1;
			score_toggle = 1;
			printf("Goal! current score: %d \r\n", score);
		}
		if ((adc_data > goal_threshold_rising)  && score_toggle==1) {
			score_toggle = 0;
		}
		
		//Hit ball
		if (rec.data[2] == 1) {
			PIOA->PIO_CODR = PIO_SODR_P14;	//Set pin 23 high
		} else {
			PIOA->PIO_SODR = PIO_CODR_P14;	//Set pin 23 low 
		}
	}
}

