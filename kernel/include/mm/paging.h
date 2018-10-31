#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <isr.h>

struct page {
	uint32_t present:1;	/*      Page present in memory                         		*/
	uint32_t rw:1;		/*      Read-only if clear, readwrite if set                */
	uint32_t user:1;	/*      Supervisor level only if clear                      */
	uint32_t accessed:1;/*      Has the page been accessed since last refresh?  	*/
	uint32_t dirty:1;	/*      Has the page been written to since last refresh? 	*/
	uint32_t unused:7;	/*      Amalgamation of unused and reserved bits            */
	uint32_t frame:20;	/*      Frame address (shifted right 12 bits)               */
};

struct page_table {
	struct page pages[1024];
};

struct page_directory {
	uint32_t tables_physical[1024];
	uint32_t physical_address;
	struct page_table *tables[1024];
};

void initialise_paging();

void switch_page_directory(struct page_directory *new_pd);

struct page *get_page(uint32_t address, struct page_directory *pd);
struct page *create_page(uint32_t address, struct page_directory *pd);

#endif
