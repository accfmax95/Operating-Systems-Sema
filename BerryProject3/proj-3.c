#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sem.h"

Semaphore *sem1, *sem2, *sem3;
int read, write, readerCount, writerCount, readerWriterCount, writerWriterCount, input, globalVar = 0;

void reader(int id);
void writer(int id);
int main() {
    
    RunQ = (struct Queue *) malloc(sizeof(struct Queue));
    sem1 = (struct Semaphore *) malloc(sizeof(struct Semaphore));
	sem2 = (struct Semaphore *) malloc(sizeof(struct Semaphore));
	sem3 = (struct Semaphore *) malloc(sizeof(struct Semaphore));

    int i = 0;
    scanf("%d,%d", &read, &write);

	InitQueue(RunQ);
    InitSem(sem1, 0);
	InitSem(sem2, 0);
	InitSem(sem3, 1);

    i = 0;
    int total = read + write;
    while (i < total) {

        int id;
        scanf("%d", &id);
        if (id <= 0) {

            start_thread(writer, id);
        } else {
            
            start_thread(reader, id);
        }

        i++;
    }

    run();
    return 0;
}

void reader(int readerID){

  	struct TCB_t *temp;
  	
	if (writerWriterCount <= 0 && writerCount <= 0) {
        
		
	} else {

        readerWriterCount++;
        P(sem2);
        readerWriterCount--;
    }

	readerCount++;

	printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, globalVar);
	yield();	
	printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, globalVar);
	
	
	readerCount--;
	if (readerCount == 0 && writerWriterCount > 0) {

	    V(sem1);
	}
	
	temp = DelQueue(RunQ);
	swapcontext(&(temp -> context), &(RunQ -> head -> context));
}	

void writer(int writerID){
	
    struct TCB_t *temp;
		
	if (readerCount <= 0 && writerCount <= 0 && readerWriterCount <= 0 && writerWriterCount <= 0) {
        
        
	} else {

        writerWriterCount++;
        P(sem1);
        writerWriterCount--;
    }

	writerCount++;
    globalVar++;
    
    printf("\n This is the %d th writer writing value i = %d \n", -writerID, globalVar);
    yield();
    printf("\n This is the %d th writer verifying value i = %d \n", -writerID, globalVar);
				
	writerCount--;
	if (readerWriterCount > 0) {

        int i = 0;
        while (i < readerWriterCount) {

            V(sem2);
            i++;
        }
	} else if (writerWriterCount > 0) {	
	    
        V(sem1);
	}

	temp = DelQueue(RunQ);
	swapcontext(&(temp -> context), &(RunQ -> head -> context));
}
