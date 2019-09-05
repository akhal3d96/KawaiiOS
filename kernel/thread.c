#include<thread.h>
#include<asm.h>
#include<mm/kheap.h>
#include<printk.h>
#include<string.h>


/* extern struct thread * current_thread; */
uint32_t next_pid = 0;

void thread_exit ();


struct thread * init_threading()
{
    struct thread *t  = kmalloc(sizeof(struct thread));
    memset(t, 0, sizeof(struct thread));
    t->pid = next_pid++;
    /*current_thread = t; */

    return t;

}

void thread_exit ()
{
  register uint32_t val __asm__ ("eax");

  printk ("Thread exited with value %d\n", val);
  hlt();

}

struct thread *create_thread (int (*fn)(void*), void *arg, uint32_t *stack)
{
    struct thread *thread = kmalloc (sizeof (struct thread));
    memset (thread, 0, sizeof (struct thread));
    thread->pid = next_pid++;

    printk ("stack: %x\n", stack);
    *--stack = (uint32_t)arg;
    printk ("stack 1: %x\n", stack);
    *--stack = (uint32_t)&thread_exit;
    printk ("stack 2: %x\n", stack);
    *--stack = (uint32_t)fn;
    printk ("stack 3: %x\n", stack);

    thread->esp = (uint32_t)stack;
    thread->ebp = 0;
    thread->eflags = 0x200;
    make_thread_ready(thread);

    return thread;
}