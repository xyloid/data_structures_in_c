// =================== Support Code =================
// Binary Search Tree ( BST ).
//
//
//
// - Implement each of the functions to create a working BST.
// - Do not change any of the function declarations
//   - (i.e. bst_t* create_bst() should not have additional arguments)
// - You should not have any 'printf' statements in your BST functions.
//   - (You may consider using these printf statements to debug, but they should
//   be removed from your final version)
// ==================================================
#ifndef MYBST_H
#define MYBST_H

// NOTE: smaller value goes to the left.

// Create a node data structure to store data within
// our BST. In our case, we will stores 'integers'
typedef struct node {
	int data;
	struct node *rightChild;
	struct node *leftChild;
} node_t;

// Create a BST data structure
// Our BST holds a pointer to the root node in our BST called root.
typedef struct BST {
	int count;    // count keeps track of how many items are in the BST.
	node_t *root; // root points to the root node in our BST.
} bst_t;

// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values.
bst_t *create_bst() {
	// Modify the body of this function as needed.
	bst_t *myBST = NULL;
	myBST = (bst_t *)malloc(sizeof(bst_t));
	// Check if malloc succeeded.
	if (myBST == NULL) {
		exit(1);
	}
	(*myBST).root = NULL;
	(*myBST).count = 0;
	return myBST;
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element enqueued)
int bst_empty(bst_t *t) {
	if (t == NULL) {
		exit(1);
	} else {
		return (*t).count == 0 ? 1 : 0;
	}
}

// Adds a new node containng item in the correct place of the BST.
// If the data is less then the current node we go right, otherwise we go left.
// Same as described in the README.md file.
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. the memory allocation for a new node failed).
// It should run in O(log(n)) time.
int bst_add(bst_t *t, int item) {
	if (t == NULL) {
		exit(1);
	}
	// Create a new node.
	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	// Check if malloc succeeded.
	if (new_node == NULL) {
		return -1;
	}
	(*new_node).data = item;
	(*new_node).rightChild = NULL;
	(*new_node).leftChild = NULL;
	// Find position to add.
	if ((*t).root == NULL) {
		(*t).root = new_node;
	} else {
		node_t **pick = &(*t).root;
		// Do the comparison until the address of the pointer holds NULL.
		// That is, the pointer = null.
		while (*pick) {
			// Update address until reaching a NULL pointer.
			// Put smaller one on the left.
			pick = item < (**pick).data ? &(**pick).leftChild
			                            : &(**pick).rightChild;
		}
		// Overwrite the NULL pointer.
		*pick = new_node;
	}
	(*t).count++;
	return 0;
}

// Print the node and it's sub-node.
// order != 0: ascending order.
// order == 0: descending order.
void node_print(node_t *n, int order) {
	if (n == NULL) {
		return;
	} else {
		if (order) {
			node_print((*n).leftChild, order);
			printf("%d ", (*n).data);
			node_print((*n).rightChild, order);
		} else {
			node_print((*n).rightChild, order);
			printf("%d ", (*n).data);
			node_print((*n).leftChild, order);
		}
	}
}

// Prints the tree in ascending order if order = 0, otherwise prints in
// descending order. For NULL tree it should print nothing. It should run in
// O(n) time.
void bst_print(bst_t *t, int order) {
	if (t == NULL) {
		return;
	} else {
		node_print((*t).root, order);
		printf("\n");
	}
}

// Since function sum(), free() and size() (count could be modified by anyone.)
// need to iterate over the bst and then perform some operations on
// each node. Here, an iterator function is designed to iterate over
// the bst and perform certain operation define in the function pointer
// void (*func)(node_t *, void *) and store the return value in the
// address pointed by void *ret. The iterator will start from the node
// pointed by node_t * n.
void iterator_node(node_t *n, void (*func)(node_t *, void *), void *ret) {
	// Check function pointer.
	if (func == NULL)
		exit(1);
	if (n) {
		// Operation on sub nodes should be perform with priority since
		// the node could be freed.
		iterator_node((*n).leftChild, func, ret);
		iterator_node((*n).rightChild, func, ret);
	}
	func(n, ret);
}

// Used to get the sum of the data. 
// It will be passed as a parameter to iterator_node().
void node_data(node_t *n, void *result) {
	int data = n ? (*n).data : 0;
	*(int *)result += data;
}

// Used to count the number of the node.
// It will be passed as a parameter to iterator_node().
void node_count(node_t *n, void *result) {
	*(unsigned int *)result += n ? 1 : 0;
}

// Used to free the node.
// It will be passed as a parameter to iterator_node().
void node_free(node_t *n, void *result) {
	free(n);
}

// Returns the sum of all the nodes in the tree.
// exits the program for a NULL tree.
// It should run in O(n) time.
int sum(bst_t *t) {
	if (t == NULL) {
		exit(1);
	} else {
		int accumulator = 0;
		// Iterate over the node.
		iterator_node((*t).root, node_data, &accumulator);
		return accumulator;
	}
}

// Returns 1 if value is found in the tree, 0 otherwise.
// For NULL tree it exists the program.
// It should run in O(log(n)) time.
int find(bst_t *t, int value) {
	if (t == NULL) {
		exit(1);
	}
	node_t *pick = (*t).root;
	while (pick) {
		if ((*pick).data == value) {
			// Find the vlaue!
			return 1;
		} else {
			// Enter next level.
			pick =
			    value < (*pick).data ? (*pick).leftChild : (*pick).rightChild;
		}
	}
	// Value not found!
	return 0;
}

// BST Size
// Queries the current size of the BST
// A BST that has not been previously created will crash the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t *t) {
	if (t == NULL) {
		exit(1);
	} else {
		unsigned int accumulator = 0;
		// Iterate over the node.
		iterator_node((*t).root, node_count, &accumulator);
		return accumulator;
	}
}

// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the proram terminates.
void free_bst(bst_t *t) {
	if (t) {
		// Iterate over the node.
		iterator_node((*t).root, node_free, NULL);
		free(t);
	}
}

#endif
