### Lab partner: C. Vinay Reddy
# Lab 3 - Sorting Algorithms
> "Computers are really just fancy machines for storing and finding information" - Your instructor

<img src="./media/sort.JPG" style="float:right;" alt="Sorting">
It is amazing how fast computers can search and find information. Think about how long it would take you to look through more than 500,000 books in a library? So what is the big trick computers use for finding the right information so quickly? Simple--we sort all of the data prior to searching.

## What did we previously learn about searching? Complexity Matters.

Previously we learned that a binary search is faster than a linear search (it helps us make better guesses when searching for information). A linear search means looking through each piece of information one at a time, while a binary search can eliminate half of the possibilities each time. We often compare algorithms based on their *complexity class* to figure out their efficiency.

<table>
  <tbody>
    <tr>
      <th>Algorithm</th>
      <th align="center">Complexity</th>
      <th>n = 100</th>
      <th>n = 100,000</th>
    </tr>
    <tr>
      <td>Linear Search</td>
      <td align="left">O(n)</td>
      <td>100</td>
      <td>100,000</td>
    </tr>
    <tr>
      <td>Binary Search</td>
      <td align="left">Log(n)</td>
      <td>6.64</td>
      <td>16.60</td>
    </tr>
  </tbody>
</table>

From the table, if we are given 'n' number of items to search, then log(n) will be smaller than O(n). The classic way to view this is visually. In the chart below, as our input grows(along the x-axis), the lower the height(on the y-axis, typically representing time) we like to have for our algorithms. Log(n) is clearly lower (thus better) than O(n).

<img src="./media/growth.png" width="300px" style="float:right;" alt="Sorting">

Now, just like there are several algorithms for searching for data, there are a range of slow to fast algorithms for sorting data. We will start with an algorithm that does an *okay* job at sorting, and then figure out how to make it more efficient in future labs!

# Part 0 - SSH and git pull

1. First open a terminal and ssh into the Khoury servers ``` ssh khoury_user_name_here@login.khoury.neu.edu ```
2. Navigate to your Monorepo directory(Use the `cd` command to change directory, `ls` to see files, and `pwd` to see your path)
3. When you are within your Monorepo, do a ```git pull```. This will add all of the files I have previously pushed into your repositories.

If for some reason you are having troubles, you can always create a new copy of your monorepo by running `git clone https://github.com/COURSENAME/monorepo-yourUserNameHere` in a separate directory.

# Part 1 - Selection Sort 

For this assignment, you are going to implement in 'C' selection sort. A skeleton file has been provided called `sort.c`. You will know your result is correct, if the data you have sorted is done so in ascending order.

## Selection sort at a high level

The selection sort algorithm at a high level, works by repeatedly finding the minimum value in an array and placing it in the correct position. You can imagine yourself going through your wallet and swapping the smaller bills with the bigger bills to be put in front, and continuously thumbing through your wallet to make sure it is in order. Another analogy would be if you are shuffling cards, and swapping the positions of each card in your hand to get an ascending order.

The expected output of sorting an array in ascending order is the following: an array with the values `[50,5,20,10,1]` would be sorted in ascending order to be `[1,5,10,20,50]`. 

## Pseudo-code

The pseudo-code for selection sort goes as follows
```c
1. Iterate through your array and find the smallest element in an array
2. Swap the smallest element with the first element of the array
3. Iterate again through your array, but this time, find the second smallest element and place it in the second position.
   - You know the smallest element is in the first position already, so you are swapping in the second position 
   - As you follow this pattern, you build a 'partially sorted' array, until you reach the end of your array..
```

<img src="./media/selection.png" width="300px" alt="Selection Sort">

Take a moment to think about how we would sort in descending order. What would we be searching for in the array? If you said the maximum value, you are correct! Thus, if we want to sort in descending order, then we would select the maximum value through each iteration..

Note: Regardles if we are using an array or a linked list, the algorithm looks the same. However, for this lab, an array is slightly easier to work with.

## Designing the algorithm

An algorithm itself does not have to be one single function. Sometimes it is helpful to have some 'helper functions' to make the code easier to understand. For selection sort, I recommend three different functions, and the function stubs have been provided.

1. swap -- Swaps two integers in an array
2. findMinimum -- Finds at which index in an array the minimum value is found (Note: this is the index, not the actual value).
3. sortIntegers -- This is where you will perform the actual selection sort.

## Compiling and running the program.

When you have made an attempt at the sorting algorithm, go ahead and try to run it. Remember to save, compile, and test early and often!

* Compile the source code with: `clang sort.c -o sort`
* Run the source code with: `./sort`

# Part 2 - Selection Sort Complexity Q & A.

With your partner, discuss and answer the following questions:

1. What do you think the Big-Oh (worst-case) complexity of this algorithm is? 
2. What do you think the best-case complexity of this algorithm is? Note-- you do not have any information about if the array is already sorted or not.
3. Does selection sort require any additional storage beyond the original array? 

## Answers:

1. *It's O(n^2). Beacuse this algorithm always iterates over every element in the unsorted part of the array.*
2. *It's O(n^2). The current state of the array won't affect the number of comparisons or swaps that the algorithm will perform.*
3. *The selection sort is a kind of in place sort, so it does not require additional storage for the array elements. However, it does need fixed number of additional memory to store the indices, for this auxiliary additional memory, it is O(1) space complexity.*

# Deliverable

- Modify the file called **sort.c** and implement a version of selection sort that sorts numbers in ascending order.
- Answer the questions in Part 2
  

# More resources to help

- [Selection sort video](https://www.youtube.com/watch?v=xWBP4lzkoyM)
- [Khan Academy Sorting, pseudocode, analysis, and exercise](https://www.khanacademy.org/computing/computer-science/algorithms/sorting-algorithms/a/sorting)

# (Optional) Going Further Task:

(This is an ungraded task--only work on this if you finish the deliverable). You will have to do a little bit of work to figure out how to open and read from files for this task.

- Implement bubble sort
- Implement selection sort, but this time, use a linked list as the storage data structure, instead of an array.
