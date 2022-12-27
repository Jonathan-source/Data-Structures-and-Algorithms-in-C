#include "cqueue.h"

const char* cqueue_error_str(cqueue_error error) {
    switch (error) {
    case CQUEUE_SUCCESS:
        return "CQUEUE_SUCCESS";
    case CQUEUE_ERROR_OVERFLOW:
        return "CQUEUE_ERROR_OVERFLOW";
    case CQUEUE_ERROR_NULL_ELEMENT:
        return "CQUEUE_ERROR_NULL_ELEMENT";
    default:
        return "INVALID_CQUEUE_ERROR_CODE";
    }
}

cqueue_t* cqueue_create() {
    cqueue_t* queue = (cqueue_t*)malloc(sizeof(cqueue_t));
    if (!queue) {
        return NULL;
    }
    queue->front = 0; // The front index points to the location of the first element in the queue.
    queue->rear = 0; // The rear index points to the location where the next element will be added to the queue.
    queue->size = 0;
    queue->items = malloc(CQUEUE_MAX_SIZE * sizeof(void*));
    if (!queue->items) {
        free(queue);
        return NULL;
    }
    return queue;
}

void cqueue_destroy(cqueue_t** q) {
    if (q == NULL || *q == NULL) {
        return;
    }
    if ((*q)->items != NULL) {
        free((*q)->items);
        (*q)->items = NULL;
    }
    if (*q != NULL) {
        free(*q);
        *q = NULL;
    }
}

int cqueue_empty(cqueue_t* const q) {
    return q->size == 0;
}

int cqueue_full(cqueue_t* const q) {
    return q->size == CQUEUE_MAX_SIZE;
}

cqueue_error cqueue_enqueue(cqueue_t* const q, void* element) {
    if (q == NULL || element == NULL) {
        return CQUEUE_ERROR_NULL_ELEMENT;
    }
    if (cqueue_full(q)) {
        return CQUEUE_ERROR_OVERFLOW;
    }
    q->items[q->rear] = element;
    q->rear = (q->rear + 1) % CQUEUE_MAX_SIZE;
    q->size++;
    return CQUEUE_SUCCESS;
}

void* cqueue_dequeue(cqueue_t* const q) {
    if (cqueue_empty(q)) {
        return NULL;
    }
    void* element = q->items[q->front];
    q->front = (q->front + 1) % CQUEUE_MAX_SIZE;
    q->size--;
    return element;
}

