/*
 * sam_dac.h
 *
 * Created: 02-Nov-23 2:51:06 PM
 *  Author: peter
 */ 
#pragma once

void dac_init();
void dac_write(int8_t data);
void dac_write_raw(uint32_t data);
uint32_t map_2(uint32_t pos_in, uint32_t pos_in_min, uint32_t pos_in_max, uint32_t pos_out_min, uint32_t pos_out_max);