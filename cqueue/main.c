#include "cqueue.h"

void test_cqueue_ints() {
    // Create a new queue
    cqueue_t* queue = cqueue_create();
    if (queue) {
        printf("cqueue_create: PASS\n");
    }
    else {
        printf("cqueue_create: FAIL\n");
    }

    // Test cqueue_empty on an empty queue
    if (cqueue_empty(queue)) {
        printf("cqueue_empty: PASS\n");
    }
    else {
        printf("cqueue_empty: FAIL\n");
    }

    // Test cqueue_full on an empty queue
    if (cqueue_full(queue)) {
        printf("cqueue_full: FAIL\n");
    }
    else {
        printf("cqueue_full: PASS\n");
    }

    // Test cqueue_dequeue on an empty queue
    if (cqueue_dequeue(queue) == NULL) {
        printf("cqueue_dequeue: PASS\n");
    }
    else {
        printf("cqueue_dequeue: FAIL\n");
    }

    // Test cqueue_enqueue on an empty queue
    int data1 = 1;
    if (cqueue_enqueue(queue, &data1) == CQUEUE_SUCCESS) {
        printf("cqueue_enqueue: PASS\n");
    }
    else {
        printf("cqueue_enqueue: FAIL\n");
    }

    // Test cqueue_empty on a non-empty queue
    if (cqueue_empty(queue)) {
        printf("cqueue_empty: FAIL\n");
    }
    else {
        printf("cqueue_empty: PASS\n");
    }

    // Test cqueue_full on a non-empty queue with room for more elements
    if (cqueue_full(queue)) {
        printf("cqueue_full: FAIL\n");
    }
    else {
        printf("cqueue_full: PASS\n");
    }

    // Test cqueue_dequeue on a non-empty queue
    if (*(int*)cqueue_dequeue(queue) == data1) {
        printf("cqueue_dequeue: PASS\n");
    }
    else {
        printf("cqueue_dequeue: FAIL\n");
    }

    // Test cqueue_enqueue on a queue with room for more elements
    int data2 = 2;
    if (cqueue_enqueue(queue, &data2) == CQUEUE_SUCCESS) {
        printf("cqueue_enqueue: PASS\n");
    }
    else {
        printf("cqueue_enqueue: FAIL\n");
    }

    // Test cqueue_full on a non-empty queue with no room for more elements
    for (int i = 0; i < CQUEUE_MAX_SIZE - 1; i++) {
        cqueue_enqueue(queue, &i);
    }
    if (cqueue_full(queue)) {
        printf("cqueue_full: PASS\n");
    }
    else {
        printf("cqueue_full: FAIL\n");
    }

    // Test cqueue_enqueue on a full queue
    int data3 = 3;
    if (cqueue_enqueue(queue, &data3) == CQUEUE_ERROR_OVERFLOW) {
        printf("cqueue_enqueue: PASS\n");
    }
    else {
        printf("cqueue_enqueue: FAIL\n");
    }

    // Test cqueue_destroy
    cqueue_destroy(&queue);
    if (queue == NULL) {
        printf("cqueue_destroy: PASS\n");
    }
    else {
        printf("cqueue_destroy: FAIL\n");
    }
}

void test_cqueue_strings() {
    // Create a new queue
    cqueue_t* queue = cqueue_create();
    if(queue){
        printf("cqueue_create: PASS\n");
    }
    else {
        printf("cqueue_create: FAIL\n");
    }

    // Test cqueue_enqueue and cqueue_dequeue with strings
    char* str1 = "hello";
    if (cqueue_enqueue(queue, str1) == CQUEUE_SUCCESS) {
        printf("cqueue_enqueue: PASS\n");
    }
    else {
        printf("cqueue_enqueue: FAIL\n");
    }
    if (strcmp(cqueue_dequeue(queue), str1) == 0) {
        printf("cqueue_dequeue: PASS\n");
    }
    else {
        printf("cqueue_dequeue: FAIL\n");
    }

    // Test cqueue_enqueue with multiple strings
    char* str2 = "world";
    char* str3 = "!";
    if (cqueue_enqueue(queue, str2) == CQUEUE_SUCCESS && cqueue_enqueue(queue, str3) == CQUEUE_SUCCESS) {
        printf("cqueue_enqueue: PASS\n");
    }
    else {
        printf("cqueue_enqueue: FAIL\n");
    }

    // Test cqueue_dequeue with multiple strings
    if (strcmp(cqueue_dequeue(queue), str2) == 0 && strcmp(cqueue_dequeue(queue), str3) == 0) {
        printf("cqueue_dequeue: PASS\n");
    }
    else {
        printf("cqueue_dequeue: FAIL\n");
    }

    // Test cqueue_destroy
    cqueue_destroy(&queue);
    if (queue == NULL) {
        printf("cqueue_destroy: PASS\n");
    }
    else {
        printf("cqueue_destroy: FAIL\n");
    }
}

void test_cqueue_capacity()
{
    cqueue_t* queue = cqueue_create();
    if (queue) {
        printf("cqueue_create: PASS\n");
    }
    else {
        printf("cqueue_create: FAIL\n");
    }

    int counter = 0;
    for (; counter < CQUEUE_MAX_SIZE; counter++) {
        int* element = (int*)malloc(sizeof(int));
        if (element == NULL) {
            fprintf(stderr, "Error: unable to allocate memory for element\n");
            return;
        }
        *element = counter;

        cqueue_error error = cqueue_enqueue(queue, element);
        if (error == CQUEUE_SUCCESS) {
            printf("cqueue_enqueue [%d]: PASS\n", *(int*)element);
        }
        else if (error == CQUEUE_ERROR_OVERFLOW) {
            printf("cqueue_enqueue [%d]: FAIL\n", *(int*)element);
        }
        else {
            printf("cqueue_enqueue [%d]: %s\n", *(int*)element, cqueue_error_str(error));
        }
    }

    // Check if queue is full
    if (cqueue_full(queue)) {
        printf("cqueue_full: PASS\n");
    }
    else {
        printf("cqueue_full: FAIL\n");
    }

    // Check if additional element can be added to queue
    int* element = (int*)malloc(sizeof(int));
    if (element == NULL) {
        fprintf(stderr, "Error: unable to allocate memory for element\n");
        return;
    }
    *element = CQUEUE_MAX_SIZE;

    cqueue_error error = cqueue_enqueue(queue, element);
    if (error == CQUEUE_ERROR_OVERFLOW) {
        printf("cqueue_enqueue: PASS\n");
    }
    else {
        printf("cqueue_enqueue: FAIL\n");
        printf("%s: \n", cqueue_error_str(error));
    }
    free(element);

    // Free memory
    for (counter = 0; counter < CQUEUE_MAX_SIZE; counter++) {
        int* element = (int*)cqueue_dequeue(queue);

        if (element != NULL) {
            printf("cqueue_dequeue [%d]: PASS\n", counter);
            free(element);
        }
        else {
            printf("cqueue_dequeue [%d]: FAIL\n", counter);
        }
    }

    // Test cqueue_destroy
    cqueue_destroy(&queue);
    if (queue == NULL) {
        printf("cqueue_destroy: PASS\n");
    }
    else {
        printf("cqueue_destroy: FAIL\n");
    }
}

int main() {
    printf("STARTING CQUEUE INT TESTS:\n");
    test_cqueue_ints();
    printf("\nSTARTING CQUEUE STRING TESTS:\n");
    test_cqueue_strings();
    printf("\nSTARTING CQUEUE CAPACITY TESTS:\n");
    test_cqueue_capacity();
    return 0;
}