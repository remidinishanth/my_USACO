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

### Play convention

* An important class of games consists of those between two players in which there are only two possible outcomes: victory and loss. If the winner is the last player who is able to make a legal move, the game is said to follow the normal play convention. Otherwise, it is said to follow the misère play convention.

If, in addition to being deterministic, impartial, and guaranteed to end in a finite number of moves, a game is also normal play, it can be analyzed using the **Sprague-Grundy theorem**. We shall denote such games as Nim-like.

source: http://wcipeg.com/wiki/Game_theory

## N-positions and P-positions

In a two-player, deterministic(no chance moves), impartial game which is guaranteed to end(win-or-lose outcome) in a finite number of moves, an N-position is a configuration such that the **n**ext player to make a move can force victory, and a P-position is a configuration such that the **p**revious player who moved can force victory.

In a normal-play game, a configuration in which no further moves are possible is a P-position, since the player who is supposed to move next cannot do so and loses; in a misère-play game, it is an N-position, since the player who moved last made the last move and hence lost.

Consider a configuration C of such a game and the configurations C_1, C_2, C_3, ... reachable from it. 
* If at least one of C_1, C_2, C_3, ... is a P-position, then the player presented with configuration C wants to make the move that results in that configuration, so that he or she becomes the previous player when the next player is to move --- guaranteeing victory. This makes C a N-position. 
* If all of C_1, C_2, C_3, ... are N-positions, then no matter what move the current player makes, the next player can force victory, making C a P-position. 

In summary,
* If all positions reachable in one move from position C are N-positions, then C is a P-position, and the current player does not have a winning strategy.
* Otherwise (at least one P-position is reachable from C) C is an N-position, and a winning strategy necessarily entails leaving behind one of these P-positions for the next player.

The problem [Nukit](https://wcipeg.com/problem/ccc08j5) from the 2008 Canadian Computing Competition describes a game which is clearly two-player, deterministic, impartial, and guaranteed to end in a finite number of moves. Because of these properties we may analyze it with N-positions and P-positions.

### Basic problem 
A simple example is the following game, played by two players who take turns moving. At the beginning there are `n` coins. When it is a player’s turn he can take away `1`, `3` or `4` coins. The player who takes the last one away is declared the winner (in other words, the player who can not make a move is the loser). The question is: For what `n` will the first player win if they both play optimally?

Positions have the following properties:
* All terminal positions are losing.
* If a player is able to move to a losing position then he is in a winning position.
* If a player is able to move only to the winning positions then he is in a losing position.

These properties could be used to create a simple recursive algorithm WL-Algorithm:

```cpp
boolean isWinning(position pos) {
    moves[] = possible positions to which I can move from the position pos;
    for (all x in moves)
        if (!isWinning(x)) return true;
    return false;
}
```

It can be seen that whether a position is winning or losing depends only on the last `k` positions, where `k` is the maximum number of coins we can take away. While there are only `2^k` possible values for the sequences of the length `k`, our sequence will become periodic. You can use this observation to solve [SRM 330: LongLongNim](https://community.topcoder.com/stat?c=problem_statement&pm=6856)

### THE GAME OF NIM

The rules of the game are as follows:

* The game board consists of one or more piles of coins or sticks.
* On a player's turn, he or she chooses one non-empty pile and removes one or more sticks from it.
* The first player who cannot make a move loses. (That is, the player who takes the last stick wins.)

Suppose that there are three heaps with `3`, `4` and `5` coins respectively. Here is how game could develop:
![](images/nim_game.png)

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
