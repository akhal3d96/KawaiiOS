#include <stdint.h>
#include <isr.h>
#include <common.h>
#include <printk.h>
#include <drivers/keyboard/ps2.h>


void keyboard_init()
{   
    outb(0x21,inb(0x21)&0xfd);
    register_interrupt_handler(IRQ1,&keyboard_handler);
}

void keyboard_handler(registers_t regs) {
	scan_code = inb(0x60);

	(*key_way[scan_code&0x7f])(scan_code);

    /*key has been handled, send ACK*/
    int com = 0;
    outb(0x61, (com=inb(0x61))|0x80);
    outb(0x61, com&0x7f);
    outb(0x20,0x20);

    old_scan_code = scan_code;

}



void key_c()
{  
    if(scan_code & 0x80)
    {
        return;
    }
    char c = key_map[scan_code & 0x7F][shift_p];
    printk("%c",c);
    // printk("scan_code: %d  character: %c\n",scan_code & 0x80,c);
}

void shift()
{
    shift_p ^= 1;
}

/* TODO :))))))) */

void unp(){}
void fun(){}
void alt(){}
void control(){}