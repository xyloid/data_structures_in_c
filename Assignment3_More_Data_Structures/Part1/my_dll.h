// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
//
//
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
// - You should not have any 'printf' statements in your DLL functions.
//   - (You may consider using these printf statements to debug, but they should
//   be removed from your final version)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H

// Define the limit of the DLL size, as the count is an int.
#define MAX_INT (((1 << (sizeof(int) * 8 - 2)) - 1) * 2 + 1)

// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node {
	int data;
	struct node *next;
	struct node *previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL {
	int count;    // count keeps track of how many items are in the DLL.
	node_t *head; // head points to the first node in our DLL.
	node_t *tail; // tail points to the last node in our DLL.
} dll_t;

// free_dll is used before exit(1) on abnormal cases.
void free_dll(dll_t *t);

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
dll_t *create_dll() {
	// Modify the body of this function as needed.
	dll_t *myDLL = NULL;
	myDLL = (dll_t *)malloc(sizeof(dll_t));
	// If memory allocation failed, exit(1);
	if (myDLL == NULL) {
		exit(1);
	} else {
		// Initialization of the fields.
		(*myDLL).head = NULL;
		(*myDLL).tail = NULL;
		(*myDLL).count = 0;
		return myDLL;
	}
}

// DLL Empty
// Check if the DLL is empty
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t *l) {
	// Check NULL pointer.
	if (l == NULL)
		exit(1);
	// Check abnormal count.
	if ((*l).count < 0) {
		free_dll(l);
		exit(1);
	}
	return (*l).count > 0 ? 0 : 1;
}

// push a new item to the front of the DLL ( before the first node in the list).
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t *l, int item) {
	if (l == NULL)
		return -1;
	// Check abnormal count.
	if ((*l).count < 0)
		return -1;
	if ((*l).count >= MAX_INT)
		return -1;

	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	// If malloc failed, return -1.
	if (new_node == NULL)
		return -1;

	(*new_node).data = item;
	// Previous node of a head is always NULL.
	(*new_node).previous = NULL;
	// Next to the new head is the old head.
	(*new_node).next = (*l).head;

	if ((*l).count == 0) {
		// Empty DLL, we need update head and tail.
		(*l).tail = new_node;
		(*l).head = new_node;
	} else {
		// Non-empty DLL shouldn't have NULL head pointer.
		if ((*l).head == NULL)
			return -1;
		// Non-empty DLL, connect old head and new head.
		(*(*l).head).previous = new_node;
		(*l).head = new_node;
	}
	(*l).count++;
	return 0;
}

// push a new item to the end of the DLL ( after the last node in the list).
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t *l, int item) {
	// Check abnormal cases.
	if (l == NULL)
		return -1;
	if ((*l).count < 0)
		return -1;
	if ((*l).count >= MAX_INT)
		return -1;

	node_t *new_node = (node_t *)malloc(sizeof(node_t));
	// If malloc failed, return -1.
	if (new_node == NULL)
		return -1;

	(*new_node).data = item;
	// Next node of the tail node is always NULL.
	(*new_node).next = NULL;
	// Previous node of the new tail is the old tail.
	(*new_node).previous = (*l).tail;

	if ((*l).count == 0) {
		// Empty DLL, assign the address of the new node to tail and head.
		(*l).head = new_node;
		(*l).tail = new_node;
	} else {
		// Non-empty DLL, connect old tail and new tail.
		(*(*l).tail).next = new_node;
		(*l).tail = new_node;
	}
	(*l).count++;
	return 0;
}

// Returns the first item in the DLL.
// Removes an item from the DLL.
// Removing from an empty DLL should crash the program, call exit(1).
int dll_pop_front(dll_t *t) {
	// Abnormal cases.
	if (t == NULL)
		exit(1);
	if ((*t).count < 1) {
		free_dll(t);
		exit(1);
	}
	if ((*t).head == NULL) {
		free_dll(t);
		exit(1);
	}
	// Store the data.
	int item = (*(*t).head).data;

	node_t *new_head = (*(*t).head).next;
	free((*t).head);
	(*t).head = new_head;
	// Decrement the count.
	if (--(*t).count == 0) {
		// Head is already NULL.
		(*t).tail = NULL;
	} else {
		// Head is not NULL.
		(*(*t).head).previous = NULL;
	}

	return item;
}

