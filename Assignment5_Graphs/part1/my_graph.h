// =================== Support Code =================
// Graph.
//
//
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they should
//   be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
// Create a neighbor data structure to server as the neighbor's list.
// In our case, we will stores 'integers' as our neighbors that
// corresponding to the data that the actual nodes store.
typedef struct neighbor {
	int data;
	struct neighbor *next;
} neighbor_t;

// Create a node data structure to store data within
// our graph. In our case, we will stores 'integers'
// as our data in the nodes
typedef struct node {
	int data;
	int visited;         // Mark if the node has been visited.
	int trace;           // Mark if has been traced in has_cycle.
	struct node *parent; // For shortest path.
	struct node *next;
	struct neighbor *neighbor;
} node_t;

// Create a graph data structure
// Our graph keeps track of the number of nodes, the number of edges and an
// array of all the nodes in the graph, and the maximum number of nodes we store
// in our graph.
typedef struct graph {
	int numNodes;
	int numEdges;
	node_t *nodes; // an array of nodes storing all of our nodes.
} graph_t;

// Declaration before use.
int contains_node(graph_t *g, int value);
int numNeighbors(graph_t *g, int value);
void free_graph(graph_t *g);
int has_cycle(graph_t *g);

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
graph_t *create_graph() {
	// Modify the body of this function as needed.
	graph_t *myGraph = NULL;
	myGraph = (graph_t *)malloc(sizeof(graph_t));
	// Check if malloc succeed.
	if (myGraph == NULL) {
		exit(1);
	}
	// Initialize variables.
	myGraph->numEdges = 0;
	myGraph->numNodes = 0;
	myGraph->nodes = NULL;
	return myGraph;
}

// Graph Empty
// Check if the graph is empty
// Returns 0 if true (The graph is completely empty, i.e. numNodes == 0 )
// Returns -1 if false (the graph has at least one node)
int graph_empty(graph_t *g) {
	if (g && g->numNodes >= 0) {
		return g->numNodes == 0 ? 0 : -1;
	} else {
		// Pointer g is NULL or numNodes < 0.
		return -1;
	}
}

// A helper function that prints the graph structure.
void print_graph_layout(graph_t *g) {
	if (g == NULL) {
		printf("Graph pointer is NULL.\n");
	} else {
		printf("@ nodes:%d; edges:%d; pointer:%p\n", g->numNodes, g->numEdges,
		       g->nodes);
		// Start from the first node.
		node_t *node_iter = g->nodes;
		// Loop on nodes.
		while (node_iter) {
			printf("%d(%d): ", node_iter->data, node_iter->visited);
			// Loop on neighbor. Print all neighbors of one node in the same
			// line.
			neighbor_t *neighbor_iter = node_iter->neighbor;
			while (neighbor_iter) {
				printf("%d ", neighbor_iter->data);
				neighbor_iter = neighbor_iter->next;
			}
			printf("\n");
			// Move to next node.
			node_iter = node_iter->next;
		}
	}
}

// Helper function.
// Get the node with item.
// Return a pointer pointing to the node.
// Return NULL if there is no node has the item or g is NULL.
node_t *graph_get_node(graph_t *g, int item) {
	node_t *ret = NULL;
	// Check invalid argument.
	if (g == NULL) {
		return NULL;
	} else {
		ret = g->nodes;
		// Iterate over the nodes.
		while (ret) {
			// Stop loop if the item is found.
			if (ret->data == item) {
				break;
			}
			ret = ret->next;
		}
	}
	return ret;
}

// Reset all the 'visited' in the graph g to 0.
void graph_reset_visited(graph_t *g) {
	if (g) {
		node_t *node_iter = g->nodes;
		while (node_iter) {
			node_iter->visited = 0;
			node_iter = node_iter->next;
		}
	}
}

// Reset all the 'trace' in the graph g to 0.
void graph_reset_trace(graph_t *g) {
	if (g) {
		node_t *node_iter = g->nodes;
		while (node_iter) {
			node_iter->trace = 0;
			node_iter = node_iter->next;
		}
	}
}

