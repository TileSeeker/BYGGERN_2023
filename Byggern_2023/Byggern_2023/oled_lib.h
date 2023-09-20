#ifndef OLED_LIB_H
#define OLED_LIB_H

#include <stdio.h>

void write_oled_command(uint8_t command);
void write_oled_data(uint8_t data);
void oled_init(void);
void oled_reset();
void oled_home();
void oled_goto_line(uint8_t line);
void oled_goto_column(uint8_t column);
void oled_clear_line(uint8_t line);
void oled_pos(uint8_t row, uint8_t column);
void oled_print(char* str);


#endif