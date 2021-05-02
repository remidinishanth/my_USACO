# Greedy paradigm

An algorithm is said to be greedy if it makes the locally optimal choice at each step with the
hope of eventually reaching the globally optimal solution. In some cases, greedy works—the
solution is short and runs efficiently. A problem must exhibit these two
properties in order for a greedy algorithm to work:

* It has optimal sub-structures. Optimal solution to the problem contains optimal solutions to the sub-problems
* It has the greedy property (difficult to prove in time-critical contest environment!).
If we make a choice that seems like the best at the moment and proceed to solve the
remaining subproblem, we reach the optimal solution. We will never have to reconsider
our previous choices

**Greedy-choice property** A locally optimal choice is globally optimal.

# Problems

## Coin change problem

Given a target amount V cents and a list of denominations of n coins,
i.e. we have coinValue[i] (in cents) for coin types i ∈ [0..n-1], what is the minimum
number of coins that we must use to represent amount V ? 

Example: If n = 4, coinValue = {25, 10, 5, 1} cents6, and
we want to represent V = 42 cents, we can use this Greedy algorithm: Select the largest
coin denomination which is not greater than the remaining amount, i.e. 42-25 = 17 → 17-10
= 7 → 7-5 = 2 → 2-1 = 1 → 1-1 = 0, a total of 5 coins. This is optimal.

However, this greedy algorithm does not work for all sets of coin denominations. Take for
example {4, 3, 1} cents. To make 6 cents with that set, a greedy algorithm would choose 3
coins {4, 1, 1} instead of the optimal solution that uses 2 coins {3, 3}.

### Solution

For the so-called canonical coin systems, a greedy algorithm of picking the largest denomination of coin which is not greater than the remaining amount to be made will produce the optimal result.

In order to decide whether the coin system `𝑐1=1 < 𝑐2 < 𝑐3 < …` is canonical, it suffices to check only for each 𝑚 whether the greedy solution for ⌈𝑐{𝑚+1}/𝑐𝑚⌉𝑐𝑚 is optimal. source: [Stackoverflow](https://math.stackexchange.com/questions/3121896/what-property-of-a-coin-system-makes-it-canonical)

## Courses [duration, lastDay]
There are n different online courses numbered from 1 to n. You are given an array courses where `courses[i] = [duration_i, lastDay_i]` indicate that the ith 
course should be taken continuously for duration_i days and must be finished before or on lastDay_i.

You will start on the 1st day and you cannot take two or more courses simultaneously.

Return the maximum number of courses that you can take.

[[100,200], [200,1300], [1000,1250], [2000,3200]] -> `3` [[100, 200], [200, 1300], [2000, 3200]]

[[5,5], [4,6], [2,6]] -> `2` [[4,6], [2,6]]

source: <https://leetcode.com/problems/course-schedule-iii/>

### Solution:

Sort the courses by end time, now loop through the sorted list while maintaining a priority queue storing the duration_i,  greedily remove the largest-length 
course until the total duration.

Clearly, this greedy choice makes the number of courses used maximal for each K. When considering potential future K, 
there's never a case where we preferred having a longer course to a shorter one, so indeed our greedy choice dominates all other candidates.

```python
import heapq

class Solution:
    def scheduleCourse(self, courses: List[List[int]]) -> int:
        courses.sort(key= lambda x: x[1])
        pq = []
        time_taken = 0
        for c in courses:
            time_taken += c[0]
            heapq.heappush(pq, -c[0])
            while time_taken > c[1]:
                time_taken += heapq.heappop(pq)  # Pop and return the smallest item from the heap, hence using negative values
        return len(pq)
```
