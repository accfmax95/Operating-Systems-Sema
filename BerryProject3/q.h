#ifndef Q_H
#define Q_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "TCB.h"

typedef struct Queue {

	  TCB_t* head;
} Queue;

bool checkEmpty(Queue* head);
void InitQueue(Queue* temp) {

  temp -> head = NULL;
}

void AddQueue(Queue* head, TCB_t* temp) {
 
    if (checkEmpty(head) != true) {
    
        temp -> next = head -> head;
        temp -> prev = head -> head -> prev;
        head -> head -> prev -> next = temp ;
        head -> head -> prev = temp ;

    } else {
    
        head -> head = temp;
        temp -> prev = temp;
        temp -> next = temp;
    }
}

TCB_t* DelQueue(Queue* head) {
  
  if (checkEmpty(head) == false) {
    
    TCB_t* temp = head -> head;
    if (temp -> next != temp) {
      
        head -> head -> prev -> next = head -> head -> next;
        head -> head -> next -> prev = head -> head -> prev;
        
        head -> head = head -> head -> next;
        temp -> next = temp -> prev = NULL;
    } else {

        head -> head = NULL;
    }

	  return temp;
  }
}

void RotateQ(Queue* head) {
  
  if (checkEmpty(head) == false) {
    
    head -> head = head -> head -> next;
  }
}

bool checkEmpty(Queue* head) {
  
  bool returnVal = false;
  if (head -> head != NULL) {
      
    returnVal = false;
  } else {

    returnVal =  true;
  }

  return returnVal;
}

#endif