// Returns the last item in the DLL.
// Removes the last item from the DLL.
// Removing from an empty DLL should crash the program, call exit(1).
int dll_pop_back(dll_t *t) {
	// Abnormal cases.
	if (t == NULL)
		exit(1);
	if ((*t).count < 1) {
		free_dll(t);
		exit(1);
	}
	if ((*t).tail == NULL) {
		free_dll(t);
		exit(1);
	}

	int item = (*(*t).tail).data;
	// New tail could be NULL.
	node_t *new_tail = (*(*t).tail).previous;
	free((*t).tail);
	(*t).tail = new_tail;

	// Decrement count.
	if (--(*t).count == 0) {
		// Tail is already NULL.
		(*t).head = NULL;
	} else {
		// Tail is not NULL.
		(*(*t).tail).next = NULL;
	}
	return item;
}
// Inserts a new node before the node at the specified position.
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. the memory allocation for a new node failed or trying to insert at a
// negative position or at
//  a position past the size of the DLL ).
int dll_insert(dll_t *l, int pos, int item) {
	// Abnormal cases.
	if (l == NULL)
		return -1;
	// Can not add before NULL, so the DLL must have at least one node.
	if ((*l).count < 1)
		return -1;
	if ((*l).count >= MAX_INT)
		return -1;
	if (pos < 0 || pos > (*l).count)
		return -1;

	// Insert before the first item.
	if (pos == 0)
		return dll_push_front(l, item);
	else if (pos == (*l).count)
		return dll_push_back(l, item);
	else {
		// Insert before a non-first item.
		// Create a new node.
		node_t *new_node = (node_t *)malloc(sizeof(node_t));
		// Check if malloc succeeded.
		if (new_node == NULL)
			return -1;
		(*new_node).data = item;
		// Check the pointer before use.
		if ((*l).head == NULL)
			return -1;
		node_t *pos_node = (*l).head;
		// Goto the position. Locate the node at the position.
		while (pos-- > 0) {
			pos_node = (*pos_node).next;
			// Check the next pointer. Just in case.
			if (pos_node == NULL)
				return -1;
		}
		// Insert before pos_node.
		// Check the pointer before use.
		if ((*pos_node).previous == NULL)
			return -1;
		(*new_node).previous = (*pos_node).previous;
		(*new_node).next = pos_node;
		(*pos_node).previous = new_node;
		if ((*(*new_node).previous).next == NULL)
			return -1;
		(*(*new_node).previous).next = new_node;
		(*l).count++;
		return 0;
	}
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the position is negative or trying to retrive an item at or
// past the size, or the list is empty.
int dll_get(dll_t *l, int pos) {
	if (l == NULL)
		return -1;
	if ((*l).count < 0)
		return -1;
	if (pos < 0 || pos > (*l).count - 1)
		return -1;

	// Check the pointer before use.
	if ((*l).head == NULL)
		return -1;
	node_t *pos_node = (*l).head;
	while (pos-- > 0) {
		pos_node = (*pos_node).next;
		// Check the next pointer. Just in case.
		if (pos_node == NULL)
			return -1;
	}
	return (*pos_node).data;
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the position is negative or trying to remove an item at or past
// the size, or if the list is empty
int dll_remove(dll_t *l, int pos) {
	if (l == NULL)
		return -1;
	// The value of pos should be in [0, size-1];
	if (pos < 0 || pos > (*l).count - 1)
		return -1;
	// At least has one element.
	if ((*l).count < 1)
		return -1;
	// Check if the head pointer is not NULL.
	if ((*l).head == NULL)
		return -1;

	node_t *pos_node = (*l).head;
	int index = pos;
	while (index-- > 0) {
		pos_node = (*pos_node).next;
		if (pos_node == NULL) {
			return -1;
		}
	}
	// Handle the node before pos_node.
	if ((*pos_node).previous != NULL) {
		node_t *node_before = (*pos_node).previous;
		(*node_before).next = (*pos_node).next;
	}
	// Handle the node after pos_node.
	if ((*pos_node).next != NULL) {
		node_t *node_after = (*pos_node).next;
		(*node_after).previous = (*pos_node).previous;
	}
	// Two ends of the range.
	if (pos == 0) {
		(*l).head = (*pos_node).next;
	}
	if (pos == (*l).count - 1) {
		(*l).tail = (*pos_node).previous;
	}
	(*l).count--;
	int item = (*pos_node).data;
	free(pos_node);
	return item;
}

// DLL Size
// Queries the current size of a DLL
// A DLL that has not been previously created will crash the program.
// (i.e. A NULL DLL cannot return the size)
unsigned int dll_size(dll_t *t) {
	if (t == NULL)
		exit(1);
	else if ((*t).count < 0) {
		free_dll(t);
		exit(1);
	} else
		return (unsigned int)(*t).count;
}

// Free DLL
// Removes a DLL and ALL of its elements from memory.
// This should be called before the proram terminates.
void free_dll(dll_t *t) {
	if (t == NULL)
		return;
	node_t *iterator = (*t).head;
	node_t *temp = NULL;
	while (iterator != NULL) {
		temp = (*iterator).next;
		free(iterator);
		iterator = temp;
	}
	free(t);
}

#endif
