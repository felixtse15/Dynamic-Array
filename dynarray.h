#ifndef DYNARRAY_H
#define DYNARRAY_H

#include <stddef.h>

// Struct representing a dynamic array
typedef struct DynamicArray DynamicArray;

/**
 * Creates a dynamic array.
 *
 * @param element_size Size of each element in the array.
 * @return Pointer to the created DynamicArray, or NULL if memory allocation
 * fails.
 */
DynamicArray* dynarray_create(size_t element_size);

/**
 * Gets an element from the dynamic array.
 *
 * @param array Pointer to the DynamicArray.
 * @param index Index of the element to get.
 * @param destination Pointer to the memory where the element will be copied.
 * @return 0 on success, -1 if the index is out of bounds.
 */
int dynarray_get(DynamicArray* array, size_t index, void* destination);

/**
 * Sets an element in the dynamic array.
 *
 * @param array Pointer to the DynamicArray.
 * @param index Index of the element to set.
 * @param element Pointer to the element to set.
 * @return 0 on success, -1 if the index is out of bounds.
 */
int dynarray_set(DynamicArray* array, size_t index, void* element);

/**
 * Appends an element to the dynamic array.
 *
 * @param array Pointer to the DynamicArray.
 * @param element Pointer to the element to append.
 * @return 0 on success, -1 if memory allocation fails.
 */
int dynarray_append(DynamicArray* array, void* element);

/**
 * Pops an element from the dynamic array.
 *
 * @param array Pointer to the DynamicArray.
 * @return 0 on success, -1 if the array is empty.
 */
int dynarray_pop(DynamicArray* array);

/**
 * Returns the length of the dynamic array.
 *
 * @param array Pointer to the DynamicArray.
 * @return length of the array.
 */
size_t dynarray_len(DynamicArray* array);

/**
 * Frees the dynamic array.
 *
 * @param array Pointer to the DynamicArray to free.
 */
void dynarray_free(DynamicArray* array);

#endif // DYNARRAY_H