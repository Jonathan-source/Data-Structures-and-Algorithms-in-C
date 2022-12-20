#include "vec2.h"

#include <assert.h>
#include <time.h>

// Test the vec2_add function
void test_vec2_add() {
    vec2 v1 = vec2_new(1, 2);
    vec2 v2 = vec2_new(3, 4);
    vec2 v3 = vec2_add(v1, v2);
    assert(v3.x == 4 && v3.y == 6);
}

// Test the vec2_sub function
void test_vec2_sub() {
    vec2 v1 = vec2_new(1, 2);
    vec2 v2 = vec2_new(3, 4);
    vec2 v3 = vec2_sub(v1, v2);
    assert(v3.x == -2 && v3.y == -2);
}

// Test the vec2_mul function
void test_vec2_mul() {
    vec2 v1 = vec2_new(1, 2);
    vec2 v2 = vec2_mul(v1, 2);
    assert(v2.x == 2 && v2.y == 4);
}

// Test the vec2_dot function
void test_vec2_dot() {
    vec2 v1 = vec2_new(1, 2);
    vec2 v2 = vec2_new(3, 4);
    double d = vec2_dot(v1, v2);
    assert(d == 11);
}

// Test the vec2_len function
void test_vec2_len() {
    vec2 v1 = vec2_new(3, 4);
    double len = vec2_len(v1);
    assert(fabs(len - 5) < 1.0E-6);
}

// Test the vec2_normalize function
void test_vec2_normalize() {
    vec2 v1 = vec2_new(3, 4);
    vec2 v2 = vec2_normalize(v1);
    double len = vec2_len(v2);
    assert(fabs(len - 1) < 1.0E-6);
}

int main(void) {
    printf("Running tests...\n");
    clock_t start = clock();
    test_vec2_add();
    test_vec2_sub();
    test_vec2_mul();
    test_vec2_dot();
    test_vec2_len();
    test_vec2_normalize();
    clock_t stop = clock();
    double elapsed_time = (double)(stop - start) / CLOCKS_PER_SEC;
    printf("All tests passed\n");
    printf("Time elapsed: %f seconds\n", elapsed_time);
    return 0;
}