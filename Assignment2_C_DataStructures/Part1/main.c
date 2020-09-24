// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "myqueue.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

// Print Queue
// Print the information about the queue.
void print_queue(queue_t *q) {
	if (q == NULL) {
		printf("NULL pointer detected\n");
	} else {
		printf("-+ print queue info:\n");
		printf(" |- capacity:%d\tsize:%d\n", (*q).capacity, (*q).size);
		printf(" |- front   :%d\tback:%d\n\n", (*q).front, (*q).back);
	}
}

// A sample test of your program
// You can add as many unit tests as you like
// We will be adding our own to test your program.
void unitTest1() {
	printf("==========Test 1==========\n");
	queue_t *test1 = create_queue(1);
	printf("Intialize queue\n");
	print_queue(test1);
	printf("Attempting to add %d\n", 1);
	queue_enqueue(test1, 1);
	print_queue(test1);
	printf("Removing: %d\n", queue_dequeue(test1));
	print_queue(test1);
	free_queue(test1);
}

// This test is commented out since it tests if the program will exit under
// certain abnormal situation.
void unitTest2() {
	printf("==========Test 2==========\n");
	printf("Initialize queue with capacity 0.\n");
	// Get a NULL pointer.
	queue_t *test = create_queue(0);
	printf("Address: %p\n", test);
	printf("queue_empty: %d\n", queue_empty(test));
	printf("queue_full: %d\n", queue_full(test));

	// EXIT_FAILURE.
	// printf("queue_dequeue: %d\n", queue_dequeue(test));
	// printf("queue_size:%d\n", queue_size(test));
	// Free a NULL pointer is safe.
	free_queue(test);
}

/* Fill, empty, refill, then empty again. */
void unitTest3() {
	printf("==========Test 3==========\n");
	queue_t *test = create_queue(3);
	printf("Initialize queue\n");
	print_queue(test);
	int i = 0;
	for (i = 0; i < 3; i++) {
		printf("enqueue %d\n", i);
		queue_enqueue(test, i);
		print_queue(test);
	}
	printf("-+ full %d empty %d\n", queue_full(test), queue_empty(test));
	printf("If add 4, we get:");
	printf("%d\n", queue_enqueue(test, 4));
	print_queue(test);

	for (i = 0; i < 3; i++) {
		printf("dequeue:%d\n", queue_dequeue(test));
		print_queue(test);
	}
	printf("-+ full %d empty %d\n", queue_full(test), queue_empty(test));

	for (i = 0; i < 3; i++) {
		int add = i + 3;
		printf("enqueue %d\n", add);
		queue_enqueue(test, add);
		print_queue(test);
	}
	for (i = 0; i < 3; i++) {
		printf("dequeue:%d\n", queue_dequeue(test));
		print_queue(test);
	}

	free_queue(test);
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
