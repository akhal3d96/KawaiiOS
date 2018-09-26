#include "screen.h"
#include "descriptor_tables.h"
#include "timer.h"
#include "isr.h"

void keyboard_hanfler(registers_t regs);

void kernel_main() {

    cls();
    print_string("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n");
    print_string("+\t\t\t\t\t\t\t+\n");
    print_string("=\t\t\t\t\t\t\t=\n");
    print_string("+\t\t\t\t\t\t\t+\n");
    char *msg = "+ Welcome to KawaiiOS, the eduactional operating system =\n";
    print_string(msg);

    char *author = "= By: Ahmed Khaled <nemoload@aol.com>\t\t\t+\n";
    print_string(author);
    print_string("+\t\t\t\t\t\t\t+\n");
    print_string("=\t\t\t\t\t\t\t=\n");
    print_string("+\t\t\t\t\t\t\t=\n");
    print_string("=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=\n\n\n");
    
 
    init_descriptor_tables();
    char *gdt = "[*] Global Descriptor Table updated\n";
    print_string(gdt);
    char *idt = "[*] Interrupt Descriptor Table crated\n";
    print_string(idt);

    register_interrupt_handler(IRQ1,&keyboard_hanfler);

    char *ps2 = "[*] PS/2 driver is ready\n";
    print_string(ps2);

    asm ("sti");
    // uint16_t freq = 44000;
    // init_timer(freq);
    // uint8_t mask = 4;
    // outb(0x60,0xED|mask);
}

void keyboard_hanfler(registers_t regs)
{
    print_string("key pressed: ");
    uint8_t scan_code = inb(0x60);
    
    print_char((char)scan_code+48,x,y,0);
    print_char('\n',x,y,0);
    /*key has been handled*/
    int com = 0;
    outb(0x61, (com=inb(0x61))|0x80);
    outb(0x61, com&0x7f);
    outb(0x20,0x20);

}