// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_bst.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

// ====================================================
// ================== Program Entry ===================
// ====================================================
void unitTest1(){
	bst_t * tree = create_bst();
	bst_add(tree,5);
	printf("count(1):%d\n",bst_size(tree));
	bst_add(tree,3);
	bst_add(tree,7);
	bst_add(tree,1);
	bst_add(tree,15);
	bst_add(tree,123);
	printf("count(6):%d\n",bst_size(tree));
	// Ascending.
	printf("Ascending order:\n");
	bst_print(tree,1);
	// Descending.
	printf("Descending order:\n");
	bst_print(tree,0);
	printf("find 1: %d\n", find(tree,1));
	printf("find 10: %d\n", find(tree,10));
	printf("find 5: %d\n", find(tree,5));
	printf("sum:%d\n",sum(tree));
	free_bst(tree);
	
}
int main(){
	unitTest1();
    return 0;
}
