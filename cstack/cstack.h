#ifndef CSTACK_H
#define CSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

const char* cstack_error_str(enum cstack_error error) {
    switch (error) {
    case CSTACK_SUCCESS:
        return "CSTACK_SUCCESS";
    case CSTACK_ERROR_MALLOC:
        return "CSTACK_ERROR_MALLOC";
    case CSTACK_ERROR_OVERFLOW:
        return "CSTACK_ERROR_OVERFLOW";
    case CSTACK_ERROR_UNDERFLOW:
        return "CSTACK_ERROR_UNDERFLOW";
    case CSTACK_ERROR_NULL_STACK:
        return "CSTACK_ERROR_NULL_STACK";
    case CSTACK_ERROR_NULL_ELEMENT:
        return "CSTACK_ERROR_ELEMENT";
    default:
        return "INVALID_CSTACK_ERROR_CODE";
    }
}

typedef struct {
    void* data;
    unsigned long long element_size;
    int elements;
    enum cstack_error error;
}cstack_t;

cstack_t* cstack_create(unsigned long long element_size) {
    if (element_size == 0) {
        return NULL;
    }

    cstack_t* stack = (cstack_t*)malloc(sizeof(cstack_t));
    if (stack == NULL) {
        return NULL;
    }

    stack->element_size = element_size;
    stack->elements = -1;
    stack->data = (void*)malloc(stack->element_size * CSTACK_MAX_SIZE);
    if (stack->data == NULL) {
        free(stack);
        return CSTACK_ERROR_MALLOC;
    }

    return stack;
}

int cstack_empty(cstack_t* stack) {
    return stack->elements == -1;
}

int cstack_full(cstack_t* stack) {
    return stack->elements == CSTACK_MAX_SIZE - 1;
}

enum cstack_error cstack_push(cstack_t* stack, const void* element) {
    if (stack == NULL) {
        return CSTACK_ERROR_NULL_STACK;
    }
    if (element == NULL) {
        return CSTACK_ERROR_NULL_ELEMENT;
    }
    if (cstack_full(stack)) {
        return CSTACK_ERROR_OVERFLOW;
    }
    stack->elements++;
    memcpy((char*)stack->data + (stack->elements * stack->element_size), element, stack->element_size);
    return CSTACK_SUCCESS;
}

enum cstack_error cstack_pop(cstack_t* stack, void** element) {
    if (cstack_empty(stack)) {
        return CSTACK_ERROR_UNDERFLOW;
    }
    *element = (char*)stack->data + (stack->elements-- * stack->element_size);
    return CSTACK_SUCCESS;
}

void cstack_free(cstack_t* stack) {
    if (stack == NULL) {
        return;
    }
    free(stack->data);
    free(stack);
}

#endif // CSTACK_H
