
# Merge sort 

For this assignment, you are going to implement in 'C' merge sort. A skeleton file has been provided called `sort.c`. You will know your result is correct, if the data you have sorted is done so in ascending order.

## Mergesort at a high level

<img align="right" src="https://upload.wikimedia.org/wikipedia/commons/c/cc/Merge-sort-example-300px.gif" alt="Merge sort picture">

Merge sort is a [divide and conquer algorithm](https://en.wikipedia.org/wiki/Divide-and-conquer_algorithm) that was invented by [John von Neumann](https://en.wikipedia.org/wiki/John_von_Neumann) in 1945. Merge sort has a worst-case time complexity being Ο(n log n), which is the best we have seen so far. 

Merge sort works as follows:

1. Divide the unsorted array into n subarrays, each containing one element (an array of one element is considered sorted).
2. Repeatedly merge subarrays to produce new sorted subarrays until there is only one subarray remaining. This will be the sorted array.

As they say a pictuer is worth a thousand words:

<img align="center" width="400px" src="https://upload.wikimedia.org/wikipedia/commons/e/e6/Merge_sort_algorithm_diagram.svg" alt="Merge sort picture">

A more detailed pseudo-code would look like this:

```cpp
MergeSort(arr[], l,  r)
If r > l
     1. Find the middle point to divide the array into two halves:  
             middle m = (l+r)/2
     2. Call mergeSort for first half:   
             Call mergeSort(arr, l, m)
     3. Call mergeSort for second half:
             Call mergeSort(arr, m+1, r)
     4. Merge the two halves sorted in step 2 and 3:
             Call merge(arr, l, m, r)
 ```  
           

Note that merge sort is not an [in-place algorithm](https://en.wikipedia.org/wiki/In-place_algorithm) as it needs to crete new arrays everytime it merges. However, it is more efficient than Selection, Insertion, or Bubble sort. 

You can watch [this](https://www.youtube.com/watch?time_continue=1&v=JSceec-wEyw) to visually see how merge sort works.

## Designing the algorithm

An algorithm itself does not have to be one single function. Sometimes it is helpful to have some 'helper functions' to make the code easier to understand. For merge sort, you would need at least two functions: 

1. mergeSort -- the main sort function
2. merge -- the main chunk of the algorithm. 

## Compiling and running the program.

When you have made an attempt at the sorting algorithm, go ahead and try to run it. Remember to save, compile, and test early and often!

* Compile the source code with: `clang sort.c -o sort`
* Run the source code with: `./sort`

# Part 2 - Merge Sort Complexity Q & A.

Discuss and answer the following questions (Make sure to elaborate and justify your responses):

1. Explain, what do you think the Big-Oh (worst-case) complexity of this algorithm is? 
2. Explain what do you think the best-case complexity of this algorithm is?
3. Does merge sort require any additional storage beyond the original array? If so how much and why?
4. How much time in Big-O does it take to merge all of the sublists together? Why?

## Answers

1. *This merge sort algorithm uses the divide and conquer paradigm to sort the integers. The size of the sub problem will be halved in each recursion. Meanwhile, the number of sub problems will be doubled. This recursive process will continue untill the sub problem could be solved in constant time complexity O(1). In this case, when the size of the array becomes 1, the sort problem can be solved in constant time. The merge sort includes several operations, including dividing, comparing, copying. In these operations, only the number of comparing varies in each merging process. In fact, if a n-element array is divided in half, then the number of comparisons is in the range of [ &lfloor;n/2&rfloor;, n-1]. But this won't affect the growth rate because only the highest order matters.*

    - *In order to be more thorough, we could assume the worst case need n-1 comparisons.*


    <img width=600px src="../images/MergeWorstCase.png">

2. *The best case is that the array is already sorted. In this case, if a n-elements array is divided in half, then the number of comparisons is  &lfloor;n/2&rfloor;. For simplicity, we can assume the array size is a power of 2 and the number of comparison is n/2.*

    <img width=600px src="../images/MergeBestCase.png">

3. *For array, we need to create a temporary array for the elements. This is because the normal merge sort doesn't swap items in the same array like insertion sort or selection sort. It needs an temporary array when it merges two sub arrays. Altough it is possible to design an in-place merge sort by using the 'rest' area in the array, it's quite difficult to design such an algorithm.*
4. *For each "level" of the merge sort, suppose a n-element array has be divided in to several sublists. Each sublist is already sorted. In order to merge them, every item will be copied from the temporary lists to the result list. Meanwhile, the number of comparisons during the merging is within [ &lfloor;n/2&rfloor;, n-1]. So the time complexity of merging the sublists of each "level" is O(n). If we are considering the overall time complexity of merging all log<sub>2</sub> n levels, then it is O(n log<sub>2</sub>n)*

# Deliverable

- Modify the file called **sort.c** and implement a version of merge sort that sorts numbers in ascending order.
- Answer the questions in Part 2
  
# Rubric

- 40% Correct implementation of merge sort (and not some other sort)
  - There should be no memory leaks
  - There should be no bugs in your functions 
  - Your implementation will be graded by our set of unit tests, and we will check your code 'style' as well.  
- 10% Correct answers to part 2
   - Make sure to edit your readme.

# More resources to help

- [Merge sort video](https://www.youtube.com/watch?time_continue=1&v=JSceec-wEyw)
- [Khan Academy Sorting, pseudocode, analysis, and exercise](https://www.khanacademy.org/computing/computer-science/algorithms/merge-sort/a/divide-and-conquer-algorithms)

# (Optional) Going Further Task:

(This is an ungraded task--only work on this if you finish the deliverable). You will have to do a little bit of work to figure out how to open and read from files for this task.

- Implement insertion sort, but this time, use a linked list as the storage data structure, instead of an array.


