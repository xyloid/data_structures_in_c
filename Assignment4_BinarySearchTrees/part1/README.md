
# Binary Search Tree *(BST)*

In Assignment 3 you implemented what is callled a [doubly linked list or a DLL](https://en.wikipedia.org/wiki/Doubly_linked_list/).
The code for our node struct looked like this:

```cpp
typedef struct node{
	int myData;
	struct node* head;
        struct node* tail;
}node_t;
```

Similarly our *DLL* (Assignment 3, Part 1) looked like this:

```cpp
typedef struct DLL{
	int count;		// count keeps track of how many items are in the DLL.
	node_t* head;		// head points to the first node in our DLL.
        node_t * tail;          //tail points to the last node in our DLL.
}dll_t;
```

In this assignment we are going to build on these ideas to create what is called a [binary search tree](https://en.wikipedia.org/wiki/Binary_search_tree) or a *BST*.

# What is a *Binary Search Tree*

<img align="right" src="https://upload.wikimedia.org/wikipedia/commons/f/f7/Binary_tree.svg" alt="Binary Tree Picture"> 

A BST is a [binary tree](https://en.wikipedia.org/wiki/Binary_tree). A Binary tree as shown in the picture on the right is better suited for showing hierarchical relationships between data (i.e. parent-child relationship), when compared to a list, stack or a DLL. 

A binary tree is like a DLL in that it is composed of nodes.  A binary tree node is like a DLL node, but rather having a *previous* and a *next* pointer, it has a *rightChild* and a *leftChild* pointer. 

```cpp
typedef struct node{
	int myData;
	struct node* rightChild;
        struct node* leftChild;
}node_t;
```

Like a DLL, a binary tree has only one pointer called *root* that points to the beginning of the tree. 

```cpp
typedef struct binary_tree{
	int count;		// count keeps track of how many items are in the DLL.
	node_t* root;		// head points to the first node in our DLL.
}binary_tree;
```

# Adding elements to a binary tree, the pictures behind the code. 

The first element we add to an empty tree will become the *root* node. Upon adding another element we have to decide where we will put the new element, to the right or to the left of our root node. 

<img width="300px" src="./../images/to_the_right.png"><img width="100px" src="./../images/space.png"> <img width="290px" src="./../images/to_the_left.png">

For example:

```cpp
...
root->left = new_node;
//or
root->right = new_node;
```
In a binary search tree, if the new node is smaller than the root we add it to the right, otherwise to the left.

```cpp
...
if ( new_node->data < root->data)
    root->right = new_node;
else
    root->left = new_node;
```

## Constructing a tree, step-by-step

Lets construct an empty new tree and add *20* to it.

```cpp
binary_tree t = create_tree();
add(t, 20)
```
<img width="80" src="./../images/20.png">

The tree is initally empty so *20* becomes our *root* node.

Now we add *10*. We look at *root* and we know that we need to go right, since *10* is less than *20*. There is no node to the right of *20*, thus we create new node to the right of the *root* and store *10* in it. We make this new node be the *rightChild* of the root.

```cpp
add(t, 10)
```
<img width="150" src="./../images/20-10.png">

Now we add *15*. *15* is less than the root, so we need to go right. However, there is another node there namely the node storing *10*. So we repeat the same process. *15* is larger than *10* so we know that we need to to the left of *10*. There is no node to the left of *10* so we create a new node that, store *15* in the node, and make our new node be the left child of the node storing *10*. 

```cpp
add(t, 15)
```

<img width="200" src="./../images/20-10-15.png">


We then add *30* which is larger than *root* so we add it to the left. 

```cpp
add(t, 30)
```
<img width="250" src="./../images/20-10-15-30.png">

We then add *25*. *25* is larger than the *root*, we go left. *25* is less than *30* so we go to the right of *30*, no node there so we add *25* to the left of 30.

```cpp
add(t, 25)
```
<img width="350" src="./../images/20-10-15-30-25.png">

We then add *5*. *5* is less than the *root*, go right, *5* is less than *10* go right, no node there, add *5* to the right of *10*.

```cpp
add(t, 5)
```
<img width="350" src="./../images/20-10-15-30-25-5.png">

We then add *35*, *35* is larger than *root* so we go left, still larger than *30* so we go left, no node there, so we add *35* to the left of *30*.


```cpp
add(t, 35)
```
<img width="350" src="./../images/20-10-15-30-25-5-35.png">

# TO DO:

* Implement *add*, that uses the example above ( needs to be recursive ).
* Implement *find* that returns 1 if the data exists in the tree otherwise false. 
* Implement *print_tree* that prints the tree in ascending order or descending order depending on the argument passed.
* Implement *sum* that returns the sum of all the nodes. 

### Unit Tests

A unit test is a standalone test that checks for the correctness of a specific use case in your code. In our case, we are testing if we have a working *binary search tree* implementation. 

You *may* also consider writing some unit tests to test your implementation (In fact, we would strongly encourage you to do so). Note that you can include your unit tests in your submission, and we will have our own test suite. 


# Rubric

- Part 1
- 50% Correct Binary-Search-Tree implementation
  - All functions should be implemented. Do not rename the functions, but you may add any 'helper' functions if you deem necessary.
    - (e.g. You might have a 'binary_search_tree_print' to help you debug)
  - There should be no memory leaks
  - There should be no bugs in your functions 
  - Your implementation will be graded by our set of unit tests, and we will check your code 'style' as well.

# Resources to help

- This is a nice interactive tutorial for learning C
  - http://www.learn-c.org/
- Doubly Linked List Data Type High level description
  - https://en.wikipedia.org/wiki/Binary_search_tree (abstract_data_type)
  
# Feedback Loop

(An optional task that will reinforce your learning throughout the semester)

- Investigate/Review more data strutures on this webpage: https://visualgo.net/en/bst?slide=1
  - There are visuals for the binary search tree here!
  - Use them as a *rough* outline for the general concept. Do make sure to follow the specifications above.
