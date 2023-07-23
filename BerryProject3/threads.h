#ifndef THREADS_H
#define THREADS_H

#include "q.h"

struct Queue* RunQ;

void start_thread(void (*function)(int), int a) { 
    
    // allocate a stack (via malloc) of a certain size (choose 8192)
    void *stack = (void *)malloc(8192);

    // allocate a TCB (via malloc)
    TCB_t* item = (TCB_t*) malloc(sizeof(TCB_t));

    // call init_TCB with appropriate arguments
    init_TCB(item, function, stack, 8192, a);

    // call addQ to add this TCB into the “RunQ” which is a global header pointer
    AddQueue(RunQ, item);

}

void run() {	

    ucontext_t parent;	// get a place to store the main context, for faking
    getcontext(&parent);	// magic sauce
    swapcontext(&parent, &(RunQ->head->context));	// start the first thread

}

void yield() {
    
    ucontext_t currContext;
	RotateQ(RunQ);

	getcontext(&currContext);
	swapcontext(&(RunQ->head->prev->context), &RunQ->head->context);

}

#endif 
