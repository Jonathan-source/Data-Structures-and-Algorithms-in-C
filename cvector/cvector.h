#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdio.h>
#include <stdlib.h>

#ifndef CVECTOR_INITIAL_CAPACITY
    #define CVECTOR_INITIAL_CAPACITY 100
#endif // CVECTOR_INITIAL_CAPACITY

#ifndef CVECTOR_GROWTH_FACTOR
    #define CVECTOR_GROWTH_FACTOR 2
#endif // CVECTOR_GROWTH_FACTOR

typedef struct {
    void** data;
    unsigned int size;
    unsigned int capacity;
} cvector_t;

/// @brief Creates a new cvector with a capacity of 'CVECTOR_INITIAL_CAPACITY'
/// @return cvector_t
cvector_t* cvector_new();

/// @brief Frees the memory used by the given cvector
/// @param v is the given cvector_t
void cvector_free(cvector_t* v);

/// @brief Resizes the capacity of the given cvector
/// @param v is the given cvector_t
/// @param new_capacity is the new capacity
void cvector_resize(cvector_t* v, unsigned int new_capacity);

/// @brief Appends an element to the end of a cvector_t
/// @param v is the given cvector_t
/// @param element is the new element
void cvector_push_back(cvector_t* v, void* element);

/// @brief Return the element at a given index in the given cvector_t
/// @param v is the given cvector_t
/// @param index is the given index
/// @return the element at a given index
void* cvector_at(cvector_t* v, int index);

/// @brief Set the element at a given index the given cvector_t
/// @param v is the given cvector_t
/// @param index is the given index
/// @param element is the new element
void cvector_set(cvector_t* v, int index, void* element);

/// @brief Insert an element at a given index the given cvector_t
/// @param v is the given cvector_t
/// @param index is the given index
/// @param element is the new element
void cvector_insert(cvector_t* v, int index, void* element);

/// @brief Removes the element at a given index the given cvector_t
/// @param v is the given cvector_t
/// @param index is the given index
void cvector_remove(cvector_t* v, int index);

#endif // CVECTOR_H
