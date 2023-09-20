#ifndef ADC_LIB_H
#define ADC_LIB_H

#define F_CPU 4915200UL //4.9152MHz
#include <util/delay.h>

//[Table 2, page 9]
#define channel_0 0
#define channel_1 1
#define channel_2 2
#define channel_3 3

int ADC_read(int channel);

#endif
