/*
 * adc_lib.c
 *
 * Created: 14-Sep-23 9:29:33 AM
 *  Author: peter
 */ 

#include <stdint.h>
#include <stdlib.h>
#include "adc_lib.h"

#define ADC_address 0x1400
#define max_value 0xFF
#define min_value 0x00

int map(int x, int in_min, int in_max, int out_min, int out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


int read_channel(uint8_t channel){
	volatile char *adc = (char *) ADC_address; //ADC start address
	
	/*
	adc[0] = (0x80 & channel);
	_delay_ms(1);
	adc[0] = (0x80 & channel);
	_delay_ms(1);
	uint8_t data = adc[0]; //Read Ch 0
	_delay_ms(1);
	*/
	
	int data = 0;
	adc[0] = 0x00;
	for(int i = 0; i<(channel+1); i++){
		data = adc[i];
	}
	return data;
}

uint8_t offset[4];
void adc_offset_callibrate(){
	offset[0] = read_channel(channel_0);
	offset[1] = read_channel(channel_1);
	offset[2] = read_channel(channel_2);
	offset[3] = read_channel(channel_3);
}

int read_angle(uint8_t channel){
	int raw_data = read_channel(channel);
	
	int angle;
	if (raw_data >= offset[channel]){
		angle = map(raw_data, offset[channel], 255, 0, 100);
	}
	else{
		angle = map(raw_data, 0, offset[channel], -100, 0);
	}
	
	//int angle = (int)map(raw_data, 0, 255, -100, 100);
	return angle;
}

char left_string[] = "Left";
char right_string[] = "Right";
char none_string[] = "-";
char *str_ptr;
int threshold = 50;
char* read_dirrection(uint8_t channel){
	int data = read_angle(channel);
	if (data > threshold){
		str_ptr = &right_string;
	}
	else if(data < -threshold){
		str_ptr = &left_string;
	}
	else{
		str_ptr = &none_string;
	} 
	return str_ptr;
}

