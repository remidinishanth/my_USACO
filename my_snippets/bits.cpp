Name: Representing sets with bitfields
// source: https://apps.topcoder.com/forums/?module=Thread&threadID=671561&start=0

Problem: There are many ways to represent a subset of a set, but most of them are slow. 
This recipe shows how subsets from a domain of up to 64 elements can be very efficiently represented and 
manipulated as integers.

Solution: Consider a subset of the set {0, 1, ..., N - 1}. This can be represented by an N-bit binary number, 
where bit i (representing 2i) is 1 if element i is present, and 0 if element i is absent. Most modern languages 
support integers of up to 64 bits, allowing subsets of 64-element sets to be encoded (some languages also allow 
for arbitrary numbers of bits). In code examples, it is assumed that a 32-bit integer is being used.

Many set operations can be achieved by bitwise and integer arithmetic:

Set union:
A | B

Set intersection:
A & B

Set subtraction:
A & ~B

Test if set is non-empty:
A != 0

Test whether element x is in A:
(A & (1 << x)) != 0

The set containing {0, ..., x - 1}:
(1 << x) - 1

Put x in A (works even if x is already in A):
A |= 1 << x;

Remove x from A (works even if x is not in A):
A &= ~(1 << x);

Set negation:
((1 << N) - 1) & ~A

Test whether A has exactly one element:
(A > 0) && (A & (A - 1)) == 0

Remove the smallest element from A:
A = A & (A - 1)

Remove all but the smallest element from A:
A = A & ~(A - 1)

Count the number of elements in A:
// GCC:
count = __builtin_popcount(A);
// Java:
count = Integer.bitCount(A);
// Portable:
count = (A & 0x55555555) + ((A >> 1) & 0x55555555);
count = (count & 0x33333333) + ((count >> 2) & 0x33333333);
count = (count & 0x0F0F0F0F) + ((count >> 4) & 0x0F0F0F0F);
count = (count & 0x00FF00FF) + ((count >> 8) & 0x00FF00FF);
count = (count & 0x0000FFFF) +  (count >> 16);

Get the index of the smallest element in A:
// GCC:
low = __builtin_ctz(A);
// Java:
low = Integer.numberOfTrailingZeros(A);
// Portable:
low = 0;
lowbit = A & ~(A - 1);
if ((tmp & 0xAAAAAAAA) != 0) low += 1;
if ((tmp & 0xCCCCCCCC) != 0) low += 2;
if ((tmp & 0xF0F0F0F0) != 0) low += 4;
if ((tmp & 0xFF00FF00) != 0) low += 8;
if ((tmp & 0xFFFF0000) != 0) low += 16;

