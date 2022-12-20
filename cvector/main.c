#include "cvector.h"
#include <time.h>
#include <assert.h>

void test_vector_push_at() {
    cvector_t* v = cvector_new();
    int* x = malloc(sizeof(int));
    *x = 1;
    cvector_push_back(v, x);
    x = malloc(sizeof(int));
    *x = 2;
    cvector_push_back(v, x);
    x = malloc(sizeof(int));
    *x = 3;
    cvector_push_back(v, x);
    assert(*((int*)cvector_at(v, 0)) == 1);
    assert(*((int*)cvector_at(v, 1)) == 2);
    assert(*((int*)cvector_at(v, 2)) == 3);
    cvector_free(v);
}

void test_vector_set() {
    cvector_t* v = cvector_new();
    int* x = malloc(sizeof(int));
    *x = 1;
    cvector_push_back(v, x);
    x = malloc(sizeof(int));
    *x = 2;
    cvector_push_back(v, x);
    x = malloc(sizeof(int));
    *x = 3;
    cvector_push_back(v, x);
    x = malloc(sizeof(int));
    *x = 4;
    cvector_set(v, 1, x);
    assert(*((int*)cvector_at(v, 0)) == 1);
    assert(*((int*)cvector_at(v, 1)) == 4);
    assert(*((int*)cvector_at(v, 2)) == 3);
    cvector_free(v);
}

void test_vector_insert_remove() {
    cvector_t* v = cvector_new();
    int* x = malloc(sizeof(int));
    *x = 1;
    cvector_push_back(v, x);
    x = malloc(sizeof(int));
    *x = 2;
    cvector_push_back(v, x);
    x = malloc(sizeof(int));
    *x = 3;
    cvector_push_back(v, x);
    x = malloc(sizeof(int));
    *x = 4;
    cvector_insert(v, 1, x);
    assert(*((int*)cvector_at(v, 0)) == 1);
    assert(*((int*)cvector_at(v, 1)) == 4);
    assert(*((int*)cvector_at(v, 2)) == 2);
    assert(*((int*)cvector_at(v, 3)) == 3);
    cvector_remove(v, 2);
    assert(*((int*)cvector_at(v, 0)) == 1);
    assert(*((int*)cvector_at(v, 1)) == 4);
    assert(*((int*)cvector_at(v, 2)) == 3);
    cvector_free(v);
}

int main(void) {
    printf("Running tests...\n");
    clock_t start = clock();
    test_vector_push_at();
    test_vector_set();
    test_vector_insert_remove();
    clock_t stop = clock();
    double elapsed_time = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("All tests passed!\n");
    printf("Time elapsed: %f seconds\n", elapsed_time);
    return EXIT_SUCCESS;
}