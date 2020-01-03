// BIT with range updates, inspired by Petr Mitrichev
struct BIT {
    int n;
    vector<int> slope;
    vector<int> intercept;
    // BIT can be thought of as having entries f[1], ..., f[n]
    // which are 0-initialized
    BIT(int n): n(n), slope(n+1), intercept(n+1) {}
    // returns f[1] + ... + f[idx-1]
    // precondition idx <= n+1
    int query(int idx) {
        int m = 0, b = 0;
        for (int i = idx-1; i > 0; i -= i&-i) {
            m += slope[i];
            b += intercept[i];
        }
        return m*idx + b;
    }
    // adds amt to f[i] for i in [idx1, idx2)
    // precondition 1 <= idx1 <= idx2 <= n+1 (you can't update element 0)
    void update(int idx1, int idx2, int amt) {
        for (int i = idx1; i <= n; i += i&-i) {
            slope[i] += amt;
            intercept[i] -= idx1*amt;
        }
        for (int i = idx2; i <= n; i += i&-i) {
            slope[i] -= amt;
            intercept[i] += idx2*amt;
        }
    }
};

/*
Basically, for a BIT, there are two modes available:

a) Range query and point update
b) Range update and point querying

You are probably more familiar with BITs using (a).

For (b), it's just a very simple modification, so I'll try to explain it the best I can.

For (a), when you call update(x, v), it will add the value of v to the position at x, and 
calling query(x) will add up all the elements x' <= x and return that.

Now, to extend it to (b), we see that when we call update(x, v), it will affect all the queries x' >= x. 
Therefore, to update a range [a,b], we can call update(a,v) and update(b+1,-v). 
Then, to get a point, we call query(p). Note that this will actually return the actual value at p, not the cumulative sum.

Now, to see why this works, see the following examples.
Suppose we just called update(a,v) and update(b+1,-v).

Now, let's say we called query(p). We have three cases:
p < a. p will not be affected by the updates, so query(p) will not be affected and still return the correct result
p > b. p will be affected by the update(a,v) since p >= a, and update(b+1,-v) since p >= b+1, therefore, v-v=0 so everything cancels out and query(p) will not be affected and return the correct result
a <= p <= b. p is only affected by update(a,v), but not update(b+1,-v), therefore, query(p)'s value is increased by v, and will return the correct result

c) Range update and range querying

Similar to Range Update - Point query, we maintain a BIT (say B1)
- Add v to [a..b] --> Update(a,v) and Update(b+1,-v) on the BIT B1
- Query(p) on B1 now gives the correct value of A[p]
 
The answer we want is ( Sum(0..b) - Sum(0..a-1) ), so lets design Sum(0..p). The thing with BIT is, 
if you design it to work for one update ( which is easy to imagine ) and all possible queries on that 
one update, mostly it should work for multiple updates ;)
 
Lets consider just one update : Add v to [a..b], rest all are 0
 
Now, consider Sum(0..p) for all possible p
1. 0 <= p <  a : 0
2. a <= p <= b : v * ( p - (a-1) )
3. b <  p <  n : v * ( b - (a-1) )
 
This suggests that, for a index p, if we have (v * p) we can get the Sum(0..p) by subtracting X from it
1. 0 <= p <  a : slope = 0 and intercept = 0
2. a <= p <= b : slope = v and intercept = -v*(a-1)
3. b <  p <  n : slope = 0 and intercept = v*b - v*(a-1)
 
So, we need to maintain something else too, to get that extra intercept term and that should give 
0 for p < a, -v*(a-1) for p in [a..b], v*b-v(a-1) for p > b. 
Does this ring something ;) ? hoho ! one more BIT for keeping this intercept.
 
We need to maintain another BIT (say B2)
- Add v to [a..b] --> Update(a,-v*(a-1)) and Update(b+1,v*b) on the BIT B2
- Query(p) on B2 now gives the extra sum that should be subtracted from A[p]*p
*/
