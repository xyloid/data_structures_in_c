### Lab partner: C. Vinay Reddy

# Lab 4 - Recursive Strategies

> "Recursion recursion recursion recursion recursion recur..." - Your instructor

<img width=400px src="./media/cartoon.png">

The cartoon above illustrates an idea of 'recursing' However, we want to be careful not to recurse 'infinitely' (i.e. have an infinite loop in a program that never terminates). For part 1, you will implement a factorial function both iteratively and recursively. Then in part 2, you will implement a Depth-First Tree Traversal recursively.

Remembering the *general* structure of a recursive program can be helpful:

```c
(1) Base case (or some other way to terminate)

(2) Computation

(3) Recursive Call
```

More generally however, remember recursive programs make sure the problem you are trying to solve is always getting smaller (e.g. if you are searching through a 'list' there may not be a general computation, but you should only be searching a smaller subset of the list after each recursive call).

# Part 0 - SSH and git pull

1. First open a terminal and ssh into the Khoury servers ``` ssh khoury_user_name_here@login.khoury.neu.edu ```
2. Navigate to your Monorepo directory(Use the `cd` command to change directory, `ls` to see files, and `pwd` to see your path)
3. When you are within your Monorepo, do a ```git pull```. This will add all of the files I have previously pushed into your repositories.

If for some reason you are having troubles, you can always create a new copy of your monorepo by running `git clone https://github.com/COURSENAME/monorepo-yourUserNameHere` in a separate directory.

# Part 1- Recursion in C

* Implement in the file `factorial.c` both an iterative and recursive solution to computing the factorial of a number.

For solving this problem, I suggest working on just one part at a time, and testing frequently to make sure your code is working.

As a reminder, a factorial is computed as follows:

```
4! = 4*3*2*1
7! = 7*6*5*4*3*2*1
```

Note: how the numbers descend, and how that may be a hint for structuring your recursive case.

## Data sizes and types

Once you have solved the above, answer and modify your programs for the following.

1. What is a bigger [data type](https://www.geeksforgeeks.org/data-types-in-c/) you can use to compute larger factorials? Change the 'return type' and input parameters to the factorial to something other than 'int' (and also change the format specifier in printf to something other than %d for the datatype you choose).
2. Try with your partner computing factorials larger than say 15. At what point does your computer start to 'crash' or really slow down when you try a big enough factorial? Experiment and report your results.

## Answers

- 1. *To compute larger factorials, we can use `unsigned long int` insead of `int` in the program. Because  a facotial can not be negative, so it is safe to use `unsigned long int` to accommodate larger result. According to my test, an 8-byte length `unsigned long int` can store 20! while a 4-byte `int` can only store 12!.*

- 2. *After experiments on both iterative and recursive solutions, both solution showed O(n) time complexity in the test range. The following figure illustrates the experiment result. As the time complexity reveals, it does not show significant sign of suddenly slowing down of the execution. But due to overflow, the maximum value of the factorial is limited. When overflow happens, the answer is incorrect.*

     - *For `signed int`, the maximum value is v<sub>max</sub> = 2<sup>(4&middot;8-1)</sup>-1 = 2147483647. 12! &lt; v<sub>max</sub> &lt; 13!. Thus, we can only compute up to 12! if the data type is `int`.*

     - *For `unsigned long int`, the maximum value is v<sub>max</sub> = 2<sup>(8&middot;8)</sup>-1 = 18446744073709551615. 20! &lt; v<sub>max</sub> &lt; 21!. Thus, we can only compute up to 20! if the data type is `unsigned long int`.*

     <img width=400px src="./media/time_comparison.png">

## Compiling and running the program.

Remember to save, compile, and test early and often!

* Compile the source code with: `clang factorial.c -o factorial`
* Run the source code with: `./factorial`

# Part 2 - Depth-First Tree Traversal

For part 2, you will implement a depth-first traversal (sometimes known as a depth-first search) of a 'tree' data structure, printing out each node that you traverse. This will help get you get started for some of the problems on the homework.

You are given a 'TreeNode_t' data structure that has two pointers that 'chain together' other nodes.

```c
typedef struct TreeNode{
     struct TreeNode* left;
     struct TreeNode* right;
     char data;
}TreeNode_t;
```

By linking these nodes left and right, you can form a 'tree' structure (i.e. you can think of it like a 'family tree'). Your goal will be to print out the nodes that have been generated for you, and implement the function `void dfs(TreeNode_t* start)`.


## Strategy

**With your partner:** First draw the tree that has been hard-coded on a piece of paper or in an online notepad. This will help give you a visualization of the tree so you know what is being printed. Then, discuss a strategy for traversing the tree and printing out each node that is traversed.

The traversal of the tree will follow some pattern like this (notice how the arrows trace around the tree going to the next node):

<img width=300px src="./media/dfs.png">

A successful output of the above tree would be:

```
Cathy
Michael
Charles
Hazel
Melody
Jim
Eleanor
(Program ends here)
```


## Compiling and running the program.

Remember to save, compile, and test early and often!

* Compile the source code with: `clang dfs.c -o dfs`
* Run the source code with: `./dfs`

# Deliverable

- Part 1 - Have a working iterative and recursive solution for computing correct factorials in the `factorial.c`.
  - Answer the questions in the readme regarding factorial.
- Part 2 - Have a working traversal of a depth-first traversal that works recursively in dfs.c. You should print out the nodes in the order you traverse them.

# More resources to help

- [Factorial](https://en.wikipedia.org/wiki/Factorial)
- [data types in C](https://www.geeksforgeeks.org/data-types-in-c/)

# (Optional) Going Further Task:

(This is an ungraded task--only work on this if you finish the deliverable). You will have to do a little bit of work to figure out how to open and read from files for this task.

- Try to implement the DFS with your 'stack' data structure from assignment 2.
