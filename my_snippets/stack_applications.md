## Largest Rectangle Area in Histogram

Important Observation

Lets consider 2 consecutive histograms H[i] and H[i+1]. Lets assume `H[i+1] < H[i]`

In such a case, for all histograms X with index > i + 1 when traversing left for L, there is no point looking at H[i] after looking at H[i+1]. If H[i+1] > X, obviously H[i] > X as we already know H[i] > H[i+1]

Then, whats the next entry we would want to look at? We would want to look at the first histogram left of H[i+1] with height less than H[i+1].

We traverse all histograms from left to right, maintain a stack of histograms. Every histogram is pushed to stack once. A histogram is popped from stack when a histogram of smaller height is seen. When a histogram is popped, we calculate the area with the popped histogram as smallest histogram. How do we get left and right indexes of the popped histogram – the current index tells us the ‘right index’ R and index of previous item in stack is the ‘left index’ L. Following is a rough

### Linear search using a stack of incomplete subproblems

We process the elements in left-to-right order and maintain a stack of information about started but yet unfinished subhistograms. 

Whenever a new element arrives it is subjected to the following rules.

* If the stack is empty we open a new subproblem by pushing the element onto the stack. 
* Otherwise we compare it to the element on top of the stack. If the new one is greater we again push it. If the new one is equal we skip it. In all these cases, we continue with the next new element.
* If the new one is less, we finish the topmost subproblem by updating the maximum area w.r.t. the element at the top of the stack. Then, we discard the element at the top, and repeat the procedure keeping the current new element. This way, all subproblems are finished until the stack becomes empty, or its top element is less than or equal to the new element, leading to the actions described above. If all elements have been processed, and the stack is not yet empty, we finish the remaining subproblems by updating the maximum area w.r.t. to the elements at the top.
For the update w.r.t. an element, we find the largest rectangle that includes that element. Observe that an update of the maximum area is carried out for all elements except for those skipped. If an element is skipped, however, it has the same largest rectangle as the element on top of the stack at that time that will be updated later.
The height of the largest rectangle is, of course, the value of the element. At the time of the update, we know how far the largest rectangle extends to the right of the element, because then, for the first time, a new element with smaller height arrived. The information, how far the largest rectangle extends to the left of the element, is available if we store it on the stack, too.
We therefore revise the procedure described above. If a new element is pushed immediately, either because the stack is empty or it is greater than the top element of the stack, the largest rectangle containing it extends to the left no farther than the current element. If it is pushed after several elements have been popped off the stack, because it is less than these elements, the largest rectangle containing it extends to the left as far as that of the most recently popped element.
Every element is pushed and popped at most once and in every step of the procedure at least one element is pushed or popped. Since the amount of work for the decisions and the update is constant, the complexity of the algorithm is O(n) by amortized analysis.

```python
class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        rect_area = 0
        stack = []  # We will just use a list to represent the stack
        heights.append(0)  # Prevents a few conditional statements to handle the final case
        for i, v in enumerate(heights):
            while stack and heights[stack[-1]] > v:
                # if we are in this while loop, we know that there are currently items in the stack
                # and that the height of our currently viewed bar is less than the top item in the stack
                # and thus we need to pop it out and calculate the area of the bar before we can add
                # the current index into our monotonic stack
                height = heights[stack.pop()]
                if stack:
                    # Notice that since we know the index of the current bar, we don't actually
                    # need to keep track of how many bars we popped for the width
                    width = i - stack[-1] - 1
                else:
                    # No items in the stack? We popped all items out and thus the current bar <= to 
                    # all bars in positions < i
                    width = i
                rect_area = max(rect_area, height * width)
            # We know that either the stack is empty at this point or all items in the stack are <=
            # height[i]
            stack.append(i)
        return rect_area
```

https://stackoverflow.com/questions/9493853/given-an-array-find-out-the-next-smaller-element-for-each-element/9495815#9495815

## Given an array, find out the next smaller element for each element. 

Given an array find the next smaller element in array for each element without changing the original order of the elements.

