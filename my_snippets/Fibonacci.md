# Fibonacci

Leonardo Fibonacci’s numbers are defined as fib(0) = 0, fib(1) = 1, and for n ≥ 2, fib(n) =
fib(n − 1) + fib(n − 2).

Fibonacci numbers have many interesting properties. One of them is the **Zeckendorf ’s
theorem**: Every positive integer can be written in a unique way as a sum of one or more
distinct Fibonacci numbers such that the sum does not include any two consecutive Fibonacci
numbers. For any given positive integer, a representation that satisfies Zeckendorf’s theorem
can be found by using a Greedy algorithm: Choose the largest possible Fibonacci number at
each step. For example: 100 = 89 + 8 + 3; 77 = 55 + 21 + 1, 18 = 13 + 5, etc.

Another property is the **Pisano Period** where the last one/last two/last three/last four
digit(s) of a Fibonacci number repeats with a period of 60/300/1500/15000, respectively.

## Linear Homogeneous Recurrence Relations

Theorem: Let c<sub>1</sub> and c<sub>2</sub> be real numbers. Suppose that r<sup>2</sup> − c<sub>1</sub>r − c<sub>2</sub> = 0 has two distinct roots r<sub>1</sub>
and r<sub>2</sub>. Then the sequence {a<sub>n</sub>} is a solution of the recurrence relation a<sub>n</sub> = c<sub>1</sub>a<sub>n-1</sub> + c<sub>2</sub>a<sub>n-2</sub> if and only if a<sub>n</sub> = α<sub>1</sub>r<sub>1</sub>
<sup>n</sup> + α<sub>2</sub>r<sub>2</sub><sup>n</sup>
 for n = 0, 1, 2,..., where α<sub>1</sub> and α<sub>2</sub> are constants.

Proof:
Distinct roots are required because, say a<sub>0</sub> = C<sub>0</sub> and a<sub>1</sub> = C<sub>1</sub>, then

a<sub>0</sub> = C<sub>0</sub> = α<sub>1</sub> + α<sub>2</sub> and a<sub>1</sub> = C<sub>1</sub> = α<sub>1</sub>r<sub>1</sub> + α<sub>2</sub>r<sub>2</sub> which implies that α<sub>1</sub> = (C<sub>1</sub> - C<sub>0</sub>r<sub>2</sub>)/(r<sub>1</sub> - r<sub>2</sub>), this requires that r1 and r2 are different.

Above theorem does not apply when there is one characteristic root of multiplicity two. If this happens, then a<sub>n</sub> = nr<sub>0</sub><sup>n</sup>
 is another solution of the recurrence relation when r<sub>0</sub> is a root of multiplicity two of the characteristic equation.

## Binet's formula

F(n+2) = F(n+1) + F(n)

If we try to find a geomtric sequences with F(n) = k<sup>n</sup>, then

k<sup>n+2</sup> = k<sup>n+1</sup> + k<sup>n</sup>

k<sup>2</sup> = k + 1

which implies

![fibonacci](images/fibonacci_1.png)

If we plug in two different values of n = 0 and n =1, and solve for A and B, we get:

![fibonacci](images/fibonacci_2.png)

((1 + √5)/2) ≈ 1.618 Golden ratio

### Fibonacci number system

https://www.johndcook.com/blog/2015/05/17/fibonacci-number-system/
