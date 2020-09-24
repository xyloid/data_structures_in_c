// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

// ====================================================
// ================== Program Entry ===================
// ====================================================
void unitTest1() {
	printf("\n\n=====Test 1=====\n");
	graph_t *testGraph = create_graph();
	print_graph_layout(testGraph);
	graph_add_node(testGraph, 101);
	graph_add_node(testGraph, 101);
	graph_add_node(testGraph, 201);
	graph_add_node(testGraph, 501);
	graph_add_edge(testGraph, 201, 101);
	graph_add_edge(testGraph, 201, 501);
	graph_add_edge(testGraph, 101, 501);
	graph_add_edge(testGraph, 501, 101);
	graph_add_edge(testGraph, 101, 101);
	printf("is_reachable 201->201:%d\n", is_reachable(testGraph, 201, 201));
	printf("is_reachable 101->101:%d\n", is_reachable(testGraph, 101, 101));
	printf("is_reachable 101->201:%d\n", is_reachable(testGraph, 101, 201));
	printf("is_reachable 201->101:%d\n", is_reachable(testGraph, 201, 101));
	print_graph_layout(testGraph);
	graph_print(testGraph);
	graph_remove_node(testGraph, 101);
	print_graph_layout(testGraph);
	graph_remove_edge(testGraph, 201, 501);
	print_graph_layout(testGraph);
	free_graph(testGraph);
}

void unitTest2() {
	printf("\n\n=====Test 2=====\n");
	graph_t *test = create_graph();
	graph_add_node(test, 101);
	graph_add_node(test, 102);
	graph_add_node(test, 103);
	graph_add_node(test, 104);
	graph_add_edge(test, 101, 102);
	graph_add_edge(test, 102, 103);
	graph_add_edge(test, 103, 104);
	graph_add_node(test, 201);
	graph_add_node(test, 202);
	graph_add_node(test, 203);
	graph_add_node(test, 204);
	graph_add_edge(test, 201, 202);
	graph_add_edge(test, 202, 203);
	graph_add_edge(test, 202, 204);
	print_graph_layout(test);

	graph_print(test);
	graph_add_edge(test, 201, 103);

	print_graph_layout(test);
	graph_print(test);

	graph_remove_edge(test, 201, 103);
	graph_add_edge(test, 101, 204);

	print_graph_layout(test);
	graph_print(test);

	free_graph(test);
}

void unitTest3() {
	printf("\n\n=====Test 3=====\n");
	graph_t *test = create_graph();
	graph_add_node(test, 101);
	graph_add_node(test, 102);
	graph_add_node(test, 103);
	graph_add_node(test, 104);
	graph_add_edge(test, 101, 102);
	graph_add_edge(test, 102, 103);
	graph_add_edge(test, 103, 104);
	printf("Path:");
	print_path(test, 101, 104);
	graph_add_edge(test, 101, 104);
	printf("Path:");
	print_path(test, 101, 104);
	// graph_remove_edge(test,101,104);

	print_graph_layout(test);
	printf("has cycle:%d\n", has_cycle(test));
	graph_add_edge(test, 104, 101);
	print_graph_layout(test);
	printf("has cycle:%d\n", has_cycle(test));
	free_graph(test);
	printf("\nSingle loop test:\n");
	graph_t *test2 = create_graph();
	graph_add_node(test2, 101);
	print_graph_layout(test2);
	printf("has cycle:%d\n", has_cycle(test2));
	printf("is_reachable:%d\n", is_reachable(test2, 101, 101));
	graph_add_edge(test2, 101, 101);
	print_graph_layout(test2);
	printf("has cycle:%d\n", has_cycle(test2));
	printf("is_reachable:%d\n", is_reachable(test2, 101, 101));
	free_graph(test2);
}

void unitTest4() {
	printf("\n\n=====Test 4=====\n");
	graph_t *test = create_graph();
	// graph_add_node(test, 101);
	graph_add_node(test, 102);
	graph_add_node(test, 103);
	graph_add_node(test, 104);
	graph_add_node(test, 101);
	graph_add_edge(test, 101, 102);
	graph_add_edge(test, 101, 103);
	graph_add_edge(test, 101, 104);

	node_t *root = find_root(test);
	int root_id = root == NULL ? 0 : root->data;
	printf("root node : %p %d\n", root, root_id);
	graph_print(test);

	print_graph_layout(test);
	int num = numNeighbors(test, 101);
	int *arr;
	arr = getNeighbors(test, 101);
	int i = 0;
	for (i = 0; i < num; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
	free(arr);
	free_graph(test);
}

void unitTest5() {
	printf("\n\n=====Test 5=====\n");
	graph_t *test = create_graph();
	// graph_add_node(test, 101);
	graph_add_node(test, 3);
	graph_add_node(test, 8);
	graph_add_node(test, 10);
	graph_add_node(test, 5);
	graph_add_node(test, 11);
	graph_add_node(test, 7);
	graph_add_node(test, 9);
	graph_add_node(test, 2);

	graph_add_edge(test, 3, 8);
	graph_add_edge(test, 3, 10);
	graph_add_edge(test, 5, 11);
	graph_add_edge(test, 11, 2);
	graph_add_edge(test, 7, 8);
	graph_add_edge(test, 8, 9);
	graph_add_edge(test, 7, 11);
	graph_add_edge(test, 11, 9);
	graph_add_edge(test, 11, 10);

	node_t *root = find_root(test);
	int root_id = root == NULL ? 0 : root->data;
	printf("root node : %p %d\n", root, root_id);

	print_graph_layout(test);
	free_graph(test);
}

void unitTest6() {
	printf("\n\n=====Test 6=====\n");
	graph_t *test = create_graph();
	graph_add_node(test, 101);
	graph_add_node(test, 102);
	graph_add_node(test, 103);
	print_graph_layout(test);

	graph_add_edge(test, 101, 102);
	graph_add_edge(test, 101, 102);
	graph_add_edge(test, 101, 102);
	print_graph_layout(test);
	graph_add_edge(test, 102, 103);
	graph_add_edge(test, 102, 103);
	print_graph_layout(test);
	graph_remove_edge(test, 101, 102);
	print_graph_layout(test);
	graph_remove_node(test, 102);
	print_graph_layout(test);
	free_graph(test);
}
int main() {
	unitTest1();
	unitTest2();
	unitTest3();
	unitTest4();
	unitTest5();
	unitTest6();
	return 0;
}