For example, suppose the given array is 4,2,1,5,3.

The resultant array would be 2,1,-1,3,-1.

### Solution

![image](https://user-images.githubusercontent.com/19663316/116826635-aa9ee300-abb2-11eb-9df8-53804f4fc703.png)

```python
def find_next_smaller_elements(xs):
    ys=[-1 for x in xs]
    stack=[]
    for i,x in enumerate(xs):
        while len(stack)>0 and x<xs[stack[-1]]:
           ys[stack.pop()]=x
        stack.append(i)
    return ys

>>> find_next_smaller_elements([4,2,1,5,3])
[2, 1, -1, 3, -1]
>>> find_next_smaller_elements([1,2,3,4,5])
[-1, -1, -1, -1, -1]
>>> find_next_smaller_elements([5,4,3,2,1])
[4, 3, 2, 1, -1]
>>> find_next_smaller_elements([1,3,5,4,2])
[-1, 2, 4, 2, -1]
>>> find_next_smaller_elements([6,4,2])
[4, 2, -1]
```

## Brian Bi t3nsor

```cpp
// Linear time all nearest smaller values, standard stack-based algorithm.
// ansv_left stores indices of nearest smaller values to the left in res. -1 means no smaller value was found.
// ansv_right likewise looks to the right. v.size() means no smaller value was found.
void ansv_left(vector<int>& v, vector<int>& res) {
	stack<pair<int, int> > stk; stk.push(make_pair(INT_MIN, v.size()));
	for (int i = v.size()-1; i >= 0; i--) {
		while (stk.top().first > v[i]) {
			res[stk.top().second] = i; stk.pop();
		}
		stk.push(make_pair(v[i], i));
	}
	while (stk.top().second < v.size()) {
		res[stk.top().second] = -1; stk.pop();
	}
}

void ansv_right(vector<int>& v, vector<int>& res) {
	stack<pair<int, int> > stk; stk.push(make_pair(INT_MIN, -1));
	for (int i = 0; i < v.size(); i++) {
		while (stk.top().first > v[i]) {
			res[stk.top().second] = i; stk.pop();
		}
		stk.push(make_pair(v[i], i));
	}
	while (stk.top().second > -1) {
		res[stk.top().second] = v.size(); stk.pop();
	}
}
```

source: https://github.com/t3nsor/codebook/blob/master/ansv.cpp

## Psychos in a Line

There are n psychos standing in a line. Each psycho is assigned a unique integer from 1 to n. At each step every psycho who has an id greater than the psycho to his right (if exists) kills his right neighbor in the line. Note that a psycho might kill and get killed at the same step.

You're given the initial arrangement of the psychos in the line. Calculate how many steps are needed to the moment of time such, that nobody kills his neighbor after that moment. Look notes to understand the statement more precise.

Input:
The first line of input contains integer n denoting the number of psychos, (1 ≤ n ≤ 10^5). In the second line there will be a list of n space separated distinct integers each in range 1 to n, inclusive — ids of the psychos in the line from left to right.

Example: In the first sample line of the psychos transforms as follows: [10 9 7 8 6 5 3 4 2 1]  →  [10 8 4]  →  [10]. So, there are two steps.

### Solution

```cpp
const int MAX_N = 100010;
const int INF = 1000000;
 
int n;
int values[MAX_N], life[MAX_N];
stack<int> killers;

int main() {
  scanf("%d ", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d ", &values[i]);
  }
 
  life[0] = INF;
  killers.push(0);
  for (int i = 1; i <= n; ++i) {
    life[i] = 1;
    while (killers.size() && values[i] > values[killers.top()]) {
      life[i] = max(life[i], life[killers.top()] + 1);
      killers.pop();
    }
    killers.push(i);
  }
 
  int sol = 0;
  for (int i = 1; i <= n; ++i) {
    if (life[i] < INF) {
      sol = max(sol, life[i]);
    }
  }
 
  printf("%d\n", sol);
 
  return 0;
}
```

