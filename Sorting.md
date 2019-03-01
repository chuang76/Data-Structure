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

<br>

<br>

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

  - suppose compares >> swaps

    - compare with middle

    - pairwise swaps → binary search

    - do a binary search on A[0:i-1] already sorted

    - example

      ![](https://www.codingeek.com/wp-content/uploads/2016/06/Insertion-Sort-and-its-implementation.png)

<br>

<br>

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

<br>

<br>

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

<br>

<br>

## Merge Sort

- idea

  - divide & conquer

  - 拆成兩個小的 array , 分別 sort 完做 merge

  - 感受一下

    ![](https://upload.wikimedia.org/wikipedia/commons/c/c5/Merge_sort_animation2.gif)

- example

  ![](https://i0.wp.com/kopu.chat/wp-content/uploads/2017/08/merge.gif?fit=476%2C191&ssl=1)

<br>

<br>

## Quick Sort

- idea

  - 隨機找一個數當 pivot , 把小於它的放左邊 , 大於它的放右邊 (partition) , 並利用遞迴將子數列做排序

  - 感受一下

    ![](https://upload.wikimedia.org/wikipedia/commons/f/fe/Quicksort.gif)

- psuedo code

  ```
  QuickSort(A, start, end)   # use index so that we don't need extra memory
  {
      if(start < end)
      	pIndex ← Partition(A, start, end)    # pivot 的 index
      	QuickSort(A, start, pIndex-1)		# 左邊的子數列
      	QuickSort(A, pIndex+1, end)			# 右邊的子數列
  }
      
  Partition(A, start, end)
  {
      pivot ← A[end]			# 假設選最右邊當 pivot
  	pIndex ← start
  	for i ← start to end-1
  		if(A[i] <= pivot)
  			swap(A[i], A[pIndex])    # index 往右移
  			pIndex ← pIndex+1   	 # 值也要跟著變
  	swap(A[pIndex], A[end])			 # 完成了
      return pIndex          	# 回傳 pivot 的 index
  }
  ```

- example

  ![](https://camo.githubusercontent.com/bfb739ea1469b2965f6ea6cad9a2acc9c850d6cb/68747470733a2f2f69322e77702e636f6d2f7777772e74656368696564656c696768742e636f6d2f77702d636f6e74656e742f75706c6f6164732f517569636b736f72742e706e673f773d313130302673736c3d31)

- Analysis

  - Divide & conquer
  
  - Recursive
  
  - Not stable 
  
    - partitioning logic in quick sort algo does not ensure stability
    
  - Time complexity
  
    - O(nlogn) : best or average case (balanced partition)
    
    - O(n<sup>2</sup>) : worst case (by using randomized version can be avoided)

<br>

<br>

