## Problem Sheets

You are given a sheet of grid paper of squares with the total size of `N×N` cells. The number N is a power of 2. 
The cells are consecutively numbered from left to right, from top to bottom. In each cell is entered only its number.

Example for N=4

![image](https://user-images.githubusercontent.com/19663316/117642388-d74f8d80-b1a4-11eb-8454-02a2ee7827e2.png)


The sheet is iteratively folded in half, first - the bottom half over the top half, 
then the right half over the left half, until the size of the folded sheet becomes equal to `1×1`.

Obviously, the cells of the folded sheet make up a column with size of `1×1×N^2`. We denote by S = <S1, S2, ..., Sp, ... S_N^2> the array consisting of the numbers in the cells of the obtained column, from the **back to front**, where P indicates the position of the number in the string.

Question Type 1. You are given a certain number X. What is the P-position of this number in the array S?
Question Type 2. You are given a certain P-position in the string S. What is the number X in this position?

### Input
The standard input contains on the first line the integer Q(`1 ≤ Q ≤ 10000`)– the number of questions. Each of the following Q lines of the standard input contain three integers T,K,V, separated by a space: T - Question Type(T=1 or T=2), K is such that `N = 2^K` and `0 ≤ K ≤ 31`, V is either X or P based of question type.

### Output
The standard output shall contain Q lines, one for each of the standard input questions. Each of these lines shall contain a single integer PP or XX, depending on the type of the question.

Example

Input
```
3
1 1 4
2 2 14
1 2 16
```

Output
```
3
15
3
```

Explanation

Sheet for K=1, sheet will be `2×2` and S = <1,3,4,2>

![image](https://user-images.githubusercontent.com/19663316/117644082-bee07280-b1a6-11eb-9d62-b17150deced8.png)

Sheet for K=2:

S = <1, 13, 16, 4, 8, 12, 9, 5, 6, 10, 11, 7, 3, 15, 14, 2>

source: https://csacademy.com/contest/algorithms-2019-01-22-12/task/sheets/statement/

### Solution

Numbers are from back to front after folding.

```cpp
#include <iostream>
#include <stdio.h>
using namespace std;

int q, t, k;
long long p;

void fold(long long x, long long y, long long h, int k, long long cur)
{
    if (k == 0)
    {
        printf("%lld\n", h);
        return;
    }
    // cur is number of sheets after folds
    // folding bottom over top
    if (x >= (1LL << (k - 1)))  // if number belongs to bottom half
    {
        x = (1LL << k) - x - 1; // invert x
        h = (cur << 1) - h + 1; // invert h with (cur*2)
    }
    // folding right over left
    if (y >= (1LL << (k - 1)))  // if number belongs to right half
    {
        y = (1LL << k) - y - 1;
        h = (cur << 2) - h + 1; // invert h with (cur*4) 4 because of folded with x then y
    }
    fold(x, y, h, k - 1, cur << 2);
}

void unfold(long long x, long long y, long long h, int k, long long cur)
{
    if (cur == 1)
    {
        printf("%lld\n", x * (1LL << k) + y + 1);
        return;
    }
    if (h > (cur >> 1))
    {
        h = cur - h + 1;
        y = (1LL << (k + 1)) - y - 1;
    }
    cur >>= 1;
    if (h > (cur >> 1))
    {
        h = cur - h + 1;
        x = (1LL << (k + 1)) - x - 1;
    }
    unfold(x, y, h, k + 1, cur >> 1);
}

int main()
{
    scanf("%d", &q);
    while (q--)
    {
        scanf("%d%d%lld", &t, &k, &p);
        if (t == 1) fold((p - 1) / (1LL << k), (p - 1) % (1LL << k), 1, k, 1);
        else unfold(0, 0, p, 0, 1LL << (k << 1));
    }
	return 0;
}

```
source: https://csacademy.com/submission/318817/

The solution can also be implemented iteratively for example source: https://csacademy.com/submission/292131/
