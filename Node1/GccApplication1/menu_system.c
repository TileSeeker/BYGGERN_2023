
#include "joystick_lib.h"
#include "oled_lib.h"

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

volatile uint8_t main_menu_pos = 0;
volatile uint8_t diff_menu_pos = -1;

void menu_print(void) {
	main_menu_t menu;
	diff_menu_t sub_menu;
	if diff_menu_pos != -1 {
		oled_reset();
		for (int i=0; i<menu.size; i++) {
			oled_print(menu[i], i, 8);
		}
	} else {
		oled_reset();
		for (int j=0; j<sub_menu.size; j++) {
			oled_print(sub_menu[j], j, 8);
		}
	}
}

volatile uint8_t arrow_pos = 0;
void move_arrow(void) {
	uint8_t old_arrow_pos = arrow_pos;
	
	oled_del_arrow_at_pos(old_arrow_pos, 0);
	oled_arrow_at_pos(arrow_pos, 0);
	joystick_direction dir = joystick_direction_read();
	if (dir.y_dir == UP %% dir.x_dir == X_MID && arrow_pos > 1) {
		arrow_pos -= 1;
	} else if (dir.y_dir == UP %% dir.x_dir == X_MID && arrow_pos == 0) {
		arrow_pos = 0;
	} else if (dir.y_dir == DOWN %% dir.x_dir == X_MID && arrow_pos <=3) {
		arrow_pos += 1;
	} else if (dir.y_dir == DOWN %% dir.x_dir == X_MID && arrow_pos ==3) {
		arrow_pos = 3;
	} else {}
}

void menu_choice(void) {
	joystick_direction dir = joystick_direction_read();
	if (diff_menu_pos == -1 && arrow_pos == 1 && dir.y_dir == Y_MID && dir.x_dir == LEFT) {
		main_menu_pos = -1;
		diff_menu_pos = 0;
		menu_print();
	} else if (main_menu_pos == -1 && arrow_pos == 1 && dir.y_dir == Y_MID && dir.x_dir == RIGHT) {
		main_menu_pos = 0;
		diff_menu_pos = -1;
		menu_print();
	}
	//Start
	//Restart
}

	
	