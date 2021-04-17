You are given 𝑁 ≤ 1000 items, each with some weight 𝑤𝑖. Is there a subset of items with total weight exactly 𝑊 ≤ 10<sup>6</sup>?

Standard knapsack with boolean array would be 𝑂(𝑁⋅𝑊), too slow.

```cpp
bool can[MAX_W];
int main() {
	int n, W;
	cin >> n >> W;
	can[0] = true;
	for(int id = 0; id < n; id++) {
		int x;
		cin >> x;
		for(int i = W; i >= x; i--) { // Reverse order is key
			if(can[i-x]) can[i] = true;
		}
	}
	puts(can[W] ? "YES" : "NO");
}
```

0-1 Knapsack Problem: Given n items, each with its own value Vi and weight Wi, ∀i ∈ [0..n-1], and a
maximum knapsack size S, compute the maximum value of the items that we can carry, if
we can either ignore or take a particular item (hence the term 0-1 for ignore/take).

Use these Complete Search recurrences val(id, remW) where id is the index of
the current item to be considered and remW is the remaining weight left in the knapsack:
1. val(id, 0) = 0 // if remW = 0, we cannot take anything else
2. val(n, remW) = 0 // if id = n, we have considered all items
3. if W[id] > remW, we have no choice but to ignore this item
val(id, remW) = val(id + 1, remW)
4. if W[id] ≤ remW, we have two choices: ignore or take this item; we take the maximum `
val(id, remW) = max(val(id + 1, remW), V[id] + val(id + 1, remW - W[id]))`
