#pragma once
#include "Piece/Piece.h"
#include "GameManager.h"

/*
* Calculates all 'sliding' moves in a given direction.
* A sliding move is a move that a piece can move forward untill it hits a piece or the board bound
* @param availTargets - Referance to the vector to store possible moves.
* @param manager - Referance to the GameManager.
* @param direction - The Direction of the silde.
* @param start - the position of the sliding piece.
* @return A vector of possible moves from start in the give direction.
*/
void Piece::getSlidingMoves(std::vector<coords>& availTargets, GameManager& manager, coords directon, coords start) const
{
	auto& board = manager.getBoard();
	coords temp = start;
	temp.first += directon.first;
	temp.second += directon.second;
	while (temp.first >= 0 && temp.first < BOARD_SIZE && temp.second >= 0 && temp.second < BOARD_SIZE) {

		if (board[temp.first][temp.second] == nullptr) {
			availTargets.push_back(temp);
		}
		else if (!isSameSide(board[temp.first][temp.second]->getPiece())) {
			availTargets.push_back(temp);
			return;
		}
		else return;

		temp.first += directon.first;
		temp.second += directon.second;
	}
}

/*
* Checks if the coords vector contains a coord
* @param vec - Vector holding the coords.
* @param c - the coord to check.
* @return true if the vector contains the coord.
*/
bool Piece::containCoords(std::vector<coords> vec, coords c) const
{
	for (const auto& i : vec) {
		if (i == c) return true;
	}

	return false;
}

/*
* Checks if this is on the same team as other
* @param other - the char of the piece to check
* @return True if the pieces are on the same team.
*/
bool Piece::isSameSide(const char other) const
{
	return (m_isWhite && std::isupper(other)) || (!m_isWhite && !std::isupper(other));
}

/*
* Checks if a given move is legal.
* @param pos - the source coordination of the move.
* @param target - the target coordination of the move.
* @param manager - A referance to the GameManager.
* @return A corresponding ResponseCode for the graphics engine.
*/
int Piece::isMoveValid(coords pos, coords target, GameManager& manager) const
{
	auto board = manager.getBoard();
	if (board[target.first][target.second] != nullptr) {
		auto targetPiece = board[target.first][target.second]->getPiece();
		if (isSameSide(targetPiece)) return 13;
	}

	if (containCoords(getPossibleMoves(pos, manager), target)) return -1;

	return RC_ILLEGAL;
}

/*
* Checks if the piece is attacking the enemy king.
* @param pos - position of the piece.
* @param enemyKing - coordinates of the enemy king
* @param manager - A referance to the GameManager.
* @return true if the piece is attacking the enemy king.
*/
bool Piece::isAttackingKing(coords pos, coords enemyKing, GameManager& manager) const
{
	return (containCoords(getPossibleMoves(pos, manager), enemyKing));
}
