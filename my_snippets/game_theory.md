Problem: https://atcoder.jp/contests/abc195/tasks/abc195_e

Solution: 
Let us consider if Takahashi is possible to win after the N − 1 rounds. Let us regard `T` as a decimal number and `r` be the remainder by 7 . 

Also, we identify S<sub>N</sub> with the corresponding digit. 

If X<sub>N</sub> is `T`, then Takahashi will win if either 10r or 10r + S<sub>N</sub> is a multiple of 7 . 

If X<sub>N</sub> is `A`, then Takahashi will win if both 10r and 10r + S<sub>N</sub> are multiples of 7 . 

As you can see, we can define the following DP, in the reversed order. 

dp[i]=The set of integers r that satisfies the following condition, where Condition: if the remainder of T divided by 7 is r after the i<sup>th</sup> round end, 
Takahashi will win 

The initial state is dp[N] = { 0 }. 

The transitions are

dp[i−1] = { r | ( 10r mod 7 ) ∈ dp[i]  or ( 10r + S<sub>i</sub> mod 7 ) ∈ dp[i]}  if X<sub>i</sub> is `T`, 

dp[i−1] = { r | ( 10r mod 7 ) ∈ dp[i] and ( 10r + S<sub>i</sub> mod 7 ) ∈ dp[i]}  if X<sub>i</sub> is `A`,


If 0 ∈ dp[0] at last, Takahashi wins; otherwise, Aoki wins. The time complexity is O(N) .
