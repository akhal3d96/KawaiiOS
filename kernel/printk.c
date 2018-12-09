#include <stdarg.h>
#include <screen.h>
#include <printk.h>
#include <string.h>
#include <asm.h>

#define STRING_SIZE 1024
#define ASCII_OFFSET 48

static char string_buff[STRING_SIZE];
static int ptr = -1;

static void int_to_string(unsigned int num, unsigned int base)
{
	unsigned int n = num / base;
	int r = num % base;
	if (num >= base)
		int_to_string(n, base);
	string_buff[++ptr] = "0123456789ABCDEF"[r];
}

void printk(const char *__restrict__ fmt, ...)
{
	int32_t c;
	char *s;

	va_list arg;
	va_start(arg, fmt);

	while ((c = *fmt++)) {
		if (c != '%') {
			print_char(c);
			continue;
		}

		switch (c = *fmt++) {
		case 'c':
			c = va_arg(arg, int);
			print_char(c);
			break;
		case 's':
			s = va_arg(arg, char *);
			print_string(s);
			break;
		case 'd':
			c = va_arg(arg, int32_t);
			int_to_string(c, 10);
			print_string(string_buff);
			ptr = -1;
			memset(string_buff, '\0', STRING_SIZE);
			break;
		case 'x':
			c = va_arg(arg, int32_t);
			int_to_string(c, 16);
			print_string("0x");
			print_string(string_buff);
			ptr = -1;
			memset(string_buff, '\0', STRING_SIZE);
			break;
		case 'o':
			c = va_arg(arg, int32_t);
			int_to_string(c, 8);
			print_string(string_buff);
			ptr = -1;
			memset(string_buff, '\0', STRING_SIZE);
		}
	}

	va_end(arg);
}
