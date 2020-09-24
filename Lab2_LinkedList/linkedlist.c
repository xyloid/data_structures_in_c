// Modify this file
// compile with: gcc linkedlist.c -o linkedlist

#include <stdio.h>
#include <stdlib.h> // contains the functions free/malloc

// Create your node_t type here
typedef struct node {
	int year;
	int wins;
	struct node *next;
} node_t;

// Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list
// You may create as many helper functions as you like.

/* A helper function that create one node at a time. */
node_t *create_node(int year, int wins, node_t *next) {
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	(*new_node).year = year;
	(*new_node).wins = wins;
	(*new_node).next = next;
	return new_node;
}

node_t *create_list(int data[][2], int length) {
	node_t *first_node;
	node_t *next_node = NULL;
	// Create the list, from the node element to the first node.
	while (length-- > 0) {
		first_node = create_node(data[length][0], data[length][1], next_node);
		next_node = first_node;
	}
	return first_node;
}

void print_list(node_t *start_node) {
	while (start_node != NULL) {
		printf("%d, %d wins\n", (*start_node).year, (*start_node).wins);
		start_node = (*start_node).next;
	}
}

void free_list(node_t *start_node) {
	node_t *temp;
	while (start_node != NULL) {
		temp = (*start_node).next;
		free(start_node);
		start_node = temp;
	}
}

int main() {
	int data[5][2] = {
	    {2018, 108}, {2017, 93}, {2016, 93}, {2015, 78}, {2014, 71}};

	node_t *first_node = create_list(data, 5);
	print_list(first_node);
	free_list(first_node);
	return 0;
}
