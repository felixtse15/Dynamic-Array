#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "dynarray.h"

/**
 * Prints a formatted error message to stderr using the supplied format
 * string and arguments.  A newline is appended to the end of the message.
 * Exits from the program indicating failure.
 *
 * @param format a printf-style format string, and all subsequent arguments
 * must match the types of arguments indicated in the format string.
 */
static void
exit_error(const char* format, ...)
{
	va_list ap;

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
	fprintf(stderr, "\n");
	exit(EXIT_FAILURE);
}

/**
 * Exercises the dynamic array interface.
 */
int
main(void)
{
	// Create a dynamic array of integers.
	DynamicArray* array = dynarray_create(sizeof(int));
	if (array == NULL)
		exit_error("dynarray_create failed");

	int val[] = { 10, 20, 30, 40 };

	// Append elements.
	for (size_t i = 0; i < sizeof(val) / sizeof(val[0]); i++) {
		if (dynarray_append(array, &val[i]) != 0)
			exit_error("dynarray_append of %d failed", val[i]);
	}

	// Test out-of-bounds access.
	int no_element;
	if (dynarray_get(array, 4, &no_element) != -1)
		exit_error("dynarray_get of 4 did not fail");

	size_t len = dynarray_len(array);
	if (len != 4)
		exit_error("dynarray_len returned %zu; expected 4", len);

	// Get and print elements (copying them into the provided pointer).
	for (size_t i = 0; i < len; i++) {
		int element;
		if (dynarray_get(array, i, &element) != 0)
			exit_error("dynarray_get at index %zu failed", i);
		printf("Element at index %zu: %d; expected %d\n",
			i, element, val[i]);
	}

	// Modify the element at index 2.
	val[2] = 50;
	if (dynarray_set(array, 2, &val[2]) != 0)
		exit_error("dynarray_set at index 2 failed");
	int modified_element;
	if (dynarray_get(array, 2, &modified_element) != 0)
		exit_error("dynarray_get at index 2 failed");
	printf("Modified element at index 2: %d; expected %d\n",
		modified_element, val[2]);

	// Pop an element and print the remaining elements.
	if (dynarray_pop(array) != 0)
		exit_error("dynarray_pop failed");
	len = dynarray_len(array);
	if (len != 3)
		exit_error("dynarray_len returned %zu; expected 3", len);
	for (size_t i = 0; i < len; i++) {
		int element;
		if (dynarray_get(array, i, &element) != 0)
			exit_error("dynarray_get at index %zu failed", i);
		printf("Element at index %zu: %d; expected %d\n",
			i, element, val[i]);
	}

	// Append to grow and pop to shrink the dynamic array.
	for (int i = 0; i < 124; i++) {
		if (dynarray_append(array, &i) != 0)
			exit_error("dynarray_append of %d failed", i);
	}
	len = dynarray_len(array);
	if (len != 127)
		exit_error("dynarray_len returned %zu; expected 127", len);
	for (int i = 0; i < 96; i++) {
		if (dynarray_pop(array) != 0)
			exit_error("dynarray_pop failed");
	}
	len = dynarray_len(array);
	if (len != 31)
		exit_error("dynarray_len returned %zu; expected 31", len);

	// Free the dynamic array.
	dynarray_free(array);

	return (EXIT_SUCCESS);
}