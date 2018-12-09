#ifndef KHEAP_H
#define KHEAP_H

#include <stdint.h>
#include <stdbool.h>

#include <utilis/bst.h>

#define KHEAP_MAGIC         0xBADDAD
#define KHEAP_END           0xFFBFF000
#define KHEAP_INITIAL_SIZE  0x100000
#define HEAP_INDEX_SIZE     0x20000
#define HEAP_MIN_SIZE       0x70000

struct header {
	uint32_t size;
	bool is_hole;
	struct header *next, *prev;
};

struct heap {
	/*struct bst index; */
	uint32_t start_address;
	uint32_t end_address;

	uint32_t max_address;

	bool supervisor;
	bool readonly;
};

struct heap *create_heap(uint32_t start_address, uint32_t end_address,
			 uint32_t max_address, bool supervisor, bool readonly);

void split_chunk(struct header *chunk, uint32_t size);
void allocate_chunk(uint32_t addr, uint32_t size);
void *kmalloc(uint32_t size);
void kfree(void *address, struct heap *heap);

#endif
