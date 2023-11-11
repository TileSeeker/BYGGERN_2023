#include "sam_dac.h"

void dac_init(){
	
	PMC->PMC_PCER1 |= PMC_PCER1_PID38;		//Enable peripheral DAC controller //ADC1 : PIN77 PB16 
	
	DACC-> DACC_MR		|= (DACC_MR_TRGEN_DIS)			//DACC in Free running Mode	
						| (DACC_MR_WORD_HALF)			//16bit input mode
						| (DACC_MR_MAXS_MAXIMUM)		//MAX speed mode enabled
						| (DACC_MR_STARTUP_1024)
						| (DACC_MR_USER_SEL_CHANNEL1);	//Channel 1 Select => PB16 -> DAC1
	
	
						
	DACC-> DACC_CHER	= (DACC_CHDR_CH1);				//DAC Channel 1 Enable
}


void dac_write_raw(uint16_t data){
	DACC-> DACC_CDR = (data << 4);
	//printf("DAC_WRITE: %08x \t", data);
}

void dac_write(int16_t data){
	dac_write_raw(MAP(data, -100, 100, 0, 0xFF));
}