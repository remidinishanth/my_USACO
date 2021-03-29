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

## The Euclidean Algorithm

Let a = bq + r, where a, b, q, and r are integers. Then gcd(a, b) = gcd(b, r).

Proof: So suppose that d divides both a and b. Then it follows that d also divides a − bq = r

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
