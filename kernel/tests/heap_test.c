#include <stdint.h>
#include <mm/kheap.h>

void heap_test()
{
    uint32_t *a, *b, *c;
    a = kmalloc(1);
	printk("a: %x\n",a);
	b = kmalloc(1);
	printk("a: %x\tb: %x\n",a,b);
	kfree(a);
	c = kmalloc(1);
	printk("b: %x\tc: %x\n",b,c);
}