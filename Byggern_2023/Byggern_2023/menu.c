#include "menu.h"

menu_t* create_new_menu(menu_t* prev, menu_t* next, char* text, void (*function)()) {
    menu_t* new = malloc(sizeof(menu_t));
    new->menu_text = text;
    new->next_menu = next;
    new->prev_menu = prev;
    new->function = function;


    return new;
}