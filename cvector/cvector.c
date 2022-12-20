#include "cvector.h"

cvector_t* cvector_new() {
    cvector_t* v = (cvector_t*)malloc(sizeof(cvector_t));
    v->data = malloc(CVECTOR_INITIAL_CAPACITY * sizeof(void*));
    v->size = 0;
    v->capacity = CVECTOR_INITIAL_CAPACITY;
    return v;
}

void cvector_free(cvector_t* v) {
    free(v->data);
    free(v);
}

void cvector_resize(cvector_t* v, unsigned int new_capacity) {
    void** new_data = realloc(v->data, new_capacity * sizeof(void*));
    if (new_data) {
        v->data = new_data;
        v->capacity = new_capacity;
    }
}

void cvector_push_back(cvector_t* v, void* element) {
    if (v->size == v->capacity) {
        cvector_resize(v, v->capacity * CVECTOR_GROWTH_FACTOR);
    }
    v->data[v->size++] = element;
}

void* cvector_at(cvector_t* v, int index) {
    if (index >= 0 && index < v->size) {
        return v->data[index];
    }
    else {
        fprintf(stderr, "%s: index out of bounds\n", __func__);
        exit(1);
    }
}

void cvector_set(cvector_t* v, int index, void* element) {
    if (index >= 0 && index < v->size) {
        v->data[index] = element;
    }
    else {
        fprintf(stderr, "%s: index out of bounds\n", __func__);
        exit(1);
    }
}

void cvector_insert(cvector_t* v, int index, void* element) {
    if (index < 0 || index > v->size) {
        fprintf(stderr, "%s: index out of bounds\n", __func__);
        exit(1);
    }
    if (v->size == v->capacity) {
        cvector_resize(v, v->capacity * CVECTOR_GROWTH_FACTOR);
    }
    for (int i = v->size; i > index; i--) {
        v->data[i] = v->data[i - 1];
    }
    v->data[index] = element;
    v->size++;
}

void cvector_remove(cvector_t* v, int index) {
    if (index < 0 || index >= v->size) {
        fprintf(stderr, "%s: index out of bounds\n", __func__);
        exit(1);
    }
    for (int i = index; i < v->size - 1; i++) {
        free(v->data[i]);
        v->data[i] = v->data[i + 1];
    }
    v->size--;
    if (v->size > 0 && v->size == v->capacity / 4) {
        cvector_resize(v, v->capacity / 2);
    }
}