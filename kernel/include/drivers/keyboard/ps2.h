#ifndef PS2_H
#define PS2_H

#include <isr.h>

static char shift_p __attribute__((used)) = 0;
static uint8_t scan_code __attribute__((used));

void shift();
void unp();
void fun();
void alt();
void control();
void key_c();

void keyboard_handler();

static const char key_map[0x3a][2] = {
	/*00 */ {0x0, 0x0}, {0x0, 0x0}, {'1', '!'}, {'2', '@'},
	/*04 */ {'3', '#'}, {'4', '$'}, {'5', '%'}, {'6', '^'},
	/*08 */ {'7', '&'}, {'8', '*'}, {'9', '('}, {'0', ')'},
	/*0c */ {'-', '_'}, {'=', '+'}, {'\b', '\b'}, {'\t', '\t'},
	/*10 */ {'q', 'Q'}, {'w', 'W'}, {'e', 'E'}, {'r', 'R'},
	/*14 */ {'t', 'T'}, {'y', 'Y'}, {'u', 'U'}, {'i', 'I'},
	/*18 */ {'o', 'O'}, {'p', 'P'}, {'[', '{'}, {']', '}'},
	/*1c */ {'\n', '\n'}, {0x0, 0x0}, {'a', 'A'}, {'s', 'S'},
	/*20 */ {'d', 'D'}, {'f', 'F'}, {'g', 'G'}, {'h', 'H'},
	/*24 */ {'j', 'J'}, {'k', 'K'}, {'l', 'L'}, {';', ':'},
	/*28 */ {'\'', '\"'}, {'`', '~'}, {0x0, 0x0}, {'\\', '|'},
	/*2c */ {'z', 'Z'}, {'x', 'X'}, {'c', 'C'}, {'v', 'V'},
	/*30 */ {'b', 'B'}, {'n', 'N'}, {'m', 'M'}, {',', '<'},
	/*34 */ {'.', '>'}, {'/', '?'}, {0x0, 0x0}, {'*', '*'},
	/*38 */ {0x0, 0x0}, {' ', ' '}

};

static void (*key_way[0x80])() __attribute__((used)) = {
	/*00 */ unp, unp, key_c, key_c, key_c, key_c, key_c, key_c,
	/*08 */ key_c, key_c, key_c, key_c, key_c, key_c, key_c, key_c,
	/*10 */ key_c, key_c, key_c, key_c, key_c, key_c, key_c, key_c,
	/*18 */ key_c, key_c, key_c, key_c, key_c, control, key_c, key_c,
	/*20 */ key_c, key_c, key_c, key_c, key_c, key_c, key_c, key_c,
	/*28 */ key_c, key_c, shift, key_c, key_c, key_c, key_c, key_c,
	/*30 */ key_c, key_c, key_c, key_c, key_c, key_c, shift, key_c,
	/*38 */ alt, key_c, unp, fun, fun, fun, fun, fun,
	/*40 */ fun, fun, fun, fun, fun, unp, unp, unp,
	/*48 */ unp, unp, unp, unp, unp, unp, unp, unp,
	/*50 */ unp, unp, unp, unp, unp, unp, unp, fun,
	/*58 */ fun, unp, unp, unp, unp, unp, unp, unp,
	/*60 */ unp, unp, unp, unp, unp, unp, unp, unp,
	/*68 */ unp, unp, unp, unp, unp, unp, unp, unp,
	/*70 */ unp, unp, unp, unp, unp, unp, unp, unp,
	/*78 */ unp, unp, unp, unp, unp, unp, unp, unp,
};

void keyboard_init();

#endif
