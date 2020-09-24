// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "mystack.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


// Print Stack
// Print the content of the stack.
void print_stack(stack_t *s) {
	if (s == NULL) {
		printf("-+ NULL pointer detected\n");
	} else {
		printf("-+ capacity:%d\tcount:%d\n | ", (*s).capacity, (*s).count);
		node_t *head = (*s).head;
		while (head != NULL) {
			printf("%d>", (*head).data);
			head = (*head).next;
		}
		printf("NULL\n\n");
	}
}

// A sample test of your program
// You can add as many unit tests as you like
// We will be adding our own to test your program.
void unitTest1() {
	printf("\n==========Test 1==========\n");
	stack_t *test1 = create_stack(MAX_DEPTH);
	printf("Attempting to push %d\n", 1);
	stack_enqueue(test1, 1);
	printf("Removing: %d\n", stack_dequeue(test1));

	free_stack(test1);
}

// Test enqueue and dequeue.
void unitTest2() {
	printf("\n==========Test 2==========\n");
	stack_t *test = create_stack(3);
	print_stack(test);
	int i = 0;
	// The 4th enqueue fails since the capacity is 3.
	for (i = 0; i < 4; i++) {
		printf("enqueue %d, result:%d", i, stack_enqueue(test, i));
		printf("\tsize:%d\n", stack_size(test));
	}
	printf("Is it full: %d\n", stack_full(test));
	printf("Is it empty: %d\n", stack_empty(test));
	print_stack(test);
	for (i = 0; i < 3; i++) {
		printf("dequeue: %d size:%d\n", stack_dequeue(test), stack_size(test));
		print_stack(test);
	}
	printf("Is it full: %d\n", stack_full(test));
	printf("Is it empty: %d\n", stack_empty(test));
	free_stack(test);
}

// Test edge cases.
void unitTest3() {
	printf("\n==========Test 3==========\n");
	printf("Initialize a stack with 0 capacity.\n");
	stack_t *test = create_stack(0);
	printf("Get address: %p\n", test);
	printf("Is it full: %d\n", stack_full(test));
	printf("Is it empty: %d\n", stack_empty(test));
}

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main() {

	// List of Unit Tests to test your data structure
	unitTest1();
	unitTest2();
	unitTest3();

	return 0;
}
