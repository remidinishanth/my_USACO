* First, **reread the problem statement**. Did you miss something important? Are you sure you have understood what the problem is asking for? Double-check your understanding on the sample input and output. Break down the problem and make progress by attacking
the parts.
* Test given in the bold is very important, make sure that you use all the information and constriants given in the problem statement.
* If you are asked to count/find something, check if finding the complement of it is easier.
* Whenever you see, there is atleast `⌈N/2⌉` or `⌈N/3⌉` elements in the answer, see if you can use randomization. Say we need to have atleast `⌈N/2⌉` elements in the answer, if we choose a person at random, there is half probability that element is in the answer. So if we repeat this process say 30 times, then the probability of failure reduces to `(1/2)^30`. Hence this works most of the time.
  * Problem: https://codeforces.com/contest/1523/problem/D , Solution: https://codeforces.com/contest/1523/submission/117881477
  ![image](https://user-images.githubusercontent.com/19663316/120113940-6f380a00-c19a-11eb-8a77-b3c4c761a32d.png)
* If you see “rollbacks” in the problem statement - this is 99.9% a reference to persistence problem.
* If you can solve the problem for a chain using a segment tree, then there is a very good chance that you can solve the problem for a tree using HLD. Indeed, if you make segment trees over the heavy edges, then the answer for your path X-Y can be broken up into two paths from X to LCA(X, Y) and from Y to LCA(X, Y). Then, using that you make only logN shifts from one heavy-chain to another, you are actually making only log(N) segment-tree queries.
* All trees are bipartite, If we color them black and white, The min(number of black, number of white) nodes is ≤ ⌈n/2⌉. source: https://codeforces.com/contest/1534/problem/D
* If the given array is of odd length and we reverse prefix of odd length, then parity of number at some index doesn't change. https://codeforces.com/contest/1561/problem/E
* When order of the numbers doesn't matter, it is better to sort the numbers, https://www.codechef.com/problems/THREEDIF
* If the problem is complex, first try to solve simplified version of the problem. For e.g If the problem is of higher dimensions say 2, check what happens in linear case first and then try to generalize etc.
* Whenever something is done with 2 difference, check if you handle even and odd case seperately, https://codeforces.com/contest/1567/problem/C
* When constrains are too small, say ~ 40, think if we can think DP of higher mutil-dimensions or some flow problem. https://codeforces.com/contest/1593/problem/D2
* Strings — if the sum of lengths is `𝑆` then there are at most `√𝑆` distinct lengths.

```cpp
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/

// Do something instead of nothing, stay organised, stay ahead!, WRITE STUFF DOWN

// WA
// 1. overflow
// 2. re-initialize global variables for every test case.
// 3. edge cases like n=1

// Run time error
// 1. division by zero.
// 2. array bounds.
```

![](images/observations_17_oct_2021.png)

![image](https://user-images.githubusercontent.com/19663316/140021477-e23d5ef4-7ddd-4ffc-8111-d8d735943530.png)

![image](https://user-images.githubusercontent.com/19663316/140021439-6df2a48e-391b-491a-a412-37de619028ac.png)
