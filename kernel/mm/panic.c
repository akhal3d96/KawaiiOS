#include <screen.h>
#include <printk.h>
#include <isr.h>
#include <asm.h>
#include <mm/panic.h>

void PANIC(struct registers * regs)
{
    uint32_t cr0, cr2, cr3;
    
    uint8_t attributeByte;
    uint16_t character;
	uint16_t i;

    uint16_t *vidmem = (uint16_t *) VIDEO_ADDRESS;

    
    char *msg = "\nA problem has been detected and your operating system has been shut down to\n\
prevent damage to your computer.\n\
If this the first time you've seen this Stop error screen, restart your computer.\n\
Technical information:";
    
    __asm__ volatile("movl    %%cr0,        %%eax":"=a"(cr0 ));
    __asm__ volatile("movl    %%cr2,        %%eax":"=a"(cr2 ));
    __asm__ volatile("movl    %%cr3,        %%eax":"=a"(cr3 ));

    screen_colorize(BLACK);
    printk(msg);

    printk("\n CS : 0x%x     EIP: 0x%x     EF : 0x%x     ERR: 0x%x",
           regs->cs, regs->eip, regs->eflags, regs->err_code);
    printk("\n SS : 0x%x     ESP: 0x%x              ",
           regs->ss, regs->esp);
    printk("\n");
    printk("\n CONTROL REGISTERS:");
    printk("\n -------------------");
    printk("\n CR0: 0x%x     CR2: 0x%x     CR3: 0x%x              ",
           cr0, cr2, cr3);
    printk("\n");
    printk("\n GENERAL REGISTERS:");
    printk("\n -------------------");
    printk("\n EAX: 0x%x     EBX: 0x%x     ECX: 0x%x     EDX: 0x%x",
           regs->eax, regs->ebx, regs->ecx, regs->edx);
    printk("\n ESI: 0x%x     EDI: 0x%x     EBP: 0x%x              ",
           regs->esi, regs->edi, regs->ebp);
    printk("\n");
    printk("\n SEGMENT SELECTORS:");
    printk("\n -------------------");
    printk("\n DS : 0x%x",
           regs->ds);
    printk("\n");
    printk("\n CALL STACK:");
    printk("\n ------------");
    printk("\n EIP: 0x%x", regs->eip);

	attributeByte =
	    (BLUE << 4) | (15 & WHITE);
	character = 0x0 | (attributeByte << 8);

	for (i = 0; i < 80 * 25; i++) {
		vidmem[i] = vidmem[i] | character;
	}
    /*
    for (i = 0; i < 4; i++) {
        printk(" <-- 0x%x", ((int32_t*)regs->ebp)[1]);
        regs->ebp = ((int32_t*)regs->ebp)[0];
    }*/
    /*screen_back_only_colorize(BLUE);*/
    hlt();
}