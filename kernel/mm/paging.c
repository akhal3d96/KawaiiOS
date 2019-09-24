#include <mm/paging.h>
#include <mm/kmem.h>
#include <stdint.h>
#include <string.h>
#include <isr.h>
#include <mm/memory.h>
#include <mm/panic.h>
#include <printk.h>

uint32_t placement_address = (uint32_t) & end;
struct page_directory *current_pd = 0;
struct page_directory *kernel_pd = 0;
uint32_t *frames;
uint32_t nframes;

void page_fault(registers_t * regs)
{
	printk("\npage_fault(): %x\n", regs->eip);
	PANIC(regs);
}

void initialise_paging(uint32_t memory_size)
{
	uint32_t frame_addr = 0;
	nframes = memory_size / FRAME_SIZE;

	/* 
	 * Set frames to be an array of integers of the size of the
	 * required bitarray that has the status of the memory frames
	 * whether a particular frame was allocated (used) or not.
	 * 
	 * INDEX_OF_BUCKET(v) get the the number of inetegrs required
	 * to map the whole memory. 
	 */
	frames = (uint32_t *) kmalloc_a(INDEX_OF_BUCKET(nframes));
	memset(frames, 0, INDEX_OF_BUCKET(nframes));

	/* Allocate memory for the Page Directory */
	kernel_pd =
	    (struct page_directory *)kmalloc_a(sizeof(struct page_directory));
	memset(kernel_pd, 0, sizeof(struct page_directory));
	current_pd = kernel_pd;

	/*
	 * Align the placement_address, with 4 KiB alignment, 
	 * which represents the end of the kernel.
	 */
	placement_address = (placement_address + 0x1000) & 0xFFFFF000;

	for (frame_addr = KHEAP_START; frame_addr < (KHEAP_START + 0x10000);
	     frame_addr += 0x1000) {
		create_page(frame_addr, kernel_pd);
	}

	/* 
	 * Map virtual addresses of the kernel to direct physical addresses. 
	 * We will loop through every address from the begining of the kernel 
	 * to the end of the kernel heap allocating a frame and also a page for it.
	 */

	for (frame_addr = 0; frame_addr < placement_address;
	     frame_addr += 0x1000) {
		allocate_frame(create_page(frame_addr, kernel_pd), true, true);

	}

	for (frame_addr = KHEAP_START; frame_addr < (KHEAP_START + 0x10000);
	     frame_addr += 0x1000) {
		allocate_frame(create_page(frame_addr, kernel_pd), true, true);
	}

	register_interrupt_handler(14, &page_fault);

	/* Enable paging */
	switch_page_directory(kernel_pd);

}

void switch_page_directory(struct page_directory *pd)
{

	uint32_t cr0;
	current_pd = pd;
	__asm__ volatile ("mov %0, %%cr3"::"r" (&current_pd->tables_physical));

	__asm__ volatile ("mov %%cr0, %0":"=r" (cr0));
	cr0 |= 0x80000000;
	__asm__ volatile ("mov %0, %%cr0"::"r" (cr0));

}

struct page * create_page(uint32_t address, struct page_directory *pd)
{

	uint32_t tmp;
	uint32_t table_index;

	/* FIXME: optimize */
	if (get_page(address, pd) != 0) {
		return get_page(address, pd);
	}
	address /= 0x1000;
	table_index = address / 1024;
	/*printk("address=%d, table_index=%d, placement_address=%d\n",address,table_index,placement_address); */

	pd->tables[table_index] =
	    (struct page_table *)kmalloc_ap(sizeof(struct page_table), &tmp);
	pd->tables_physical[table_index] = tmp | 0x7;

	return &pd->tables[table_index]->pages[address % 1024];
}

struct page * get_page(uint32_t address, struct page_directory *pd)
{
	uint32_t table_index;
	address /= 0x1000;
	table_index = address / 1024;

	if (pd->tables[table_index]) {
		return &pd->tables[table_index]->pages[address % 1024];
	}

	return 0;
}
