TODO: https://contest.cs.cmu.edu/295/s20/tutorials/counting.mark

### CF 721 Div2 C. Sequence Pair Weight

The weight of a sequence is defined as the number of unordered pairs of indexes `(i, j)` (here `i < j`) with same value `(a𝑖 = a𝑗)`. For example, the weight of sequence `a = [1,1,2,2,1]` is `4`. The set of unordered pairs of indexes with same value are `(1,2), (1,5), (2,5), and (3,4)`.

You are given a sequence `a` of `n` integers. Print the sum of the weight of all subsegments of `a`.

A sequence `b` is a subsegment of a sequence `a` if `b` can be obtained from `a` by deletion of several (possibly, zero or all) elements from the beginning and several (possibly, zero or all) elements from the end.

**Solution**

For each subsegment, we have `i` possible choices for starting position of the subsegment and `(n - j + 1)` for ending position of the subsegment. For each element `a[i]` it is counted towards weight for any segment which start with index less than `i`, hence we can maintain a map to count how many times can it be included `m[a[i]] += i`. Now for every segment whose end is greater than `i` we count the summ of all segments till this index `i`.

```cpp
const int N = 1e5 + 5;
 
int n;
int a[N];
 
int32_t main()
{
	int t;
	cin >> t;
	while(t--)
	{
		cin >> n;
		for(int i = 1; i <= n; i++)
			cin >> a[i];
		map<int, int> m;
		int ans = 0;
		for(int i = 1; i <= n; i++)
		{
			ans += (n - i  + 1) * (m[a[i]]);
			m[a[i]] += i;
		}
		cout << ans << endl;
	}
	return 0;
}

```
