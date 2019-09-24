#ifndef SCREEN_H
#define SCREEN_H

#include <stdint.h>

#define  VIDEO_ADDRESS 0xB8000
#define  VGA_HEIGHT  25
#define  VGA_WIDTH   80
#define  WHITE_ON_BLACK 0x0F

/*  Screen  device I/O ports*/
#define  REG_SCREEN_CTRL 0x3D4
#define  REG_SCREEN_DATA 0x3D5

extern uint16_t VGA_X_POS;
extern uint16_t VGA_Y_POS;

enum VGA_COLOR {
	VGA_COLOR_BLACK,
	VGA_COLOR_BLUE,
	VGA_COLOR_GREEN,
	VGA_COLOR_CYAN,
	VGA_COLOR_RED,
	VGA_COLOR_PURPLE,
	VGA_COLOR_BROWN,
	VGA_COLOR_GRAY,
	VGA_COLOR_DARK_GRAY,
	VGA_COLOR_LIGHT_BLUE,
	VGA_COLOR_LIGHT_GREEN,
	VGA_COLOR_LIGHT_CYAN,
	VGA_COLOR_LIGHT_RED,
	VGA_COLOR_LIGHT_PURPLE,
	VGA_COLOR_YELLOW,
	VGA_COLOR_WHITE
};


void print_string(char *str);
void print_char(char c);
void cls();
void screen_colorize(uint8_t back_color);

void print_char_at(char c, uint16_t cursor_x, uint16_t cursor_y,
		   uint8_t back_color, uint8_t fore_color);

#endif
