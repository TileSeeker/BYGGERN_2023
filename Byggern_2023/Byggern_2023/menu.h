#ifndef MENU_H
#define MENU_H

#include "joystick_lib.h"
#include "oled_lib.h"

typedef struct menu_t {
    char* menu_text;
    menu_t* prev_menu;
    menu_t* next_menu;
    void (*function)();
} menu_t;

typedef struct main_menu_t {
	char[] Start;
	char[] Difficulty;
	char[] Restart;
	uint8_t size = 3;
	} main_menu_t;
	
typedef struct diff_menu_t {
	char[] Easy;
	char[] Medium;
	char[] Hard;
	uint8_t size = 3;
} diff_menu_t;


#endif