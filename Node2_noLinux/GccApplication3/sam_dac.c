/*
 * sam_dac.c
 *
 * Created: 02-Nov-23 2:50:51 PM
 *  Author: peter
 */ 
#include "sam.h"
#include "sam_dac.h"
#include "stdio.h"
#include <stdint.h>

void dac_init(){
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID38;		//Enable peripheral DAC controller //ADC1 : PIN77 PB16 
	//PMC->PMC_PCR |= ((1<<28) + (1<<12) + 38);
	
	//DACC->DACC_WPMR = (('D'<<24)+('A'<<16)+('C'<<8) + 0);
	//DACC-> DACC_MR = DACC_MR_WORD_WORD;
	
	DACC-> DACC_MR		|= (DACC_MR_TRGEN_DIS)			//DACC in Free running Mode	
						| (DACC_MR_WORD_WORD)			//16bit input mode
						| (DACC_MR_MAXS_MAXIMUM)		//MAX speed mode enabled
						| (DACC_MR_STARTUP_1024)
						| (DACC_MR_USER_SEL_CHANNEL1);	//Channel 1 Select
	
	
						
	DACC-> DACC_CHER	= (DACC_CHDR_CH1);				//DAC Channel 1 Enable
	//DACC->DACC_WPMR = (('D'<<24)+('A'<<16)+('C'<<8) + 1);
}




void dac_write_raw(uint32_t data){
	//data = ((data & ((1<<9) -1)) << 20);
	DACC-> DACC_CDR = data;
	printf("DAC_WRITE: %08x \r\n", data);
}

void dac_write(int8_t data){
	dac_write_raw(map_2((uint8_t)(data+100), 0, 200, 0x0, 0xFFFFFFFF));
}

uint32_t map_2(uint32_t pos_in, uint32_t pos_in_min, uint32_t pos_in_max, uint32_t pos_out_min, uint32_t pos_out_max) {
	return ((((pos_in - pos_in_min) * (pos_out_max - pos_out_min)) / (pos_in_max - pos_in_min)) + pos_out_min);
}