#ifndef THREAD_H
#define THREAD_H

#include <stdint.h>
#include <scheduler.h>

struct thread
{
  uint32_t esp, ebp, ebx, esi, edi, eflags;
  uint32_t pid;
};


struct thread *init_threading ();
struct thread *create_thread (int (*fn)(void*), void *arg, uint32_t *stack);

struct thread_list;
void switch_thread (struct thread_list *next);

#endif