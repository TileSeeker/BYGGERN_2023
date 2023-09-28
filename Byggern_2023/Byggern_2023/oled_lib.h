#ifndef OLED_LIB_H
#define OLED_LIB_H

#include <stdio.h>
#include "xmem.h"

void write_oled_command(uint8_t command);
void write_oled_data(uint8_t data);
void oled_init(void);
void oled_goto_line(uint8_t line);
void oled_goto_column(uint8_t column);
void oled_clear_line(uint8_t line);
void oled_reset();
void oled_pos(uint8_t row, uint8_t column);
void oled_set_brigthness(uint8_t lvl);
void oled_print(char str);
void oled_arrow_at_pos(uint8_t row, uint8_t column);

void oled_home();
void print_menu(Menu menu);
void select(Menu menu);

typedef struct Menu {
	uint8_t select = 0;
	uint8_t menu_options = 3;
	char options[3][] =	{"Start", "Quit", "Credits"};
};

#endif