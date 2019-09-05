#include <scheduler.h>
#include <mm/kheap.h>
#include <string.h>
#include <asm.h>
#include <thread.h>

thread_list_t *ready_queue = 0;
thread_list_t *current_thread = 0;

void init_scheduler(struct thread * initial_thread)
{
    current_thread = (thread_list_t*) kmalloc (sizeof (thread_list_t));
    memset(current_thread, 0, sizeof (thread_list_t));
    current_thread->thread = initial_thread;
    current_thread->next = 0;
    ready_queue = 0;
}

void schedule ()
{
    thread_list_t *new_thread;
    thread_list_t *iterator;
    
    if (!ready_queue) return;

    cli();
    /* Get the last thread */
    iterator = ready_queue;
    while (iterator->next)
        iterator = iterator->next;

    /*  Add the old thread to the end of the queue, and remove it from the start.*/
    iterator->next = current_thread;
    current_thread->next = 0;
    
    new_thread = ready_queue;
    ready_queue = ready_queue->next;

    switch_thread (new_thread);
    sti();

}


void make_thread_ready(struct thread * t)
{
    thread_list_t *iterator;
    thread_list_t *item = (thread_list_t*) kmalloc (sizeof (thread_list_t));
    memset(item, 0, sizeof (thread_list_t));
    item->thread = t;
    item->next = 0;


    if (!ready_queue)
    {
        ready_queue = item;
    }
    else
    { 
        iterator = ready_queue;
        while (iterator->next)
        {
            iterator = iterator->next;
        }
        iterator->next = item;
    }
}

void make_thread_not_ready(struct thread * t)
{
    thread_list_t *tmp;
    thread_list_t *iterator = ready_queue;
    if (iterator->thread == t)
    {
        ready_queue = iterator->next;
        kfree (iterator);
        return;
    }

  while (iterator->next)
  {
    if (iterator->next->thread == t)
    {
      tmp = iterator->next;
      iterator->next = tmp->next;
      kfree (tmp);
    }
    iterator = iterator->next;
  }
}
