#ifndef SEM_H
#define SEM_H

#include <ucontext.h>
#include <string.h>
#include "threads.h"

typedef struct Semaphore {
    
    int item;
    Queue* semQ;
} Semaphore;

void P(Semaphore* Semaphore) {

    struct TCB_t* temp;
    while (Semaphore -> item <= 0) {
        
        if(checkEmpty(RunQ) != true){
            
            
        } else {

            exit(0);
        }

        temp = DelQueue(RunQ);
        AddQueue(Semaphore -> semQ, temp); 
        swapcontext(&(temp -> context), &(RunQ -> head -> context));   
    }

  Semaphore -> item--;
}

void V(Semaphore* Semaphore) {

	struct TCB_t *tcb;

    if (checkEmpty(Semaphore -> semQ) == true){

	    Semaphore -> item++;
    } else {

        struct TCB_t *semThread = DelQueue(Semaphore -> semQ);
	    AddQueue(RunQ, semThread);
        Semaphore -> item++;
    }

}

void InitSem(Semaphore* Semaphore, int val) {
    
    Semaphore -> semQ = (struct Queue*)malloc(sizeof(struct Queue));
    Semaphore -> item = val;
}

#endif