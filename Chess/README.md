//***********************************************
EXCELLENTEAM_EX01 - CHESS
//***********************************************

//***********************************************
Author: Ilya Kirshtein
ID: 323299362
//***********************************************

//***********************************************
Overview:
//***********************************************

A classic game of chess.

*CONTROLS*: keyboard controlled.
exit - to exit
chess commands looks like: @#@#
where @ is - a-h or A-H
      # is - 1-8
the first two symbols for which piece you want to move
the second two for where to move the piece to.

//***********************************************
Created Files:
//***********************************************

GameManager.h && GameManager.cpp:
Responsible for general game rules, overall player mistakes, such as wrong tile selection.
Or rules that apply to multiple pieces, such as check.
Contains the game 'board', location of the kings for convenience, and backup data to undo if necessary.

Piece.h && Piece.cpp:
Abstract base class for all the game pieces.
Inheriting classes have to implement getPossibleMoves 
that return a vector of moves the piece can do based on given pos.
Implements a variety of common logic for pieces, such as sliding move that the Rook, Queen, Bishop use,
Can check if a given piece is the same side as this and more.

PieceFactory.h && PieceFactory.cpp:
Standard factory for piece creation.

Pawn, Knight, Bishop, Rook, Queen, King.h && .cpp:
All those classes inherting from Piece.
They represent the logic for all the standard chess pieces.

//***********************************************
Remarks for the examiner:
//***********************************************

checkmate is not supported by the visual engine?
promotion is not supported by my code nor the visual engine.
special moves such as castling or en-passant are not supported.

//***********************************************
Known bugs:
//***********************************************

None