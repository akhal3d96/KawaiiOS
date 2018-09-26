#ifndef SCREEN_H
#define SCREEN_H

#include<stdint.h>

extern uint16_t x;
extern uint16_t y;

void print_string(char *str);
void print_char(char c, uint16_t cursor_x , uint16_t cursor_y, uint8_t color);
void cls();

#endif