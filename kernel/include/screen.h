#ifndef SCREEN_H
#define SCREEN_H

#include<stdint.h>

#define  VIDEO_ADDRESS 0xb8000
#define  MAX_ROWS  25
#define  MAX_COLS  80
#define  WHITE_ON_BLACK 0x0f

/*  Screen  device I/O ports*/
#define  REG_SCREEN_CTRL 0x3D4
#define  REG_SCREEN_DATA 0x3D5

enum COLOR {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	BROWN,
	GRAY,
	DARK_GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_PURPLE,
	YELLOW,
	WHITE
};

extern uint16_t x;
extern uint16_t y;

void print_string(char *str);
void print_string_blue(char *str);
void print_char(char c);
void cls();
void screen_colorize(uint8_t back_color);

void print_char_at(char c, uint16_t cursor_x, uint16_t cursor_y, uint8_t back_color, uint8_t fore_color);

#endif