// Reset all the 'parent' pointers in the graph g to NULL.
void graph_reset_parent(graph_t *g) {
	if (g) {
		node_t *node_iter = g->nodes;
		while (node_iter) {
			node_iter->parent = NULL;
			node_iter = node_iter->next;
		}
	}
}
// Adds a new node withe the correspoding item in the graph.
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (i.e. the memory allocation for a new node failed).
// Duplicates nodes should not be added. For a duplicate node returns 0.
int graph_add_node(graph_t *g, int item) {
	// Check pointer argument.
	if (g == NULL) {
		return -1;
	}
	// Check for duplicate.
	if (g->numNodes > 0) {
		node_t *pick = g->nodes;
		while (pick) {
			if (pick->data == item) {
				return -1;
			}
			pick = pick->next;
		}
	}
	// Create new node.
	node_t *newNode = (node_t *)malloc(sizeof(node_t));
	// Check if malloc success.
	if (newNode == NULL) {
		return -1;
	}
	// Initialize variables.
	newNode->data = item;
	newNode->visited = 0;
	newNode->trace = 0;
	newNode->parent = NULL;
	newNode->next = NULL;
	newNode->neighbor = NULL;
	// Add new node to the graph g.
	// Append to the end of the linked list.
	node_t **pick = &(g->nodes);
	while ((*pick) != NULL) {
		pick = &((*pick)->next);
	}
	*pick = newNode;
	g->numNodes++;
	return 0;
}

// Removes the node from the graph and the corresponding edges connected
// to the node.
// Returns a -1 if the operation fails (otherwise returns 0 on success).
// (the node to be removed doesn't exist in the graph).
int graph_remove_node(graph_t *g, int item) {
	// Make sure g is not NULL.
	if (g == NULL) {
		return -1;
	}
	// Check if node exists.
	// Case 1: empty list.
	if (g->numNodes < 1) {
		return -1;
	}
	// case 2: non-empty list.
	// try to locate the node.
	node_t **pick = &(g->nodes);
	while ((*pick) != NULL) {
		if ((*pick)->data == item) {
			break;
		}
		pick = &((*pick)->next);
	}
	// If item hasn't been found, return -1;
	if ((*pick) == NULL) {
		return -1;
	} else {
		// Remove item's node in three steps:
		// 1, Remove item's neighbor list.
		// 2, Remove this nodes.
		// 3, Remove other nodes' neighbor list's item.

		// 1, Remove neighbor list of this node.
		// Free all the neighbors' memory.
		neighbor_t *iter = (*pick)->neighbor;
		neighbor_t *temp;
		while (iter) {
			temp = iter->next;
			free(iter);
			iter = temp;
		}
		// 2, Remove this node.
		node_t *delete_node = *pick;
		*pick = (*pick)->next;
		// Free the node's memory.
		free(delete_node);
		g->numNodes--;

		// 3, Remove this node from neighbors of other nodes.
		node_t *node_iter = g->nodes;
		// Iterate over the rest nodes.
		while (node_iter) {

			// Free neighbor refering to the removed node.
			neighbor_t **pIter = &(node_iter->neighbor);
			while ((*pIter)) {
				if ((*pIter)->data == item) {
					neighbor_t *del_neighbor = *pIter;
					// Set the current pointer to point the next neighbor.
					*pIter = (*pIter)->next;
					free(del_neighbor);
					g->numEdges--;
					// Here we do not break the loop in case of duplicate edges.
				} else {
					pIter = &((*pIter)->next);
				}
			}

			node_iter = node_iter->next;
		}
		return 0;
	}
}

// Adds an edge from source to destination.
// If source or desination is not found in the graph returns -1.
// Otherwise it returns 0 ( even for trying to add a duplicate edge )
int graph_add_edge(graph_t *g, int source, int destination) {
	node_t *src = graph_get_node(g, source);
	if (src) {
		// Check if destination exists.
		if (contains_node(g, destination) == 0) {
			// Get neighbor. Loop is allowed.
			neighbor_t **pick = &(src->neighbor);
			// Get the end of the list.
			while ((*pick)) {
				pick = &((*pick)->next);
			}
			// Append neighbor.
			(*pick) = (neighbor_t *)malloc(sizeof(neighbor_t));
			// Check if malloc failed.
			if ((*pick) == NULL) {
				return -1;
			}
			// Initialize variables of the new neighbor.
			(*pick)->data = destination;
			(*pick)->next = NULL;
			g->numEdges++;
			return 0;
		} else {
			// Return if destination does not exist.
			return -1;
		}
	} else {
		// Return if source does not exist.
		return -1;
	}
}

