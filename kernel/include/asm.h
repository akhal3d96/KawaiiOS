#ifndef ASM_H
#define ASM_H 

#include <stdint.h>

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

void hlt();
void cli();
void sti();

#endif