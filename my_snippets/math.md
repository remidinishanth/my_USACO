# Maths

## Well Ordering Principle

Every nonempty set of positive integers contains a smallest member.

## Division Algorithm

Let a and b be integers with b > 0. Then there exist unique integers q and r with the property that a = b*q + r, where 0 ≤ r < b.

## GCD

BÉZOUT’S THEOREM:  For any nonzero integers a and b, there exist integers s and t such that `gcd(a, b) = as + bt`. Moreover, gcd(a, b) is the smallest positive integer of the form as + bt.

If a and b are relatively prime, then there exist integers s and t such that as + bt = 1.

Euclid's lemma:
If p is a prime that divides ab, then p divides a or p divides b.

Proof: Suppose p is a prime that divides ab but does not divide a. We must show that p divides b. Since p does not divide a, there are integers s and t such that as + pt = 1. Then abs + pbt = b, and since p divides the left-hand side of this equation, p also divides b.

## Fermat's little theorem

FERMAT’S LITTLE THEOREM: If p is prime and a is an integer not divisible by p,
then
a<sup>p−1</sup> ≡ 1 (mod p).

Furthermore, for every integer a we have
a<sup>p</sup> ≡ a (mod p).

The modular multiplicative inverse 𝑥 of 𝑎 modulo 𝑝 is defined as

```math
a . x ≡ 1 (mod p)
```

Here, I will replace 𝑥 with inv(𝑎), so we have

a . inv(a) ≡ 1 (mod 𝑝)

a ⋅ inv(a) ≡ a<sup>p−1</sup> (mod 𝑝)

inv(a) ≡ a<sup>p−2</sup> (mod p).

## The Euclidean Algorithm

Let a = bq + r, where a, b, q, and r are integers. Then gcd(a, b) = gcd(b, r).

Proof: Suppose that d divides both a and b. Then it follows that d also divides a − bq = r

Likewise, suppose that d divides both b and r. Then d also divides bq + r = a. Hence, any
common divisor of b and r is also a common divisor of a and b.
Consequently, gcd(a, b) = gcd(b, r).

## Important Modulo property

Let r = x mod p

So, x = k*p + r

If k = 0, x mod p remains to be x.

If k ≠ 0, x mod p = r = 2r/2 < (p+r)/2 ≤ (k*p+r)/2 = x/2

We realize every time a change happening on x, x will be reduced by at least a half.

So if a ≥ b then a % b < a/2

## Seive of Eratosthenes

If n is a composite integer, then n has a prime divisor less than or equal to √n

Goldbach’s Conjecture In 1742, Christian Goldbach, in a letter to Leonhard Euler, conjectured that every odd integer n, n > 5, is the sum of three primes. Euler replied that this conjecture
is equivalent to the conjecture that every even integer n, n > 2, is the sum of two primes (see
Exercise 21 in the Supplementary Exercises). The conjecture that every even integer n, n > 2, is
the sum of two primes is now called Goldbach’s conjecture

## Binomial Coefficients

<sup>n</sup>𝐶<sub>𝑘</sub> means how many ways you can choose 𝑘 items from an array of 𝑛 items, also denoted as (<sup>n</sup><sub>k</sub>). This is also known as binomial coefficients. The formula for combination is

<sup>n</sup>𝐶<sub>𝑘</sub> = n!/k!(n-k)!

Sometimes, the denominator 𝑘!(𝑛−𝑘)! is very large, but we can't modulo it since modulo operations can't be done independently on the denominator. 

C(n, 0) = C(n, n) = 1 // base cases.
C(n, k) = C(n − 1, k − 1) + C(n − 1, k) // take or ignore an item, n > k > 0.

## Modular multiplicative inverse

Getting back to the formula for combination, we can rearrange so that

<sup>n</sup>𝐶<sub>𝑘</sub> = 𝑛!⋅ 1/𝑘!⋅ 1/(𝑛−𝑘)!

Here, we can use inv(𝑎) as follows

<sup>n</sup>𝐶<sub>𝑘</sub> ≡ 𝑛! ⋅ inv(𝑘!) ⋅ inv((𝑛−𝑘)!) (mod 𝑝)

