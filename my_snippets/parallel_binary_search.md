# Parallel Binary Search

## Problem Meteors

Byteotian Interstellar Union (BIU) has recently discovered a new planet in a nearby galaxy. The planet is unsuitable for colonisation due to strange meteor showers, which on the other hand make it an exceptionally interesting object of study.

The member states of BIU have already placed space stations close to the planet's orbit. The stations' goal is to take samples of the rocks flying by. The BIU Commission has partitioned the orbit into *m* sectors, numbered from *1* to *m*, where the sectors *1* and *m* are adjacent. In each sector there is a single space station, belonging to one of the *n* member states.

Each state has declared a number of meteor samples it intends to gather before the mission ends. Your task is to determine, for each state, when it can stop taking samples, based on the meter shower predictions for the years to come.

### Input

The first line of the standard input gives two integers, *n* and *m* (1 <=n,m <=300000), separated by a single space, that denote, respectively, the number of BIU member states and the number of sectors the orbit has been partitioned into.

In the second line there are *m* integers  *o*<sub>i</sub>(1 <= o<sub>i</sub> <=*n*), separated by single spaces, that denote the states owning stations in successive sectors.

In the third line there are *n* integers *p*<sub>i</sub> (1 <= p<sub>i</sub> <=10<sup>9</sup>), separated by single spaces, that denote the numbers of meteor samples that the successive states intend to gather.

In the fourth line there is a single integer *k* (1 <= *k* <= 300000) that denotes the number of meteor showers predictions. The following *k* lines specify the (predicted) meteor showers chronologically. The *i*-th of these lines holds three integers l<sub>i</sub>, r<sub>i</sub>, a<sub>i</sub> (separated by single spaces), which denote that a meteor shower is expected in sectors l<sub>i</sub>, l<sub>i+1</sub>,...,r<sub>i</sub> (if l<sub>i</sub> <= r<sub>i</sub>) or sectors l<sub>i</sub>, l<sub>i+1</sub>,...,*m*,1,..., r<sub>i</sub>  (if l<sub>i</sub> > r<sub>i</sub>), which should provide each station in those sectors with  meteor samples (1 <= a<sub>i</sub> <= 10<sup>9</sup>).

In tests worth at least 20% of the points it additionally holds that *n*,*m*,*k* <= 1000.

### Ouput

Your program should print *n* lines on the standard output. The *i*-th of them should contain a single integer *w*<sub>i</sub>, denoting the number of shower after which the stations belonging to the *i*-th state are expected to gather at least *p*<sub>i</sub> samples, or the word *NIE* (Polish for no) if that state is not expected to gather enough samples in the foreseeable future.

### Example

For the input data:

```
3 5
1 3 2 1 3
10 5 7
3
4 2 4
1 3 1
3 5 2
```
the correct result is:

```
3
NIE
1
```

Task authors: Paweł Mechlinski and Jakub Pachocki.