// Removes an edge from source to destination.
// If source or desination is not found in the graph returns -1.
// If no such edge exists also returns -1.
// Otherwise it returns 0
int graph_remove_edge(graph_t *g, int source, int destination) {
	node_t *src = graph_get_node(g, source);
	if (src) {
		// Check if destination exists.
		if (contains_node(g, destination) == 0) {
			// Get neighbor. Loop is allowed.
			neighbor_t **pick = &(src->neighbor);
			while ((*pick)) {
				if ((*pick)->data == destination) {
					// Remove the neighbor.
					neighbor_t *del_neighbor = *pick;
					*pick = (*pick)->next;
					free(del_neighbor);
					g->numEdges--;
					break;
					// Break because the description of the function specify
					// "removes an edge".
				} else {
					pick = &((*pick)->next);
				}
			}
			return 0;
		} else {
			// Return if no destination.
			return -1;
		}
	} else {
		// Return if no source.
		return -1;
	}
}
// Returns 0 if the node with value is in the graph, otherwise returns -1;
int contains_node(graph_t *g, int value) {
	// Check pointer argument.
	if (g == NULL) {
		return -1;
	}
	// Check for value.
	if (g->numNodes > 0) {
		node_t *pick = g->nodes;
		while (pick) {
			if (pick->data == value) {
				return 0;
			}
			pick = pick->next;
		}
	}
	return -1;
}

// Returns 0 if an edge from source to destination exists, -1 otherwise.
int contains_edge(graph_t *g, int source, int destination) {
	node_t *node = graph_get_node(g, source);
	if (node) {
		neighbor_t *iter = node->neighbor;
		// Iterate over neighbors to find the edge.
		while (iter) {
			if (iter->data == destination) {
				return 0;
			}
		}
	}
	// Return -1 if the source node or the egde does not exist.
	return -1;
}
// Returns an int array of all the neighbors of the node with data=value.
// If the node has no neighbor, return NULL.
int *getNeighbors(graph_t *g, int value) {
	node_t *node = graph_get_node(g, value);
	if (node) {
		int num = numNeighbors(g, value);
		int *ret = NULL;
		if (num > 0) {
			ret = (int *)malloc(sizeof(int) * num);
			if (ret == NULL) {
				return NULL;
			}
			// Copy data to the array.
			neighbor_t *iter = node->neighbor;
			int i = 0;
			while (iter) {
				ret[i++] = iter->data;
				iter = iter->next;
			}
		}
		return ret;
	}
	// Return if graph_get_node returns NULL.
	// It will return NULL if g is NULL.
	return NULL;
}

// Returns the number of neighbors for value.
int numNeighbors(graph_t *g, int value) {
	if (g) {
		int ret = 0;
		node_t *node = graph_get_node(g, value);
		if (node) {
			// Count number of neighbors.
			neighbor_t *iter = node->neighbor;
			while (iter) {
				ret++;
				iter = iter->next;
			}
			return ret;
		} else {
			// Node does not exist.
			return -1;
		}
	} else {
		// Graph is NULL.
		return -1;
	}
}

// Implement topological sort in order to find an appropriate root node
// in a connected directed acyclic graph.
// This function is used in find_root function to find an appropriate
// root of a DAG by topological sort.
// Arguments:
// 			     g : the graph
// 			  node : the node being visited.
// 			result : the stack store the sort result.
void topological_sort(graph_t *g, node_t *node, dll_t *result) {
	// Check invalid arguments. No pointer can be NULL.
	if (g && node && result) {

		neighbor_t *iter = node->neighbor;
		// DFS paradigm is used.
		while (iter) {
			node_t *neighbor = graph_get_node(g, iter->data);
			if (neighbor->visited == 0) {
				// Visit neighbors. Recursive DFS.
				topological_sort(g, neighbor, result);
			}
			iter = iter->next;
		}
		node->visited = 1;
		// Push after child nodes have been visited and pushed into the stack.
		// Thus the last item pushed to the stack should be a root.
		// There could be multiple roots. This algorithm doesn't choose between
		// roots.
		dll_push_front(result, node->data);
	}
}

