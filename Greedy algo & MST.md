# Greedy algo & MST

- Topic

  - optimal substructure

  - greedy-choice property

  - Prim's algo

  - Kruskal's algo

    

- Recall greedy algo

  - greedy algo repeatedly makes <u>locally best</u> choice/decision, ignoring effect on future

    ![](https://pbs.twimg.com/profile_images/552145045663408129/egywNuyx_400x400.png)

  - like cookie monster, repeatedly eat another cookie :cookie: (but maybe it will bite you in the future)

  - standard algo : eat the largest cookie first!



- what is our problem ? 

  - tree : connected acyclic graph

  - spanning : contains all the vertices

  - spanning tree of graph G : subset of edges of G that form a tree & hit all vertices of G

    (focus on G is connected, or we can get spanning forest)

  - minimum spanning tree : 

    given weighted graph G = (V, E) & edge-weights w : E → R

    find a spanning tree T of minimum weight : 
    $$
    \sum_{e\in T}^{} w(e)
    $$

  - so our problem is finding a MST, it's a relatively simple problem, but it is not easy to find an algorithm (Because you have to prove a lot to make sure that you really find the right tree!)



- naive algorithm

  - try all spanning trees and compute the weight of each tree and return the minimum

  - the number of spanning trees can be exponential number, so it's bad

  - so we're going to get a polynomial algorithm 

  

- Greedy properties

  1. optimal structure 

     - optimal solution to problem incorporates optimal solution to subproblems

     - it means if you can solve subproblems optimally, then you can solve your original problem

       (this may happen recursively)

     - in some sense, greedy is a special form of dynamic programming

  2. greedy-choice property

     - eating largest cookie is actually a good thing to do :cookie:
     
     - if we keep making locally optimal choices, then will lead to global optimal solution



- Optimal substructure for MST

  - if e = {u, v} is an edge of some MST, how can we simplify the graph ? (fewer edges)

  - remove e ? -> but it may be disconnected

  - merge two nodes into one !

    - then any edge adjacent to vertex u or v is adjacent to the newly created vertex

    - and the process could result in a multiedge if u and v have a <u>mutual neighbor</u>

    - we resolve the multiedge problem by creating a single edge with the <u>minimum weight</u> between the two edges 
    
    - so if T' is a MST of G/e (G removes e), then T' ∪ {e} is a MST of G

  

- Dynamic program

     - step

       1. guess edge e in a MST (safe edge)

       2. contract e

       3. recurse

       4. decontract

       5. add e to MST

     - [ 聯想:cloud:] 感覺想法跟 Kargen's Min Cut 有點像

         - Reference : [graph contraction](http://www.cs.cmu.edu/afs/cs/academic/class/15210-f12/www/lectures/lecture16.pdf "link")

     - however, it's also a bad algorithm -> need exponential running time

         because at every step, we're <u>guessing</u> an arbitrary edge in the graph, there's no structure

         and there are <u>exponential number</u> of edges that we can guess to form MST

     - but we can get polynomial if we remove guessing process

     - so (1) instead of guessing edge, we can <u>choose a good choice</u> (choose biggest cookie! :cookie:)

         - [ 聯想☁️] 感覺想法跟 IR 裡提過的 Clustering pruning 有點像 , 比起隨機亂選 , 不如一開始就認真的 choose

           

- Lemma 1 : If T' is a minimum spanning tree of G/e, then T' ∪ {e} is an MST of G 

  - Proof :

    Let T* is a MST of G contains edge e, then T*/e is a spanning tree of G/e = G'

    By definition, T' is a MST of G/e = G', thus the total weight of T' is less than or equal to T*/e, means

    ​	  w(T') ≦ w(T* / e)

    ​	  w(T') + w(e) ≦ w(T* / e) + w(e) = w(T*)

    Thus we can get T' ∪ {e} is an MST of G !



- Greedy-choice property for MST

  - Lemma 2

    1. consider any cut (S, V-S)

    2. say e is a least-weight edge crossing cut

       e = {u, v} , u ∈ S , v ∈  V-S

    3. then e ∈ some MST

  - question : why the edge e is guaranteed to be the MST ?

  - Proof :  

    - idea : use cut & paste argument (用在 greedy 好用)

      ![](https://lcopl.files.wordpress.com/2015/04/cutcopypaste.gif)

    - step

      1. let T* be a MST of G and say e ∉ T* 

      2. so there must be a an edge e' ∈ MST crossing the cut (then we can start to cut & paste!)

      3. (T* - e' ∪ e) is spanning tree (if we remove e', does it will be disconnected? 

         don't worry! we have added e, so it is still a spanning tree, then we need to do is to prove it is minimum)

      4. consider the weight of T* - e' ∪ e, and by definition, e is a least weight edge crossing cut, 

         so w(e') ≦ w(e), we can get  w(T* - e' ∪ {e}) = w(T* ) - w(e') + w(e) ≦ w(T*)

         So we know w(T* - e' ∪ e) is less than or equal to the w(T*), which is optimal weight (minimum weight)

         Thus we can conclude that (T* - e' ∪ e) is actually MST of G (and it includes our edge e!) 

      5. 注意到了嗎 ? we only modified edges crossing cut(S, V-S) :smile:

         

- [思考:cloud:] : 把 lemma 2 合到 lemma 1 , 我們就可以不用 random 挑 edge 啦 , 藉由 polynomial 的 running time 就可以得出 MST 了

- 接下來我們就要用上述兩個 lemma 來建立 algorithm 



## Prim's algo

- [思考:cloud:] : 跟 Dijkstra 有點像 , 想法是 choose cut

  - we're going to start out with an obvious cut, which is a single vertex

  - suppose we choose vertex s, then select the least weight edge e from s and put it in our MST

  - then consider s and the vertex t (which is adjacent to s with e) together, do recursively

- step

  1. maintain priority queue Q on V \ S

     - question : what is the key value of that node stored in the priority queue ?

       →  v.key = min { w(u, v) | u ∈ S }

       so the key value is the <u>minimum weight</u> of edge which crosses the cut (cut u and

  2. initialization

     - let Q stores V (because S is empty, so Q will store everybody)

     - s.key = ∅ for arbitrary start vertex s ∈ V

     - for v ∈ V \ {s} , v.key = ∞ (because we haven't yet seen any edges that go in there)

  3. (do a loop) until Q empty :

     - (if Q is empty, that means S is everybody, and we're done!)

     - u = Extract - Min(Q), add u to S (remove vertex u from the Q)

     - then we look at all of the <u>neighbors</u> of u 

     - for v ∈ Adj[u] :

       - if v ∈ Q (means v ∉ S) & w(u, v) < v.key :

         - v.key = w(u, v)  (update the key, because key is supposed to be the min) (<u>decrease-key</u>, so you may move in heap)

         - v.parent = u (use pointer to remember the trace)

       - so when you end up extracting a vertex, you're already figured out which edge you added to put into the set

       - [思考:cloud:] 

         - why we consider vertex v ? can we consider vertex u and choose the least weight edge from u to v ? (it's same thing :laughing:)

         - prim's algo 的角度是 vertex , 藉由 neighbor 從 queue 裡面選出新的 vertex , 

           並從兩個 vertices 中選出 weight 最少的邊 ,  接下來考慮新的 vertex , 不斷地做 iteration , 

           直到所有 vertices 都被選完 (此時 queue 為 empty) , 我們即產生 MST

           

           ![](http://lcm.csa.iisc.ernet.in/dsa/img425.gif)

          

  - return { { v, v.parent } | v ∈ V } (根據這個就可以全部串起來得到 MST)

- pseudo code

  ![](https://i.stack.imgur.com/mckRr.png)

- 感受一下

  ![](https://i.imgur.com/k6OJ0jt.gif?1)

- Correctness

  - Reference : loop invariant (類似歸納法)

  - the key value of every vertex always remains the minimum ?

  - 兩個 invariants 怎麼保證它 true

    1. v ∉ S ⇒ v.key = min {w(u, v) | u ∈ S}

    2. Tree T<sub>s</sub> within S  ⊆ MST of G

  - proof

    1. 第一個 follow 上面的 algo (for v ∈ Adj[u] 這裡)

    2. 第二個 

       - by induction, T<sub>s</sub> ⊆ some MST T* (T* contain T<sub>s</sub>)

       - T<sub>s</sub> → T<sub>s'</sub> = T<sub>s</sub> ∪ {e}

       - by greedy choice property : (一直藉由 cut & paste)

         - modify T* to include e & T<sub>s</sub> 

         - because the edges of T<sub>s</sub> do not cross the cut, we do not disturb it, remain T<sub>s</sub> in T* , just made edge e in T*, and we get new MST

         - so we keep changing T* , but we preserve this property

- Runtime

  - O(V lg V + E) 

  - 待補



## Kruskal's algo

- Idea

  - The global minimum edge is the minimum weight edge for all cuts that it crossed

    (the global minimum edge is valid choice)

  - use DP concept to contract edge

- Catch

  - maintain connected components in MST-so-far T (actually forest) in union-find structure

    - review : union-find have three operations

      1. make set
      
      2. union
      
      3. find set

  - T = ∅ (initially)

  - for v ∈ V : Make-Set(v)

    (so every vertex lives in its own singleton set)

  - sorting E by weight (incr. order)

  - for e = {u, v} ∈ E

    - how can we know two vertices u and v are in the same connected component ?

      -> call Find-Set function twice and see whether they are equal

    - if Find-Set(u) ≠ Find-Set(v) :

      - T = T ∪ {e}
    
      - Union(u, v)

- pseudo code

  ![](https://i.stack.imgur.com/RN7h3.jpg)

- 舉例

  ![](https://www.geneseo.edu/~baldwin/csci242/spring2013/kruskal.png)

- 感受一下

  ![](https://upload.wikimedia.org/wikipedia/commons/thumb/b/bb/KruskalDemo.gif/220px-KruskalDemo.gif)

- Runtime

  - O( sort(E) × E ．α(V) + V )
  
  - 待補

- Correctness

  - 待補

