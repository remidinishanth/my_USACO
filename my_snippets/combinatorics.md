TODO: https://codeforces.com/contest/1536/problem/F

## Enumerative combinatorics

### Catalan numbers
The Catalan numbers are a remarkable sequence of numbers that “solve” a number of seemingly unrelated counting problems. 

* **Triangulation of polygon:** A convex `(n+2)`-gon can be split into `n` triangles by `n-1` non-intersecting diagonals. The number of different ways of splitting is given by catalan number Cn. \
 ![image](https://user-images.githubusercontent.com/19663316/121805524-3f443880-cc69-11eb-88a5-3ae9587e94d1.png)\
 Proof: Given `(n+2)-gon`, say we consider the base of the polygon and number vertices from `1` to `n`. Suppose that the third vertex of the base triangle is `k`, the green polygon is `k+1`-gon and the red polygon is `n+k-2`-gon, then we get the following recurrence relation.\
 ![image](https://user-images.githubusercontent.com/19663316/121806031-a6fb8300-cc6b-11eb-83d4-e3e0c7d74bbf.png)
 
* **Casheir Problem:** Cn is the number of ways to form a "mountain range" with n upstrokes and n downstrokes that all stay above a horizontal line. The mountain range interpretation is that the mountains will never go below the horizon. For `n = 3`  `Cn = 5`.\
  ![image](https://user-images.githubusercontent.com/19663316/121807707-e6799d80-cc72-11eb-8f5b-d4024f185e7d.png)
  Say in a country we only have 2 coin denominations `5` and `10`. Now suppose that we have `2n` people in a line waiting to buy a movie ticket, `n` of them are having `5` rupees and the other `n` are having `10` rupees and the cashier has no change. How many different ways are possible such that ticket seller is always able to satisfy all the people. If we consider `5` as `+1` and `10` as `-1` then for the people in the line, the prefix sum should always be `>= 0`. If we consider `5` as moving 1 unit in x direction and `10` and moving 1 unit in y direction. We should never touch the line `y = x + 1`.
  ![image](https://user-images.githubusercontent.com/19663316/121807919-ceeee480-cc73-11eb-8446-7997342bbcc2.png)
  ![image](https://user-images.githubusercontent.com/19663316/121807874-a23acd00-cc73-11eb-8fec-9ca0ad1ffa25.png)

  The number of invalid paths can be calculated Andre's reflection principle. Andre's Reflection Principle: A path is invalid if it touches or crosses the line `y = x + 1`. In any case it touches the line the first time at let's say 𝑃. Now, we reflect the first part of the path from 𝐴=(0,0) to 𝑃 at the line `y = x + 1` getting a path from `A′=(−1,1)`. So the total valid paths = `[All paths from (0, 0) to (n, n)]` - `[All paths from (-1, 1) to (n, n)]`. `[All paths from (0, 0) to (n, n)]` = `[number of ways of arranging n A's and n B's = (2n choose n)]`\
  ![image](https://user-images.githubusercontent.com/19663316/121806851-2f2f5780-cc6f-11eb-9a63-df2c741ceb28.png)
  ![image](https://user-images.githubusercontent.com/19663316/121807149-9bf72180-cc70-11eb-8c3f-7d08a4350c77.png)
  
  **Bertrand's ballot problem** is the question: "In an election where candidate A receives p votes and candidate B receives q votes with p > q, what is the probability that A will be strictly ahead of B throughout the count?" The answer is  (p - q)/(p + q). The number of favourable ways `(p+q-1 choose p-1)` - `(p+q-1 choose p)`. Proof: First vote should always go to candidate A, now we are left with `(p-1)` A's votes and `q` B's votes and now ties are allowed, so by reflection trick we get `(p+q-1 choose p-1)` - `(p+q-1 choose p)`. If ties are allowed in the original problem then the answer would be `(p+q choose q) - (p+q choose q-1)`.




