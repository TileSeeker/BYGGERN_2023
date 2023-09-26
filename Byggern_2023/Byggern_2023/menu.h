#ifndef MENU_H
#define MENU_H

typedef struct menu_t {
    char* menu_text;
    menu_t* prev_menu;
    menu_t* next_menu;
    void (*function)();
} menu_t;


#endif