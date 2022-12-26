#ifndef CSTACK_H
#define CSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef CSTACK_MAX_SIZE
#define CSTACK_MAX_SIZE 100
#endif // CSTACK_MAX_SIZE

enum cstack_error {
    CSTACK_SUCCESS,
    CSTACK_ERROR_MALLOC,
    CSTACK_ERROR_OVERFLOW,
    CSTACK_ERROR_UNDERFLOW,
    CSTACK_ERROR_NULL_STACK,
    CSTACK_ERROR_NULL_ELEMENT
};

const char* cstack_error_str(enum cstack_error error);


typedef struct {
    void* data;
    unsigned long long element_size;
    int elements;
} cstack_t;

cstack_t* cstack_create(unsigned long long element_size);

int cstack_empty(cstack_t* stack);

int cstack_full(cstack_t* stack);

enum cstack_error cstack_push(cstack_t* stack, const void* element);

enum cstack_error cstack_pop(cstack_t* stack, void** element);

void cstack_free(cstack_t* stack);

#endif // CSTACK_H
