/* timer.c -- Initialises the PIT, and handles clock updates.*/
/*            Written for JamesM's kernel development tutorials.*/

#include <timer.h>
#include <isr.h>
#include <screen.h>
/* #include <stdbool.h>*/
uint32_t tick = 0;

static void timer_callback( /*registers_t regs */ )
{
	tick++;
	/* print_string("Tick: "); */
	/* print_char_at(tick+48,x,y,0); */
	/* print_char_at('\n',x,y,0); */
}

void init_timer(uint32_t frequency)
{
	uint32_t divisor;
	uint8_t l;
	uint8_t h;

	/* Firstly, register our timer callback. */
	register_interrupt_handler(IRQ0, &timer_callback);

	/* The value we send to the PIT is the value to divide it's input clock */
	/* (1193180 Hz) by, to get our required frequency. Important to note is */
	/* that the divisor must be small enough to fit into 16-bits. */

	divisor = 1193180 / frequency;

	/* Send the command byte. */
	outb(0x43, 0x36);

	/* Divisor has to be sent byte-wise, so split here into upper/lower bytes. */
	l = (uint8_t) (divisor & 0xFF);
	h = (uint8_t) ((divisor >> 8) & 0xFF);

	/* Send the frequency divisor. */
	outb(0x40, l);
	outb(0x40, h);

	/* print_string("[*] Timer initiated\n"); */
}
