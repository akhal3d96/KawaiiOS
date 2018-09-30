#include <stdarg.h>
#include <screen.h>
#include <printk.h>
#include <common.h>

#define STRING_SIZE 1024
#define ASCII_OFFSET 48

static char string_buff[STRING_SIZE];
static int ptr = -1;

int_to_string(unsigned int num, int base)
{
    unsigned int n = num / base;
	int r = num % base;
	if (num >= base)
		int_to_string(n, base);
	string_buff[++ptr] = r+ASCII_OFFSET;
}

void printk(const char *restrict fmt,...)
{
    va_list arg;
    va_start(arg, fmt);
    
    int32_t c;
    char *s;

    while(c = *fmt++)
    {
        if (c != '%')
        {
            print_char(c);
            continue;
        }
        
        switch(c = *fmt++)
        {
            case 'c':
                c = va_arg(arg,int);
                print_char(c);
                break;
            case 's':
                s = va_arg(arg,char *);
                print_string(s);
                break;
            case 'd':
                c = va_arg(arg,int32_t);
                int_to_string(c,10);
                print_string(string_buff);
                ptr = -1;
                memset(string_buff,'\0',STRING_SIZE);
                break;
            case 'x':
                c = va_arg(arg,int32_t);
                int_to_string(c,16);
                print_string(string_buff);
                ptr = -1;
                memset(string_buff,'\0',STRING_SIZE);
                break;
            case 'o':
                c = va_arg(arg,int32_t);
                int_to_string(c,8);
                print_string(string_buff);
                ptr = -1;
                memset(string_buff,'\0',STRING_SIZE);
        }
    }

    va_end(arg);
}