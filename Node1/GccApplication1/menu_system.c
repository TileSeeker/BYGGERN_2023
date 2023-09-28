#include "menu_system.h"

volatile int main_menu = 0;
volatile int diff_menu = -1;
volatile uint8_t arrow_pos = 0;

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
		oled_del_arrow_at_pos(old_arrow_pos);
	}
}

void menu_choice(void) {
	joystick_direction dir = joystick_direction_read();
	if (main_menu >= 0 && arrow_pos == 1 && dir.x_dir == RIGHT) {
		oled_reset();
		main_menu = -1;
		diff_menu = 0;
		_delay_ms(300);
		menu_print();
	} else if (diff_menu >= 0 && arrow_pos == 1 && dir.x_dir == LEFT) {
		oled_reset();
		main_menu = 0;
		diff_menu = -1;
		_delay_ms(300);
		menu_print();
	}
	//Start
	//Restart
	
	//Easy
	//Medium
	//Hard
}

	
	