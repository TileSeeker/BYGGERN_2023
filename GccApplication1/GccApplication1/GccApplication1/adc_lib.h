/*
 * adc_lib.h
 *
 * Created: 14-Sep-23 9:29:45 AM
 *  Author: peter
 */ 

#pragma once

enum{
	channel_0 = 0x0,
	channel_1 = 0x1,
	channel_2 = 0x2,
	channel_3 = 0x3
};

int map(int x, int in_min, int in_max, int out_min, int out_max);

int read_channel(uint8_t channel);
int read_angle(uint8_t channel);
void adc_offset_callibrate();
char* read_dirrection(uint8_t channel);