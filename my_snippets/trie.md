![](images/trie_1.png)

source: Errichto Trie youtube

Using vectors instead of static arrays

![](images/trie_2.png)

## Binary Trie - maximum XOR of Y with all numbers

<img width="879" alt="image" src="https://user-images.githubusercontent.com/19663316/185746063-9f02cc39-08f5-4569-bec2-a05f1fac56c1.png">

```cpp
int tree[6000000][2];
int root = 1;
int cnt[6000000];
int cur = 1;
void update(int x, int val) {
    int now = root;
    cnt[now] += val;
    for (int i = 29; i >= 0; i--) {
        int c = (x >> i) & 1;
        if (tree[now][c] == 0) {
            cur++;
            tree[now][c] = cur;
        }
        now = tree[now][c];
        cnt[now] += val;
    }
}

void query(int x) {
    int now = root;
    int ans = 0;
    for (int i = 29; i >= 0; i--) {
        int c = (x >> i) & 1;
        if (tree[now][1 ^ c] == 0 || cnt[tree[now][1 ^ c]] == 0) {
            ans = ans;
        } else {
            ans ^= (1 << i);
            c ^= 1;
        }
        now = tree[now][c];
    }
    printf("%d\n", ans);
}

int main() {
    int q, x;
    char word[10];

    update(0, 1);

    scanf("%d", & q);
    for (int i = 0; i < q; i++) {
        scanf("%s %d", word, & x);
        if (word[0] == '+') update(x, 1);
        else if (word[0] == '-') update(x, -1);
        else query(x);
    }

    return 0;
}
```

source: https://codeforces.com/contest/706/submission/19798788

#### Make sure you clear the array before using the trie again

Something like 

```cpp
	while(m > 0) {
		m--;
		go[m][0] = go[m][1] = 0;
		trieDp[m][0] = trieDp[m][1] = 0;
	}
```

in the submission https://codeforces.com/contest/1720/submission/168841834

#### Max XOR of Two Numbers using Trie

TODO: https://threadsiiithyderabad.quora.com/Tutorial-on-Trie-and-example-problems


Nice Problem: https://codeforces.com/contest/1720/problem/D2, see umnik implementation(from video) and https://codeforces.com/blog/entry/106136?#comment-944979


TODO: https://leetcode.com/problems/word-search-ii/ and https://leetcode.com/problems/word-search-ii/discuss/59790/Python-dfs-solution-(directly-use-Trie-implemented).
