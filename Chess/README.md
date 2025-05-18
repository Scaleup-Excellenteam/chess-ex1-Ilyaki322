
## EXCELLENTEAM_EX02 - MOVE RECOMMENDATION AND TEMPLATES

## Author: Ilya Kirshtein
## ID: 323299362
## Mail: ilyaki@edu.jmc.ac.il

## Files Added for EX2:

### BoardStack.h && BoardStack.cpp:
Acts as a move stack, pushes and pops moves.
used to be able to reverse a few moves and not only one as in ex1.


### MoveAnalyzer.h && MoveAnalyzer.cpp:
Using the minmax and alpha beta pruning to find the best move.


### PriorityQueue.h && PriorityQueue.cpp:
A templated priority queue as requested in the assignment.
inserts in O(n) and pops on O(1).
will keep objects up to m_size, and pop excess.

EmptyStructureException.h && NoKingsFoundException.h:
custom exceptions to handle trying to pop empty BoardStack / PriorityQueue
or trying to start a game with no kings.

## Minmax:
The minmax algorithm will get a board position, and recusivly play all possible moves,
and on those moves will apply minmax, up to depth.
for each move it will evaluate the board and return a value,
overall this will return a move that has the highest value.

The algorithm also uses alpha beta pruning:
minmax plays both black and white moves, so
it will 'cut' and stop the recursion if it finds moves that are better for the opponent,
it assumes the opponent will make the best move for them, and so we reduce the number
of positions we need to check.
for example: if we look at 3 different moves, and on the first the evaluation favours
the enemy, then if on the second move we find a lower evaluation, we will skip the entire recursion
of that move.

## Run time:
for each depth(d) level we check ALL possible moves(m)
if we assume checking a move is O(1) then we get O(d^m).
if not then given checking a move = O(t) then we get O(d^mt).