/*
Discussion:

Most of the set operations are straight-forward, but the operations on the smallest element are more interesting. 
Suppose we wish to find the lowest set bit of A (which is known to be non-zero). If we subtract 1 from A then this 
bit is cleared, but all the other one bits in A remain set. Thus, A & ~(A - 1) consists of only the lowest set bit of A. 
You might sometimes see this written as A & -A, because when using twos-complement arithmetic they're equivalent.

If we want the index of the highest or lowest bit (rather than the corresponding set representation), the obvious approach 
is simply to loop through the bits (upwards or downwards) until we find one that is set. At first glance this seems slow, 
since it does not take advantage of the bit-packing at all. However, if all 2N subsets of the N-element domain are equally 
likely, then the loop will take only two iterations on average, and this is actually the fastest method.

The 386 introduced CPU instructions for bit scanning: BSF (bit scan forward) and BSR (bit scan reverse). GCC exposes these 
instructions through the built-in functions __builtin_ctz (count trailing zeros) and __builtin_clz (count leading zeros). 
These are the most convenient way to find bit indices for C++ programmers in TopCoder. Be warned though: the return value 
is undefined for an argument of zero.

One can easily check if a number is a power of 2: clear the lowest 1 bit (see above) and check if the result is 0. However, 
sometimes it is necessary to know how many bits are set, and this is more difficult. GCC has a function called 
__builtin_popcount which does precisely this. However, unlike __builtin_ctz, it does not translate into a hardware instruction
(at least on x86). Instead, it uses a table-based method, but it is nevertheless quite efficient and also extremely convenient.
The language-neutral alternative listed above is not as efficient in practice, but quite elegant: in the first step it 
replaces each pair of a bits with a 2-bit value indicating the count of those bits; in the second step it replaces each 
4-bit group with the count for that group; and so on, until the entire 32-bit value is replaced by a count of bits.

There are a few mistakes that are very easy to make when performing bit manipulations. Watch out for them in your code:

When executing a shift instruction a << b, the x86 architecture uses only the bottom 5 bits of b (6 for 64-bit integers). 
This means that shifting left (or right) by 32 does nothing, rather than clearing all the bits. 
This behavior is also specified by the Java and C# language standards; C++ says that shifting by at least the size of the 
value gives an undefined result.

A related point to the above is to be careful to use the appropriate type for constants to avoid overflow. 
For example, if you're using a Java long to represent a set, then you should write 1L << x rather than 1 << x.

In most languages, the & and | operators have lower precedence than comparison operators. 
That means that x & 3 == 1 is interpreted as x & (3 == 1), which is probably not what you want.

Where possible, use unsigned values, particularly if you want to use the top bit. C++ leaves the effect of 
right-shifting a negative value undefined, although in the environment used by TopCoder it has the same behavior 
as in Java and C# (namely, replicating the sign bit). Java only has signed types, but the Java-specific operator >>> will 
shift in zeros rather than replicating the sign bit.

The code examples above are for 32-bit integers. In most cases, the only change that needs to be made for 64-bit integers 
is to ensure that constants are forced to be the appropriate size (e.g., by writing 1 as 1L in Java or 1ULL in C++). 
The GCC builtin functions also require a ll suffix when using 64-bit integers (to indicate that they take a long long). For 
the portable alternatives to builtin functions, the patterns need to be extended to an extra iteration and 64-bit constants.
*/

inline int two(int n) { return 1 << n; }
inline int test(int n, int b) { return (n>>b)&1; }
inline void set_bit(int & n, int b) { n |= two(b); }
inline void unset_bit(int & n, int b) { n &= ~two(b); }
inline int last_bit(int n) { return n & (-n); }
inline int ones(int n) { int res = 0; while(n && ++res) n-=n&(-n); return res; }

#define LSOne(S) (S&(-S))

// iterate over all the subsets of the mask
for(int i = mask; i > 0; i = (i-1) & mask)

// Given a bitmask m, you want to efficiently iterate through all of its submasks, that is, masks s in which only bits that were included in mask m are set.

//Consider the implementation of this algorithm, based on tricks with bit operations:

int s = m;
while (s > 0) {
 ... you can use s ...
 s = (s-1) & m;
}

// or, using a more compact for statement:

for (int s=m; s; s=(s-1)&m)
 ... you can use s ...

// In both variants of the code, the submask equal to zero will not be processed. We can either process it outside the loop, or use a less elegant design, 

// for example:

for (int s=m; ; s=(s-1)&m) {
 ... you can use s ...
 if (s==0)  break;
}

// Let us examine why the above code visits all submasks of m, without repetition, and in descending order.

// Suppose we have a current bitmask s, and we want to move on to the next bitmask. By subtracting from the mask s one unit, 
// we will remove the rightmost set bit and all bits to the right of it will become 1. 
// Then we remove all the "extra" one bits that are not included in the mask m and therefore can't be a part of a submask. 
// We do this removal by using the bitwise operation (s-1) & m. As a result, we "cut" mask s−1 to determine the highest value that it can take, that is, 
// the next submask after s in descending order.

// Thus, this algorithm generates all submasks of this mask in descending order, performing only two operations per iteration.
