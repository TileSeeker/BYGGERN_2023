#include "menu_system.h"

volatile int main_menu = 0;
volatile int diff_menu = -1;
volatile uint8_t arrow_pos = 0;
volatile uint8_t difficulty = 0;

#define diff_menu_pos 1

void menu_print(void) {
	if (diff_menu == -1) {
		oled_print("Start", 0, 8);
		oled_print("Difficulty", 1, 8);
		oled_print("Restart", 2, 8);
	} else if (main_menu == -1) {
		oled_print("Easy", 0, 8);
		oled_print("Medium", 1, 8);
		oled_print("Hard", 2, 8);
	}
}

void move_arrow(void) {
	uint8_t old_arrow_pos = arrow_pos;
	oled_arrow_at_pos(arrow_pos, 0);
	
	joystick_direction dir = joystick_direction_read();
	if (dir.y_dir == UP && dir.x_dir == X_MID && arrow_pos >= 1) {
		arrow_pos -= 1;
		_delay_ms(300);
	} else if (dir.y_dir == UP && dir.x_dir == X_MID && arrow_pos == 0) {
		arrow_pos = 0;
		_delay_ms(300);
	} else if (dir.y_dir == DOWN && dir.x_dir == X_MID && arrow_pos <= 2) {
		arrow_pos += 1;
		_delay_ms(300);
	} else if (dir.y_dir == DOWN && dir.x_dir == X_MID && arrow_pos == 2) {
		arrow_pos = 3;
		_delay_ms(300);
	} else {}
	
	if (old_arrow_pos != arrow_pos) {
		oled_del_arrow_at_pos(old_arrow_pos, 0);
	}
}

void menu_choice(void) {
	joystick_direction dir = joystick_direction_read();
	
	//Choose main or sub menu
	if (main_menu >= 0 && arrow_pos == diff_menu_pos && dir.x_dir == RIGHT) {
		main_menu = -1;
		diff_menu = 0;
		_delay_ms(300);
		
		oled_reset();
		menu_print();
	} else if (diff_menu >= 0 && dir.x_dir == LEFT) {
		main_menu = 0;
		diff_menu = -1;
		_delay_ms(300);
		
		oled_reset();
		menu_print();
	}
	
	//Choose functions
	if (main_menu >= 0 && arrow_pos == 0 && dir.x_dir == RIGHT) {
		printf("Starting.. \n\n");
		_delay_ms(300);
	} else if (main_menu >= 0 && arrow_pos == 2 && dir.x_dir == RIGHT) {
		printf("Restart \n\n");
		_delay_ms(300);
	} else if (diff_menu >= 0 && arrow_pos == 0 && dir.x_dir == RIGHT) {
		difficulty = 0;
		printf("Difficulty set to easy! \n\n");
		_delay_ms(300);
	} else if (diff_menu >= 0 && arrow_pos == 1 && dir.x_dir == RIGHT) {
		difficulty = 1;
		printf("Difficulty set to medium! \n\n");
		_delay_ms(300);
	} else if (diff_menu >= 0 && arrow_pos == 2 && dir.x_dir == RIGHT) {
		difficulty = 2;
		printf("Difficulty set to hard! \n\n");
		_delay_ms(300);
	} else {}
}

	
	