#ifndef SAM_ADC_H
#define SAM_ADC_H

#include "sam.h"

void adc_init(void);
uint16_t adc_read(void);
uint16_t adc_read_last();

#endif