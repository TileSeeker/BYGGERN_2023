#include "oled_lib.h"

void write_oled_command(uint8_t command) {
	volatile char *oled_command = (char *) 0x1000;
	oled_command[0] = command;
}

void write_oled_data(uint8_t data) {
	volatile char *oled_data = (char *) 0x1200;
	oled_data[0] = data;
}

//9.4 Recommended Software Initialization
void oled_init(void) {
	write_oled_command(0xae); //display off
	write_oled_command(0xa1); //segment remap
	write_oled_command(0x12);
	write_oled_command(0xc8); //common output direction: com63~com0
	write_oled_command(0xa8); //multiplex ration mode:63
	write_oled_command(0x3f);
	write_oled_command(0xd5); //display divide ratio/osc. freq. mode
	write_oled_command(0x080);
	write_oled_command(0x81); //contrast control
	write_oled_command(0x50);
	write_oled_command(0xd9); //set pre-charge period
	write_oled_command(0x21);
	write_oled_command(0x20); //set memory adressing mode
	write_oled_command(0x02);
	write_oled_command(0xdb); //VCOM deselect mode
	write_oled_command(0x30); 
	write_oled_command(0xad); //master configuration
	write_oled_command(0x00);
	write_oled_command(0xa4); //out follows RAM content
	write_oled_command(0xa6); //set normal display
	write_oled_command(0xaf); //display on
}

void oled_reset() {}
void oled_home() {}
void oled_goto_line(uint8_t line) {}
void oled_goto_column(uint8_t column) {}
void oled_clear_line(uint8_t line) {}
void oled_pos(uint8_t row, uint8_t column) {}
void oled_print(char* str) {}