// Find the root node of a graph g.
// If there is no root, then return NULL.
// If there are several possible root nodes. Then the node to be
// returned depends on the order of linked list of the nodes.
node_t *find_root(graph_t *g) {
	node_t *ret = NULL;
	// Proceed if g in not NULL, nor empty, nor cyclic.
	// Topological sort is used here to find a root.
	if (g && g->nodes && (has_cycle(g) != 0)) {
		graph_reset_visited(g);
		// Create a "stack" for topological sort.
		dll_t *stack = create_dll();
		node_t *node = g->nodes;
		// Iterate over all nodes and perform topological sort.
		while (node) {
			if (node->visited == 0) {
				topological_sort(g, node, stack);
			}
			node = node->next;
		}
		// Clean before return.
		int root = dll_pop_front(stack);
		free_dll(stack);
		graph_reset_visited(g);
		ret = graph_get_node(g, root);
	}
	return ret;
}

// Prints the the graph using BFS
// For NULL or empty graph it should print nothing.
// A graph can have several bfs tree.
void graph_print(graph_t *g) {
	if (g && g->numNodes > 0) {
		// Clear temporary data.
		graph_reset_visited(g);
		node_t *current_node = g->nodes;
		// Try to find an appropriate root.
		// If can not find it, then use the first node in the list as the root.
		node_t *root = find_root(g);
		if (root) {
			current_node = root;
		}
		// Queue is needed here to implment BFS.
		// Here DLL data strucuture  from Assigment3 is used.
		dll_t *dll_queue = create_dll();
		// Iterate over all the nodes in the list in case of a disconnected
		// graph.
		while (current_node) {
			if (current_node->visited == 0) {
				dll_push_back(dll_queue, current_node->data);
				while (dll_size(dll_queue) > 0) {
					// Get the first item from the queue.
					int item = dll_pop_front(dll_queue);
					// Get the node of the item.
					node_t *node = graph_get_node(g, item);
					// Node has not been visited.
					if (node && node->visited == 0) {
						node->visited = 1;
						printf("%d ", item);
						// Enqueue neighbors.
						neighbor_t *neighbor_iter = node->neighbor;
						while (neighbor_iter) {
							dll_push_back(dll_queue, neighbor_iter->data);
							neighbor_iter = neighbor_iter->next;
						}
					}
				}
				// End current line when a tree is finished.
				// There might be a new line if there are still some unvisited
				// nodes. Thus, for a disconnected graph, we have multiple
				// lines.
				printf("\n");
			}
			// Move to next node.
			current_node = current_node->next;
		}
		// Clear temporary data.
		graph_reset_visited(g);
		free_dll(dll_queue);
	}
}

// Graph Size
// Returns the number of nodes in the graph
unsigned int graph_num_nodes(graph_t *g) {
	if (g) {
		return g->numNodes;
	} else {
		// Pointer g is NULL.
		return -1;
	}
}

// Graph Size
// Returns the number of edges in the graph
unsigned int graph_num_edges(graph_t *g) {
	if (g) {
		return g->numEdges;
	} else {
		// Pointer g is NULL.
		return -1;
	}
}

// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the proram terminates.
void free_graph(graph_t *g) {
	if (g) {
		// Outside loop: iterate over nodes and free them.
		// Inside loop: iterate over neighbors and free them.
		// Node is freed after its neighbors list has been freed.
		node_t **node_iter = &(g->nodes);
		while (*node_iter) {
			neighbor_t **neighbor_iter = NULL;
			neighbor_iter = &(*node_iter)->neighbor;
			neighbor_t *del_neighbor = NULL;
			// Free neighbors.
			while (*neighbor_iter) {
				del_neighbor = *neighbor_iter;
				*neighbor_iter = (*neighbor_iter)->next;
				free(del_neighbor);
			}
			node_t *del_node = NULL;
			del_node = *node_iter;
			// Update pointer.
			*node_iter = (*node_iter)->next;
			// Free node.
			free(del_node);
		}
		free(g);
	}
}

// Return 0 if the dest is reachable from source. Otherwise, return -1.
int is_reachable(graph_t *g, int source, int dest) {
	if (g && g->numNodes > 0) {
		graph_reset_visited(g);
		// BFS method is used.
		// Here DLL data strucuture  from Assigment3 is being used.
		dll_t *dll_queue = create_dll();
		dll_push_back(dll_queue, source);
		while (dll_size(dll_queue) > 0) {
			// Get the first item from the queue.
			int item = dll_pop_front(dll_queue);
			// Get the node of the item.
			node_t *node = graph_get_node(g, item);
			// If node has not been visited.
			if (node && node->visited == 0) {
				node->visited = 1;
				// Enqueue neighbors.
				neighbor_t *neighbor_iter = node->neighbor;
				while (neighbor_iter) {
					// If dest is reachable, then it must be some nodes'
					// neighbors. So check for dest in neigbors.
					if (neighbor_iter->data == dest) {
						free_dll(dll_queue);
						graph_reset_visited(g);
						return 0;
					}
					// Push neighbor into the queue.
					dll_push_back(dll_queue, neighbor_iter->data);
					neighbor_iter = neighbor_iter->next;
				}
			}
		}
		free_dll(dll_queue);
		graph_reset_visited(g);
		// After iteration over, the dest node is not found.
		return -1;
	} else {
		// Return -1 on invalid graph data.
		return -1;
	}
}

