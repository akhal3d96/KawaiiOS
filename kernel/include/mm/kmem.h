#ifndef KMEM_H
#define KMEM_H

#include <stdint.h>
#include <stdbool.h>
#include <mm/paging.h>

#define FRAME_SIZE 0x1000	/*  4 KiB     */
#define BUCKET_SIZE  0x20	/*  32 Bit    */
#define BITS_WS    5		/*  2^5 = 32  */
#define MASK       0x1F

#define INDEX_OF_BUCKET(v) (v >> BITS_WS)

uint32_t kmalloc_a(uint32_t size);
uint32_t kmalloc_ap(uint32_t size, uint32_t * physical);

void allocate_frame(struct page *p, int is_kernel, int is_writeable);
void clear_frame(uint32_t frame_addr);

#endif
