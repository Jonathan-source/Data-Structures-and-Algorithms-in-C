#include "cstack.h"

#include <assert.h>

void test_stack() {

    cstack_t* stack = cstack_create(sizeof(int));;    
    if (stack == NULL) {
        printf("Error creating stack\n");
        return;
    }

    // Test push and pop
    int a = 1;
    enum cstack_error error = cstack_push(stack, &a);
    if (error != CSTACK_SUCCESS) {
        printf("Error pushing to stack: %s\n", cstack_error_str(error));
        return;
    }
    int b = 2;
    error = cstack_push(stack, &b);
    if (error != CSTACK_SUCCESS) {
        printf("Error pushing to stack: %s\n", cstack_error_str(error));
        return;
    }
    int c = 3;
    error = cstack_push(stack, &c);
    if (error != CSTACK_SUCCESS) {
        printf("Error pushing to stack: %s\n", cstack_error_str(error));
        return;
    }
    void* item;
    error = cstack_pop(stack, &item);
    if (error != CSTACK_SUCCESS) {
        printf("Error popping from stack: %s\n", cstack_error_str(error));
        return;
    } 
    assert(*(int*)item == 3);

    error = cstack_pop(stack, &item);
    if (error != CSTACK_SUCCESS) {
        printf("Error popping from stack: %s\n", cstack_error_str(error));
        return;
    }
    assert(*(int*)item == 2);

    error = cstack_pop(stack, &item);
    if (error != CSTACK_SUCCESS) {
        printf("Error popping from stack: %s\n", cstack_error_str(error));
        return;
    }
    assert(*(int*)item == 1);
    assert(cstack_empty(stack));

    // Test stack overflow
    for (int i = 0; i < CSTACK_MAX_SIZE; i++) {
        error = cstack_push(stack, &i);
        if (error != CSTACK_SUCCESS) {
            printf("Error pushing to stack: %s\n", cstack_error_str(error));
            return;
        }
        printf("%d\n", i);
    }
    assert(cstack_full(stack));

    error = cstack_pop(stack, &item);
    if (error != CSTACK_SUCCESS) {
        printf("Error popping from stack: %s\n", cstack_error_str(error));
        return;
    }
    printf("%d\n", *(int*)item);
    assert(*(int*)item == CSTACK_MAX_SIZE - 1);

    while (!cstack_empty(stack)) {
        error = cstack_pop(stack, &item);
        if (error != CSTACK_SUCCESS) {
            printf("Error poping from stack: %s\n", cstack_error_str(error));
            return;
        }
    }
    assert(cstack_empty(stack));

    // Test stack underflow
    error = cstack_pop(stack, &item);
    if (error != CSTACK_ERROR_UNDERFLOW) {
        printf("Error popping from stack: %s\n", cstack_error_str(error));
        return;
    }

    cstack_free(&stack);
    if (stack != NULL) {
        printf("Error deallocating stack\n");
    }

    printf("All tests passed\n");
}

int main() {
    test_stack();
    return 0;
}
