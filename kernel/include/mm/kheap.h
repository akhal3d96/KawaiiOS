#ifndef KHEAP_H
#define KHEAP_H

#include <stdint.h>
#include <stdbool.h>

#define KHEAP_END           0xFFBFF000
#define KHEAP_INITIAL_SIZE  0x100000
#define KHEAP_START 		0xCC0000
#define KHEAP_INDEX_SIZE	0x1000 

/*#define HEAP_INDEX_SIZE     0x20000
#define HEAP_MIN_SIZE       0x70000*/

struct header {
	uint32_t size;
	bool is_hole;
	struct header *next, *prev;
};

void split_chunk(struct header *chunk, uint32_t size);
void allocate_chunk(uint32_t addr, uint32_t size);
void *kmalloc(uint32_t size);
void kfree(void *address);
void coalesce_block(struct header * block_header);
#endif
