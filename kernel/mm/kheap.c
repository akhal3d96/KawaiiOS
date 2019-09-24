#include<mm/kheap.h>
#include<mm/kmem.h>
#include<mm/paging.h>
#include<mm/memory.h>
#include<stdint.h>
#include<string.h>

uint32_t heap_max = KHEAP_START;

struct header *heap_first = 0;

void * kmalloc(uint32_t size)
{
	uint32_t chunk_start;
	struct header *curr_header, *prev_header;

	size += sizeof(struct header);

	curr_header = heap_first;
	prev_header = 0;

	while (curr_header) {
		/* We have found a hole which satisfies our request */
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

void kfree(void * address)
{
	/* Pointer to the block's header */
	struct header * block_header =  (struct header *)((uint32_t)address - sizeof(struct header));
	block_header->is_hole = true;

	/* coalesce the block */
	coalesce_block(block_header);
}

void free_chunk(struct header * block_header)
{
	struct page * p;

	block_header->prev->next = NULL;

	if(block_header->prev == NULL)
	{
		/* We went back to our initial state: an empty heap */
		heap_first = 0;	
	}
	/* Check if the decreamen in the heap size is larger than or q */
	while( (heap_max-KHEAP_INDEX_SIZE) >= (uint32_t)block_header)
	{
		heap_max-=KHEAP_INDEX_SIZE;
		p = get_page(heap_max, kernel_pd);
		clear_frame(p->frame);
	}
}

void coalesce_block(struct header * block_header)
{
	/* left coalesce */
	if (block_header->prev && block_header->prev->is_hole)
	{
		block_header->size += block_header->prev->size;
		
		/* As if we are deleteing a node in a linked list*/
		block_header->prev->next = block_header->next;
		/* And vice versa! */
		block_header->next->prev = block_header->prev;

		block_header = block_header->prev;
	}

	/* right coalesce */
	if (block_header->next && block_header->next->is_hole)
	{
		/* The same rules apply. */
		block_header->size += block_header->next->size;
		block_header->next = block_header->next->next;
		block_header->next->next->prev = block_header;
	}

	/* 
	* We won't free its frame pages nor reduce the heap size
	* it, even if we stumbled upon it again we will simply split it.
	* 
	* We will reduce the heap size, only when the free()'ed block
	* resides at the end of the heap. 
	*/
	if(!block_header->next)
	{
		free_chunk(block_header);
	}
}