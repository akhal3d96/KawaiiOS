#include <mm/kmem.h>
#include <mm/paging.h>
#include <stdint.h>
#include <stdbool.h>
#include <mm/memory.h>
#include <asm.h>
#include <printk.h>

extern uint32_t placement_address;
extern uint32_t *frames;
extern uint32_t nframes;

/*
* `index` and `offset` are used interchangeably in this file.
*/
static void set_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / FRAME_SIZE;
	uint32_t bucket = INDEX_OF_BUCKET(frame);
	uint32_t offset = frame & MASK;

	frames[bucket] |= (1 << offset);
}

void clear_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / FRAME_SIZE;
	uint32_t bucket = frame >> BITS_WS;
	uint32_t offset = frame & MASK;

	frames[bucket] &= ~(1 << offset);
}
/*
static uint32_t test_frame(uint32_t frame_addr)
{
	uint32_t frame = frame_addr / FRAME_SIZE;
	uint32_t bucket = frame >> BITS_WS;
	uint32_t offset = frame & MASK;

	return (frames[bucket] & (1 << offset));
}
*/
static uint32_t first_frame()
{
	uint32_t bucket;
	uint32_t index;

	for (bucket = 0; bucket < INDEX_OF_BUCKET(nframes); bucket++) {
		if (frames[bucket] != UINT32_MAX) {
			for (index = 0; index < BUCKET_SIZE; index++) {
				/* Free frame, get it! */
				if ((frames[bucket] & (1 << index)) == 0) {
					return bucket * BUCKET_SIZE + index;
				}
			}
		}
	}
	printk("why?!\n");
	hlt();
	return 0;
}

void allocate_frame(struct page *p, int is_kernel, int is_writeable)
{
	/* Ignore already allocated page */
	if (p->frame != 0) {
		return;
	} else {
		uint32_t index = first_frame();

		/* 
		* FIXME: Change this behavior.
		* There's no free memoey, kernel panic! 
		*/
		if (index == (uint32_t) - 1) {
			printk("No free memeory\n");
			hlt();

		} else {
			set_frame(index * FRAME_SIZE);

			p->present = 1;
			p->user = !is_kernel;
			p->rw = is_writeable;
			p->frame = index;
		}
	}
}

uint32_t kmalloc_a(uint32_t size)
{
	uint32_t tmp = placement_address;
	placement_address = (placement_address + size + 0x1000) & 0xFFFFF000;

	return tmp;
}

/* 
* kmalloc _ap(uint32_t size) allocates memory 
* with alignment the same as kmalloc but it
* returns the physical address.
*/
uint32_t kmalloc_ap(uint32_t size, uint32_t * physical)
{
	uint32_t tmp;

	placement_address = (placement_address + size + 0x1000) & 0xFFFFF000;

	*physical = placement_address;

	tmp = placement_address;

	placement_address += size;

	return tmp;
}
