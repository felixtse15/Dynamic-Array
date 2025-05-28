#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dynarray.h"

// The initial capacity of a dynamic array
#define INITIAL_CAPACITY 2

// Struct representing a dynamic array
struct DynamicArray {
	size_t element_size;
	size_t current_size;
	size_t capacity;
	void* data;
};

// Function to create a dynamic array
/**
 * Creates a dynamic array.
 *
 * @param element_size Size of each element in the array.
 * @return Pointer to the created DynamicArray, or NULL if memory allocation
 * fails.
 */
DynamicArray* dynarray_create(size_t element_size) {
	
	struct DynamicArray* p;
	
	 
	 if ((p = malloc(sizeof(struct DynamicArray))) == NULL) {
		 printf("Memory allocation failed");
		 return NULL;
	 }

	 p->element_size = element_size;
	 p->current_size = 0;
	 p->capacity = INITIAL_CAPACITY;
	 p->data = calloc(p->capacity, element_size);

	 if ((p->data) == NULL) {
		 printf("Data allocation failed");
		 free(p);
		 return NULL;
	 }
	 
	 return p;
}

// Function to get an element from the dynamic array and copy it into the
// provided pointer
// Gets an element from the dynamic array.
// @param array Pointer to the DynamicArray.
// @param index Index of the element to get.
// @param destination Pointer to the memory where the element will be copied.
// @return 0 on success, -1 if the index is out of bounds.

int dynarray_get(DynamicArray* array, size_t index, void* destination) {
	
	if ((array->data) == NULL) {
		return(-1);
	}
	if (index >= array->current_size) {
		return(-1);
	}

	char* from = ((char *)array->data) + (index * (array->element_size)); // base address (first byte of the data) plus the byte offset (data size)

	memcpy(destination, from, array->element_size); //memcpy because we dont care about overlap src to destination
	return (0);
}

// Function to set an element in the dynamic array
/**
 * Sets an element in the dynamic array.
 *
 * @param array Pointer to the DynamicArray.
 * @param index Index of the element to set.
 * @param element Pointer to the element to set.
 * @return 0 on success, -1 if the index is out of bounds.
 */
int dynarray_set(DynamicArray* array, size_t index, void* element) {

	if ((array->data) == NULL) {
		return(-1);
	}

	if (index >= array->current_size) {
		return(-1);
	}

	char* to = ((char*)array->data) + (index
		* (array->element_size));

	memmove(to, element, array->element_size);
	return(0);
}

// Function to append an element to the dynamic array
	/*
	 * Hint: Be careful how you handle realloc(array->data, ...) failing.
	 * You should ensure that the existing data referenced by array->data
	 * is not lost.
	 */
	 // check if current size equal to capacity
	 // if yes, double capacity
	 // append element to array
	 // increment current size by 1
int dynarray_append(DynamicArray* array, void* element) {

	
	if (array->current_size == array->capacity) {
		array->capacity = ((array->capacity) == 0) ? 1 : (array->capacity) * 2;
	}

	void* temp = realloc(array->data, (array->capacity) * (array->element_size)); //realloc may return a new pointer, use a temp variable

	if (temp == NULL) {
		return (-1);
	}
	else {
		array->data = temp;
	}
	

	char* append = ((char*)array->data) + ((array->current_size) * (array->element_size));
	memmove(append, element, array->element_size);
	(array->current_size)++;
	return (0);

}

// Function to pop an element from the dynamic array
int dynarray_pop(DynamicArray* array) {

	if (array->current_size <= (array->capacity / 4)) {
		void* temp = realloc(array->data, (array->capacity / 2) * (array->element_size));
		if (temp == NULL) {
			return(-1);
		}
		else {
			array->data = temp;
		}
	}

	// pop last element from array by changing current size
	(array->current_size--);
	return (0);
}

// Function to get the length of the dynamic array
size_t dynarray_len(DynamicArray* array) {
	return (array->current_size);
}

// Function to free the dynamic array
void dynarray_free(DynamicArray* array) {
	free(array->data);
}