# Sorting

- motivation : why we interested in sorting ?

  - obvious : phone book

  - problems that become easy once item are sorted

    ex. find a median

    - if we have a sorted list A[0:n] and we want to find the median, then we just need constant time

      -> median = A[n/2]

      (although there is some more efficient ways to find a median)

  - not so obvious apps

    - data compression : sorting finds duplicates
    
    - computer graphics : rendering scenes front to back



## Insertion sort

- idea

  - 其實想法跟 playing card 很像 , 我們把 unsorted array 藉由 swap 擺到正確的位置

    ![](https://www.cmprogrammers.com/images/in-articles/insertionsort-01.gif)

- pseudo code

  ```
  for i = 1, 2, ..., n	# input
  	insert A[i] into sorted array A[0:n-1] by pairwise swaps down to the correct position
  ```

- example

  ![](https://i.stack.imgur.com/CK6vC.jpg)

- analysis

  - how many steps do I have ?
  
    - Θ(n) steps 
    
    - and at any given step, it's quite possible that I have to do Θ(n) to work
    
    - so each step is Θ(n) swaps (compare & swap)
    
  - compare & swap
  
    - swapping pointers or references to do the swap
    
    - but comparision could be substantially more expensive



## Selection sort

- idea

  - 反覆從 unsorted list 取出最小的 element , 加入新的 list

  - 感受一下

    ![](https://upload.wikimedia.org/wikipedia/commons/thumb/b/b0/Selection_sort_animation.gif/250px-Selection_sort_animation.gif)

- pseudo code

  ```
  for i ← 1 to n-1
  	min ← i
  	for j ← i+1 to n
  		if arr[j] < arr[min]
  			min ← j
  	if min != i
  		swap(arr[i], arr[min])
  ```

- example

  ![](https://freefeast.info/wp-content/uploads//2013/02/Insertion-Sort.jpg)



## Bubble sort

- idea

  - 每一輪比較兩兩相鄰的 element , 小的浮出 , 大的往下沉 , 一輪結束後確定最大值的位置 (沉到最底)

  - 感受一下

    ![](https://upload.wikimedia.org/wikipedia/commons/5/54/Sorting_bubblesort_anim.gif)

- pseudo code

  ```
  for i ← 0 to n-1
  	for j ← 0 to n-i-1
  		if arr[j] > arr[j+1]
  			swap(arr[j], arr[j+1])
  ```

- example

  ![](https://developersadda.files.wordpress.com/2016/08/c34ba-java2bbubble2bsort2bexample.png?w=640&h=316)

