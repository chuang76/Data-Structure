# Karger's Min Cut Algorithm

1. 在圖中隨機選取一條邊 , 將邊的兩個端點合併 (contraction) 成一個 set

   同時消除所有因為合併產生 loop 的邊

2. recursive , 直到圖只剩兩個點

3. return 最終兩個點之間的邊

   ![](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e7/Single_run_of_Karger%E2%80%99s_Mincut_algorithm.svg/683px-Single_run_of_Karger%E2%80%99s_Mincut_algorithm.svg.png)

