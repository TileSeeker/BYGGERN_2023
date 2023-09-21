#include "oled_lib.h"
#include "fonts.h"
#include <string.h>

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
	write_oled_command(0xAE); //display off
	write_oled_command(0xA1); //segment remap
	write_oled_command(0x12);
	write_oled_command(0xC8); //common output direction: com63~com0
	write_oled_command(0xA8); //multiplex ration mode:63
	write_oled_command(0x3F);
	write_oled_command(0xD5); //display divide ratio/osc. freq. mode
	write_oled_command(0x080);
	write_oled_command(0x81); //contrast control
	write_oled_command(0x50);
	write_oled_command(0xD9); //set pre-charge period
	write_oled_command(0x21);
	write_oled_command(0x20); //set memory adressing mode
	write_oled_command(0x02);
	write_oled_command(0xDB); //VCOM deselect mode
	write_oled_command(0x30); 
	write_oled_command(0xAD); //master configuration
	write_oled_command(0x00);
	write_oled_command(0xA4); //out follows RAM content
	write_oled_command(0xA6); //set normal display
	write_oled_command(0xAF); //display on
}

void oled_goto_line(uint8_t line) {
	write_oled_command(0xB0 + line); //Set row 0 - 7
}

void oled_goto_column(uint8_t column) {
	write_oled_command(0x00 + (column % 16)); //lower nibble of column / last 4 bits of column
	write_oled_command(0x10 + (column / 16)); //higher nibble of column / first 4 bits of column
}

void oled_clear_line(uint8_t line) {
	oled_goto_line(line);
	for (int j=0; j<127; j++) { //Every row has 128 columns with length of 8 pixels/bits
		oled_goto_column(j);
		write_oled_data(0x00);
	}
}

void oled_reset() {
	for (int i=0; i<7; i++) {
		oled_clear_line(i);
	}
}

	
void oled_pos(uint8_t row, uint8_t column) {
	oled_goto_line(row);
	oled_goto_column(column);

}

void oled_set_brigthness(uint8_t lvl) {
	write_oled_command(0x81);
	write_oled_command(lvl);
}

void oled_print_char(char str, uint8_t row, uint8_t column) {
	unsigned char letter;
	int i = column;
	for (i; i < (column + font_size); i++) {
		letter = pgm_read_byte(&(font8[str-32][i-column]));
		oled_pos(row,i);
		write_oled_data(letter);
	}
}

void oled_print(char string[], uint8_t row, uint8_t column) {
	for (int i=0; i<strlen(string); i++) {
		oled_print_char(string[i], row, column);
		column = column + font_size;
	}
	
}

void oled_arrow_at_pos(uint8_t row, uint8_t column) {
	oled_pos(row, column);
	write_oled_data(0b00011000);
	write_oled_data(0b01111110);
	write_oled_data(0b00111100);
	write_oled_data(0b00011000);
}
	
void oled_home() {}