## Extended Euclid Algorithm

Standard euclid algorithm proceeds in the following way

![Extended Euclid](images/extended_euclid_1.svg)

The extended Euclidean algorithm proceeds similarly, but adds two other sequences, as follows

![Extended Euclid](images/extended_euclid_2.svg)

The computation stops when r<sub>k+1</sub> = 0, which implies
* r<sub>k</sub> is gcd of a = r<sub>0</sub> and b = r<sub>1</sub>
* Bezout coefficients are s<sub>k</sub> and t<sub>k</sub>, that is gcd(a, b) = r<sub>k</sub> = as<sub>k</sub> + bt<sub>k</sub>

Proof:

As r<sub>i+1</sub> = r<sub>i-1</sub> - r<sub>i</sub>q<sub>i</sub>, the gcd is same for (r<sub>i-1</sub>, r<sub>i</sub>) and (r<sub>i</sub>, r<sub>i+1</sub>).

As a = r<sub>0</sub> and b = r<sub>1</sub>, we have as<sub>i</sub> + bt<sub>i</sub> = r<sub>i</sub> for i = 0 and 1. The relation follows by induction for all i > 1:

![Extended Euclid](images/extended_euclid_3.svg)

Alternate Proof:

As seen above, x and y are results for inputs a and b,
   a.x + b.y = gcd                      ----(1)  

And x1 and y1 are results for inputs b%a and a
   (b%a).x1 + a.y1 = gcd

When we put b%a = (b - (⌊b/a⌋).a) in above, 
we get following. Note that ⌊b/a⌋ is floor(b/a)

   (b - (⌊b/a⌋).a).x1 + a.y1  = gcd

Above equation can also be written as below
   b.x1 + a.(y1 - (⌊b/a⌋).x1) = gcd      ---(2)

After comparing coefficients of 'a' and 'b' in (1) and (2), we get following
   x = y1 - ⌊b/a⌋ * x1
   y = x1

The extended Euclidean algorithm is particularly useful when a and b are coprime (or gcd is 1). Since x is the modular multiplicative inverse of “a modulo b”, and y is the modular multiplicative inverse of “b modulo a”.

## Modulo inverse for every modulo m

m mod i = m − ⌊m / i⌋ ⋅ i

Taking both sides modulo m yields:

m mod i ≡ − ⌊m / i⌋ ⋅ i (mod m)

Multiply both sides by i<sup>−1</sup>⋅(m mod i)<sup>−1</sup> yields

(m mod i)⋅i<sup>−1</sup>⋅(m mod i)<sup>−1</sup> ≡ −⌊m / i⌋⋅i⋅i<sup>−1</sup>⋅(m mod i)<sup>−1</sup> mod m,

which simplifies to:

i<sup>−1</sup> ≡ −⌊m / i⌋⋅(m mod i)<sup>−1</sup> mod m

We denote by inv[i] the modular inverse of i. Then for i>1 the following equation is valid:

inv[i]=−⌊m / i⌋ ⋅ inv[m mod i] mod m


## Bit operations

XOR any numerical input

```math
   a + b - ab(1 + a + b - ab)
```

XOR binary input

```math
   a + b - 2ab or (a-b)²
```

### Derivation

Basic Logical Operators

```math
   NOT = (1-x)

   AND = x*y
```

From those operators we can get...

```math
   OR = (1-(1-a)(1-b)) = a + b - ab
```

Note: If a and b are mutually exclusive then their and condition will always be zero - from a Venn diagram perspective, this means there is no overlap. In that case, we could write `OR = a + b`, since `a*b = 0` for all values of a & b.

2-Factor XOR

```math
Defining XOR as (a OR B) AND (NOT (a AND b)):

(a OR B) --> (a + b - ab)

(NOT (a AND b)) --> (1 - ab)
```

AND these conditions together to get...

```math
(a + b - ab)(1 - ab) = a + b - ab(1 + a + b - ab)
```

### Addition

```math
a + b = ((a and b) << 1) + (a xor b)
```
