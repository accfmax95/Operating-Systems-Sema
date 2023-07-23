#ifndef TCB_H
#define TCB_H

#include <ucontext.h>
#include <string.h>

typedef struct TCB_t {
     
    struct TCB_t     *next;
    struct TCB_t     *prev;
    ucontext_t      context;
    int thread_id;
} TCB_t;



void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size, int a)
{
    memset(tcb, '\0', sizeof(TCB_t));       
    getcontext(&tcb->context);              
    tcb->context.uc_stack.ss_sp = stackP;
    tcb->context.uc_stack.ss_size = (size_t) stack_size;
    makecontext(&tcb->context, function, 1, a);
}

#endif

