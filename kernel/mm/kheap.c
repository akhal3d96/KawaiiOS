#include<mm/kheap.h>
#include<mm/kmem.h>
#include<mm/paging.h>
#include<mm/memory.h>
#include<utilis/bst.h>
#include<stdint.h>

uint32_t heap_max = KHEAP_START;

struct header *heap_first = 0;

void *kmalloc(uint32_t size)
{
	uint32_t chunk_start;
	struct header *curr_header, *prev_header;

	size += sizeof(struct header);

	curr_header = heap_first;
	prev_header = 0;

	while (curr_header) {
		if (curr_header->is_hole == true && curr_header->size >= size) {
			split_chunk(curr_header, size);
			curr_header->is_hole = false;	/* It's a block now */

			return (void *)((uint32_t) curr_header +
					sizeof(struct header));
		}
		prev_header = curr_header;
		curr_header = curr_header->next;
	}

	/*
	 * We haven't found any hole sufficent enough for our requested size,
	 * which can happen in two scenarios
	 *   1. We haven't initialized our heap, yet.
	 *   2. We simply don't have any holes to allocate them as blocks. 
	 */

	if (prev_header)
		chunk_start = (uint32_t) prev_header + prev_header->size;
	else {
		/* Initializing the heap */
		chunk_start = KHEAP_START;
		heap_first = (struct header *)chunk_start;
	}

	/* Increase the kernel heap size enough to get the requested hole/block. */
	allocate_chunk(chunk_start, size);

	curr_header = (struct header *)chunk_start;
	curr_header->size = size;
	curr_header->is_hole = false;
	curr_header->next = 0;
	curr_header->prev = prev_header;

	prev_header->next = curr_header;

	return (void *)(chunk_start + sizeof(struct header));
}

void split_chunk(struct header *chunk, uint32_t size)
{
	/* 
	 * Make sure that the splitted chucnk has enough space
	 * for our header.
	 */
	if (chunk->size - size > sizeof(struct header)) {
		struct header *new_chunk =
		    (struct header *)((uint32_t) chunk + chunk->size);
		new_chunk->prev = chunk;
		new_chunk->next = 0;
		new_chunk->is_hole = true;
		new_chunk->size = chunk->size - size;

		chunk->next = new_chunk;
		chunk->size = size;
	}
}

void allocate_chunk(uint32_t addr, uint32_t size)
{
	while ((addr + size) > heap_max) {
		allocate_frame(create_page(heap_max, kernel_pd), true, true);
		heap_max += 0x1000;
	}

}