// Helper function for has_cycle.
// Like has_cycle function, return 0 if has cycle, otherwise, return -1.
// Using recursive DFS to search a cycle.
int has_cycle_dfs(graph_t *g, node_t *node) {
	if (node) {
		// If node hasn't been visited.
		if (node->visited == 0) {
			node->visited = 1;
			node->trace = 1;
			// Iterate on neighbors.
			neighbor_t *neighbor = node->neighbor;
			while (neighbor) {
				node_t *pick = graph_get_node(g, neighbor->data);

				// Recursive call.
				if (pick->visited == 0 && has_cycle_dfs(g, pick) == 0) {
					return 0;
				} else if (pick->trace == 1) {
					// Cycle found.
					return 0;
				}
				neighbor = neighbor->next;
			}
		}
		node->trace = 0;
	}
	return -1;
}

// Returns 0 if there is a cycle in the graph, otherwise returns -1.
int has_cycle(graph_t *g) {
	// There could be several trees in a graph.
	if (g && g->numNodes > 0) {
		node_t *current_node = g->nodes;
		// Iterate over linked list of node in case of disconnected graph.
		while (current_node) {
			// Clear temporary data.
			graph_reset_visited(g);
			// Start search from unvisited node.
			if (current_node->visited == 0) {
				int result = has_cycle_dfs(g, current_node);
				if (result == 0) {
					// Clear temporary data.
					graph_reset_visited(g);
					return 0;
				}
			}

			// Move to next node.
			current_node = current_node->next;
		}
		// Clear temporary data.
		graph_reset_visited(g);
	}
	return -1;
}

// Using BFS to assign the parent of each node.
// If the dest's parent node pointer is null, then, it is unreachable.
void print_path(graph_t *g, int source, int dest) {
	if (g && g->numNodes > 0) {
		// Clear flags.
		graph_reset_parent(g);
		// BFS.
		// Here DLL data strucuture  from Assigment3 is being used.
		dll_t *dll_queue = create_dll();
		dll_push_back(dll_queue, source);
		while (dll_size(dll_queue) > 0) {
			// Get the first item from the queue.
			int item = dll_pop_front(dll_queue);
			// Get the node of the item.
			node_t *node = graph_get_node(g, item);
			// If node has not been visited.
			if (node && node->visited == 0) {
				node->visited = 1;
				// Enqueue neighbors.
				neighbor_t *neighbor_iter = node->neighbor;
				while (neighbor_iter) {

					// Setup parent node.
					node_t *child = graph_get_node(g, neighbor_iter->data);
					child->parent = node;

					// If there is a path, then dest must be some nodes'
					// neighbor.
					if (neighbor_iter->data == dest) {
						// Find shortest path.

						// Trace the path by *parent.
						// Push the item of the path into a stack.
						dll_t *path = create_dll();
						node_t *tracer = graph_get_node(g, dest);
						while (tracer) {
							dll_push_front(path, tracer->data);
							tracer = tracer->parent;
						}
						// Print path.
						while (dll_size(path) > 0) {
							printf("%d ", dll_pop_front(path));
						}
						printf("\n");
						// Clean.
						free_dll(path);
						free_dll(dll_queue);
						graph_reset_visited(g);
						graph_reset_parent(g);
						return;
					}
					// If neighbor is not dest, then push it into the queue.
					dll_push_back(dll_queue, neighbor_iter->data);
					neighbor_iter = neighbor_iter->next;
				}
			}
		}
		// No path, print nothing.
		free_dll(dll_queue);
		graph_reset_visited(g);

		// Clear flags.
		graph_reset_parent(g);
	} else {
		// Return if g is NULL or empty.
		return;
	}
}
#endif
