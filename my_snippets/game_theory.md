## Game Theory

Formal study of mathematical games. The ultimate goal of game theory is usually to solve a game; that is, to determine the nature of an optimal strategy for each player, and the outcome of such a strategy.

### State
* The state, position, or configuration of a game, loosely put, consists of exactly that information which determines the valid moves that can be made in the future and is itself modified when moves take place.

### Determinism
* A deterministic game is one in which the decisions of the players, reflected in the moves they make, are sufficient to determine the game's outcome. The opposite is an indeterministic game. More simply, "games of chance" are nondeterministic, whereas pure strategy games with no element of chance are deterministic. Chess, for example, is a deterministic game, whereas backgammon(involves roll of two dice) is not. 
* In a deterministic game, the state, taken together with the players' strategies, is sufficient and necessary to determine the game's outcome. In a nondeterministic game, the same combination is sufficient and necessary to determine the probabilities of the possible outcomes of the game.

### Availability of information
* When all players know the entire state of a game at any given time, the game is said to be perfect information. Perfect information games include chess, Go, and tic-tac-toe. In particular, games which have winning strategies for one of the players tend to be perfect-information. Imperfect information games include most card games, as each player usually hides cards from opponents.

### Partiality

* An impartial game is one which satisfies two conditions:
  * The valid moves from a given position depend only upon the position itself and not upon which player is to move next.
  * The outcome of the game is symmetric with respect to the players.
* Most games fail the first condition. Chess, for example, fails the first, since we must know if the player moving next is player 1 or player 2 to determine whether that player is to move a white piece or a black piece.
* Nim is a archetype for the impartial game; pieces are shared between the two players and each has the same goal.

## Play convention

* An important class of games consists of those between two players in which there are only two possible outcomes: victory and loss. If the winner is the last player who is able to make a legal move, the game is said to follow the normal play convention. Otherwise, it is said to follow the misère play convention.

## Grundy numbers

TODO: https://atcoder.jp/contests/abc206/tasks/abc206_f

#### Problem: https://atcoder.jp/contests/abc195/tasks/abc195_e

**Solution:** 

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
