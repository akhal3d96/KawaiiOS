#include <screen.h>
#include <string.h>
#include <mm/kheap.h>
#include <thread.h>

int fn1(void *arg);
int fn2(void *arg);
int fn3(void *arg);

void multithreading_test() 
{
    uint32_t *stack1, *stack2, *stack3;
    
    stack1 = (uint32_t*) kmalloc(0x400) + 0x3F0;
	stack2 = (uint32_t*) kmalloc(0x400) + 0x3F0;
	stack3 = (uint32_t*) kmalloc(0x400) + 0x3F0;
	
	memset(stack1 - 0x3F0, 0, 0x400);
	memset(stack2 - 0x3F0, 0, 0x400);
	memset(stack3 - 0x3F0, 0, 0x400);

	create_thread(&fn1, (void*)0x567, stack1);	
	create_thread(&fn2, (void*)0x567, stack2);
	create_thread(&fn3, (void*)0x567, stack3);
}



int fn1(void *arg)
{
	int i;
	for(i=0;i<10;i++) 
	{
		print_char_at(' ',VGA_X_POS,VGA_Y_POS,VGA_COLOR_RED,VGA_COLOR_RED);
		i=0;

	}
  return 0xBAD;
}

int fn2(void *arg)
{
	int i;
	for(i=0;i<10;i++) 
	{
		print_char_at(' ',VGA_X_POS,VGA_Y_POS,VGA_COLOR_GREEN,VGA_COLOR_GREEN);
		i = 0;

	}
  return 0xDAD;
}

int fn3(void *arg)
{
	int i;
	for(i=0;i<10;i++) 
	{
		print_char_at(' ',VGA_X_POS,VGA_Y_POS,VGA_COLOR_BLUE,VGA_COLOR_BLUE);
		i = 0;

	}
  return 0xDAD;
}
