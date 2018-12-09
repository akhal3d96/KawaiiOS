#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <mm/paging.h>
/* 
* The end location of the kernel in memory
* defined by the linker (See kernel/linker.ld)
*/
extern uint32_t end;

extern uint32_t placement_address;

extern struct page_directory *current_pd;
extern struct page_directory *kernel_pd;

extern uint32_t *frames;
uint32_t nframes;

/* 
* FIXME
* Assume 16 Mib memory. The memory size should be passed from 
* the bootloader.
*/
#define MEMORY_SIZE 0x1000000
#define KHEAP_START 0xCC0000

#endif