Source: [szkopul.edu]([https://szkopul.edu.pl/problemset/problem/7JrCYZ7LhEK4nBR5zbAXpcmM/site/?key=statement)

## Solution

Prerequisites for solution

* Binary search

* Segment tree with two operations

  * Add number  𝑋  on segment (lazy propagation/update)

  * Get value of  𝑝 'th element

It involves a parallel binary search trick.

Just for simplicity sake, let’s make an additional dummy  𝐾+1 'st meteor shower, covering segment  [1;𝑀]  with infinity amount of meteors, so after it there will be definitely sufficient meteors for all companies.

Now, we know that for each company answer will be between  [1;𝐾+1] , inclusively. So, let’s create two arrays, denoting the lower and upper bounds of answers,  𝐿𝑖  and  𝑅𝑖 , with  𝐿𝑖=1  and  𝑅𝑖=𝐾+1 , initially.

And now we will make  O(𝑙𝑜𝑔(𝐾)) iterations of parallel binary search.

For  𝑖'th company we want to efficiently check whether first  𝑀𝑖=(𝐿𝑖+𝑅𝑖)/2  showers will provide  ≥𝑃𝑖  meteors. We will group same  𝑀𝑖 's together and then do the following process:

1. Initialize segment tree with  𝑀  leafs with  0 , where  𝑖 'th leaf will denote number of meteors  𝑖 'th sector currently has.

2. Start making showers in chronological order. It is essentially just making an addition on segment.

3. Suppose we just processed the shower number  𝑄 . If some  𝑀𝑖=𝑄 , then we can - in  O(𝑛𝑢𝑚𝑂𝑓𝑃𝑜𝑠𝑖𝑡𝑖𝑜𝑛𝑠𝑖)  time - if there is sufficient number of meteors already and move its  𝐿𝑖  or  𝑅𝑖 . Total number of iterations will be  O(∑𝑁𝑖=1𝑛𝑢𝑚𝑂𝑓𝑃𝑜𝑠𝑖𝑡𝑖𝑜𝑛𝑠𝑖)  which is just  O(𝑀) .
After, just output answers, and if for some company answer is  𝐾+1 , then output NIE.

Result

Thus, we have solved the problem in  O((𝑀+𝑁+𝐾⋅log(𝑀))⋅𝑙𝑜𝑔(𝐾)) .

Source: [Quora](https://www.quora.com/What-are-some-POI-Polish-Olympiad-in-Informatics-problems-with-very-elegant-solutions)

## Codeforces Blog

The naive binary solution here is to do a binary search for each of the N member states. We can update in a range using segment trees with lazy propagation for each query. The time complexity of such a solution would be O(N * logQ * Q * logM). But this one will easily TLE.

Let's see if there's something we are overdoing. For every member state, the binary search applies all the queries until a point multiple times! For example, the first value of mid in the binary search is same for all member states, but we are unnecessarily applying this update everytime, instead of somehow caching it.

Let's do all of these N binary searches in a slightly different fashion. Suppose, in every step we group member states by the range of their binary search. In the first step, all member states lie in range [1, Q]. In the second step, some lie in range [1, Q / 2] while some lie in range [Q / 2, Q] depending on whether the binary search predicate is satisfied. In the third step, the ranges would be [1, Q / 4], [Q / 4, Q / 2], [Q / 2, 3Q / 4], [3Q / 4, Q]. So after logQ steps, every range is a single point, denoting the answer for that member state. Also, for each step running the simulation of all Q queries once is sufficient since it can cater to all the member states. This is pretty effective as we can get our answer in Q * logQ simulations rather than N * Q * logQ simulations. Since each simulation is effectively O(logM), we can now solve this problem in O(Q * logQ * logM).


### Pseudo Code

```pascal
for all logQ steps:
    clear range tree and linked list check
    for all member states i:
        if L[i] != R[i]:
            mid = (L[i] + R[i]) / 2
            insert i in check[mid]
    for all queries q:
        apply(q)
        for all member states m in check[q]:
            if m has requirements fulfilled:
                R[m] = q
            else:
                L[m] = q + 1
```

In this code, the apply() function applies the current update, i.e. , it executes the range update on segment tree. Also to check if the requirements are fulfilled, one needs to traverse over all the sectors owner by that member state and find out the sum. In case you still have doubts, go over to the next section and see my code for this problem.

## Errichto's Solution

I wrote a recursive function `rec(int low, int high, vector<int> owners)` and I run it once as `rec(1, q, {1,2,...,n})`. Vector owners contains people for which answer is in interval [low, high].

Let's denote mid = (low + high) / 2. I want to know which owners already won after the first mid queries. Then, I run `rec(low, mid, owners_who_won)` and `rec(mid, high, those_who_didnt)`.

To check "which owners already won" I need standard range tree. In my code below you can find a variable act_tree denoting the number of first queries summed in the tree. Let's say my function is run with arguments low = 70 and high = 90. My global tree should now contain the sum of first mid = 80 queries (so there should be act_tree = 80). Later I want to run rec(70, 80) and rec(80, 90). I need to do the following:

1. I subtract queries 80, 79, 78, 77, 76.
2. The tree contains the sum of first 75 queries (act_tree = 75). I can run rec(70, 80).
3. I add queries 76, 77, ..., 85.
4. The tree contains the sum of first 85 queries. I can run rec(80, 90).
5. I subtract queries 85, 84, 83, 82, 81.

The time complexity is something like O((N+Q)⋅𝑙𝑜𝑔<sup>2</sup>(N+Q))  . Naive implementation will result in the memory complexity O(Q+N.𝑙𝑜𝑔(Q)). To make it O(N + Q) you need to pass vector owners by reference and clear it after checking which owners already won. Check details in my code below.

```cpp
#include<bits/stdc++.h>
using namespace std;

const int pot = 512 * 1024;
long long tr[2*pot];

vector<int> properties[pot];
int need[pot];
int ans[pot];
int from[pot], to[pot], val[pot];

void tree_add(int low, int high, int v) {
	assert(low <= high);
	low += pot;
	high += pot;
	tr[low] += v;
	if(low != high) tr[high] += v;
	while(low + 1 < high) {
		if(low % 2 == 0) tr[low+1] += v;
		if(high % 2 == 1) tr[high-1] += v;
		low /= 2;
		high /= 2;
	}
}
void tree_add(int i_q, int multiplier) {
	int v = val[i_q] * multiplier;
	if(from[i_q] <= to[i_q])
		tree_add(from[i_q], to[i_q], v);
	else {
		tree_add(from[i_q], pot - 1, v);
		tree_add(0, to[i_q], v);
	}
}
long long tree_get(int where) {
	long long s = 0;
	for(int x = pot + where; x >= 1; x /= 2)
		s += tr[x];
	return s;
}

void rec(int low, int high, vector<int> & owners, int & act_tree) {
	if(owners.empty()) return;
	int mid = (low + high) / 2;
	while(act_tree < mid)
		tree_add(++act_tree, 1);
	while(act_tree > mid)
		tree_add(act_tree--, -1);
	
	vector<int> left_owners;
	vector<int> right_owners;
	for(int who : owners) {
		long long his_value = 0;
		for(int where : properties[who]) {
			his_value += tree_get(where);
			if(his_value >= need[who]) break;
		}
		if(his_value >= need[who]) {
			left_owners.push_back(who);
			ans[who] = high;
		}
		else
			right_owners.push_back(who);
	}
	owners.clear(); // thanks to this line the memory is O(n), not O(n log(n))
	if(low < high) {
		rec(low, mid, left_owners, act_tree);
		rec(mid + 1, high, right_owners, act_tree);
	}
}

int main() {
	int n, len;
	scanf("%d%d", &n, &len);
	for(int where = 1; where <= len; ++where) {
		int who;
		scanf("%d", &who);
		properties[who].push_back(where);
	}
	for(int who = 1; who <= n; ++who)
		scanf("%d", &need[who]);
	int q;
	scanf("%d", &q);
	for(int day = 1; day <= q; ++day)
		scanf("%d%d%d", &from[day], &to[day], &val[day]);
	
	vector<int> owners;
	for(int who = 1; who <= n; ++who)
		owners.push_back(who);
	
	int act_tree = 0;
	rec(1, q, owners, act_tree);
	
	for(int who = 1; who <= n; ++who) {
		if(ans[who]) printf("%d\n", ans[who]);
		else puts("NIE");
	}
	return 0;
}
```
