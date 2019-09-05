#ifndef SCHEDULAR_H
#define SCHEDULAR_H

#include <thread.h>

typedef struct thread_list
{
  struct thread *thread;
  struct thread_list *next;
} thread_list_t;


void init_scheduler (struct thread *initial_thread);
void make_thread_ready (struct thread *t);
void make_thread_not_ready (struct thread *t);
void schedule ();

#endif