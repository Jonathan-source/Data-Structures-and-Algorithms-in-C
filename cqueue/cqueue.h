#ifndef CQUEUE_H
#define CQUEUE_H

/*
* CIRCULAR QUEUE
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifndef CQUEUE_MAX_SIZE
// todo: the implementation can only hold CQUEUE_MAX_SIZE - 1 items atm.
#define CQUEUE_MAX_SIZE 100
#endif // CQUEUE_MAX_SIZE

typedef enum {
    CQUEUE_SUCCESS,
    CQUEUE_ERROR_OVERFLOW,
    CQUEUE_ERROR_NULL_ELEMENT
} cqueue_error;

const char* cqueue_error_str(cqueue_error error);

typedef struct {
    int front;
    int rear;
    int size;
    void**items;
} cqueue_t;

cqueue_t* cqueue_create();

void cqueue_destroy(cqueue_t** q);

int cqueue_empty(cqueue_t* const q);

int cqueue_full(cqueue_t* const q);

cqueue_error cqueue_enqueue(cqueue_t* const q, void* element);

void* cqueue_dequeue(cqueue_t* const q);

#endif // CQUEUE_H

