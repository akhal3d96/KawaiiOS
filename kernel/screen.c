#include <stdint.h>
#include <stdbool.h>
#include <asm.h>
#include <screen.h>

uint16_t x = 0;
uint16_t y = 0;

uint16_t *vidmem = (uint16_t *) VIDEO_ADDRESS;

void move_cursor(uint16_t cursor_x, uint16_t cursor_y)
{
	uint16_t cursorLocation;

	x = cursor_x;
	y = cursor_y;

	cursorLocation = cursor_y * 80 + cursor_x;

	outb(0x3D4, 14);	/* Tell the VGA board we are setting the high cursor byte. */
	outb(0x3D5, cursorLocation >> 8);	/* Send the high cursor byte. */
	outb(0x3D4, 15);	/* Tell the VGA board we are setting the low cursor byte. */
	outb(0x3D5, cursorLocation);	/* Send the low cursor byte. */
}

 /*FIXME*/ uint16_t get_cursor()
{
	/* outb(REG_SCREEN_CTRL , 14); */
	/* uint16_t  offset = port_byte_in(REG_SCREEN_DATA) << 8; */
	/* outb(REG_SCREEN_CTRL , 15); */
	/* offset  |=  port_byte_in(REG_SCREEN_DATA ); */

	return x * y;

}

void cls()
{
	screen_colorize((uint8_t) BLACK);
}

void screen_colorize(uint8_t back_color)
{
	/* Make an attribute byte for the default colours */
	uint8_t attributeByte;
	uint16_t blank;

	uint16_t cursor_x;
	uint16_t cursor_y;

	uint16_t i;

	attributeByte = (back_color << 4) | (15 & WHITE);
	blank = 0x20 /* space */  | (attributeByte << 8);

	for (i = 0; i < 80 * 25; i++) {
		vidmem[i] = blank;
	}

	/* Move the hardware cursor back to the start. */
	cursor_x = 0;
	cursor_y = 0;
	move_cursor(cursor_x, cursor_y);
}

static bool scroll()
{

	uint8_t attributeByte;
	uint16_t blank;

	attributeByte = (BLACK << 4) | (15 & WHITE_ON_BLACK);
	blank = 0x20 /* space */  | (attributeByte << 8);

	/* Row 25 is the end, this means we need to scroll up */
	if (y >= 24) {
		/* Move the current text chunk that makes up the screen */
		/* back in the buffer by a line */
		uint16_t i;
		for (i = 0; i < 24 * 80; i++) {
			vidmem[i] = vidmem[i + 80];
		}

		/* The last line should now be blank. Do this by writing */
		/* 80 spaces to it. */
		for (i = 24 * 80; i < 25 * 80; i++) {
			vidmem[i] = blank;
		}
		/* The cursor should now be on the last line. */
		y = 23;
		return true;
	}

	return false;
}

void print_char(char c)
{
	print_char_at(c, x, y, (uint8_t) BLACK, (uint8_t) WHITE);
}

void print_char_at(char c, uint16_t cursor_x, uint16_t cursor_y,
		   uint8_t back_color, uint8_t fore_color)
{
	/* The attribute byte is made up of two nibbles - the lower being the */
	/* foreground colour, and the upper the background colour. */
	uint8_t attributeByte = (back_color << 4) | (fore_color & WHITE);

	/* The attribute byte is the top 8 bits of the word we have to send to the */
	/* VGA board. */
	uint16_t attribute = attributeByte << 8;

	uint16_t blank;

	uint16_t location;

	/* FIXME */
	/*
	   if (cursor_x >= 0 && cursor_y >= 0) {
	   location = cursor_y * 80 + cursor_x;
	   } else {
	 */
	cursor_y = y;
	cursor_x = x;
	location = y * 80 + x;
	/*
	   }
	 */

	/* Handle a backspace, by moving the cursor back one space */
	if (c == 0x08 && cursor_x) {
		cursor_x--;
		blank = 0x20 /* space */  | (attributeByte << 8);
		vidmem[cursor_y * 80 + cursor_x] = blank;
	}

	/* Handle a tab by increasing the cursor's X, but only to a point */
	/* where it is divisible by 8. */
	else if (c == 0x09) {
		cursor_x = (cursor_x + 8) & ~(8 - 1);
	}

	/* Handle carriage return */
	else if (c == '\r') {
		cursor_x = 0;
	}

	/* Handle newline by moving cursor back to left and increasing the row */
	else if (c == '\n') {
		cursor_x = 0;
		cursor_y++;
	}
	/* Handle any other printable character. */
	else if (c >= ' ') {
		vidmem[location] = c | attribute;
		cursor_x++;
	}

	/* Check if we need to insert a new line because we have reached the end */
	/* of the screen. */
	if (cursor_x >= 80) {
		cursor_x = 0;
		cursor_y++;
	}

	/* Scroll the screen if needed. */
	if (scroll()) {
		cursor_y = y;

	}

	/* Move the hardware cursor. */
	move_cursor(cursor_x, cursor_y);

}

void print_string(char *str)
{
	uint16_t i = 0;
	while (str[i]) {
		print_char_at(str[i], x, y, (uint8_t) BLACK, (uint8_t) WHITE);
		i++;
	}
}

void print_string_blue(char *str)
{
	uint16_t i = 0;
	while (str[i]) {
		print_char_at(str[i], x, y, (uint8_t) BLUE, (uint8_t) WHITE);
		i++;
	}
}
