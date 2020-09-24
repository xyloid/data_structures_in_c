// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_dll.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

// ====================================================
// ================== Program Entry ===================
// ====================================================

// Print the count of the DLL, and print the whole list
// form head to tail, and from tail to head.
void print_dll(dll_t *l) {
	if (l) {
		printf("\n__________\n");
		printf("\tCount: %u\tHead:%p\tTail:%p\n", dll_size(l), (*l).head,
		       (*l).tail);
		if (dll_size(l) > 0) {
			printf("\tPrint from the head:\n\t");
			node_t *head = (*l).head;
			while (head) {
				printf("%d,", (*head).data);
				head = (*head).next;
			}
			printf("\n");
			printf("\tPrint from the tail:\n\t");
			node_t *tail = (*l).tail;
			while (tail) {
				printf("%d,", (*tail).data);
				tail = (*tail).previous;
			}
		}
		printf("\n==========\n");

	} else {
		printf("NULL pointer detected.\n");
	}
}

// Test DLL opereations with normal arguments.
void unitTest1() {
	printf("TEST 1\n");
	dll_t *test = create_dll();
	printf("The address of the test dll:%p\n", test);
	printf("Is dll empty:%d\n", dll_empty(test));
	print_dll(test);
	dll_push_front(test, 1);
	dll_push_front(test, 2);
	dll_push_back(test, -1);
	dll_push_back(test, -3);
	print_dll(test);
	dll_insert(test, 0, 3);
	dll_insert(test, 3, 0);
	dll_insert(test, dll_size(test) - 1, -2);
	dll_insert(test, dll_size(test), 100);
	print_dll(test);
	int remove_1 = dll_remove(test, 0);
	int remove_2 = dll_remove(test, (*test).count - 1);
	int remove_3 = dll_remove(test, 2);
	printf("Removed: %d, %d, %d\n", remove_1, remove_2, remove_3);
	print_dll(test);
	printf("dll_pop_back:%d\n", dll_pop_back(test));
	printf("dll_pop_front:%d\n", dll_pop_front(test));
	print_dll(test);

	int i;
	for (i = 0; i < dll_size(test); i++)
		printf("dll_get(test,%d)=%d\n", i, dll_get(test, i));
	dll_pop_back(test);
	dll_pop_front(test);
	print_dll(test);
	dll_remove(test, 0);
	print_dll(test);
	free_dll(test);
}

// Test DLL operations with abnormal arguments
void unitTest2() {
	printf("TEST 2\n");
	dll_t *test = NULL;
	printf("If the pointer pointing to the DLL struct is NULL, then:\n");
	printf("dll_push_front returns:\t%d\n", dll_push_front(test, 2));
	printf("dll_push_back returns:\t%d\n", dll_push_back(test, -2));
	printf("dll_insert returns:\t%d\n", dll_insert(test, 0, 2));
	printf("dll_get returns:\t%d\n", dll_get(test, 0));
	printf("dll_remove returns:\t%d\n", dll_remove(test, 0));

	printf("\nNow create_dll.\n");
	test = create_dll();
	printf("dll_empty(test) returns:\t%d\n", dll_empty(test));
	printf("dll_size(test) returns:\t%d\n", dll_size(test));
	printf("dll_insert(test,0,10) returns:\t%d\n", dll_insert(test, 0, 10));
	printf("dll_get(test,0) returns:\t%d\n", dll_get(test, 0));
	printf("dll_remove(test,0) returns\t%d\n:", dll_remove(test, 0));

	free_dll(test);
}
// Test on operation combinations.
void unitTest3() {
	printf("TEST 3\n");
	dll_t *test = create_dll();
	printf("dll_push_back(test,10) returns:\t%d\n", dll_push_back(test, 10));
	print_dll(test);
	printf("dll_pop_front(test) returns:\t%d\n", dll_pop_front(test));
	print_dll(test);

	printf("dll_push_front(test,10) returns:\t%d\n", dll_push_front(test, 10));
	print_dll(test);
	printf("dll_pop_back(test,10) returns:\t%d\n", dll_pop_back(test));
	print_dll(test);

	printf("dll_push_back(test,10) returns:\t%d\n", dll_push_back(test, 10));
	print_dll(test);
	printf("dll_push_front(test,20) returns:\t%d\n", dll_push_front(test, 20));
	print_dll(test);
	printf("dll_get(test,1) returns:\t%d\n", dll_get(test, 1));
	printf("dll_remove(test,1) returns:\t%d\n", dll_remove(test, 1));
	print_dll(test);
	free_dll(test);
}
int main() {
	printf("sizeof(dll_t):%lu\n", sizeof(dll_t));
	printf("sizeof(node_t):%lu\n", sizeof(node_t));
	printf("\n\nBegin of Test.\n");
	unitTest1();
	unitTest2();
	unitTest3();
	printf("End of Test.\n\n");
	return 0;
}
