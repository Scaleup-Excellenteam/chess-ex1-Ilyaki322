#pragma once
#include "Piece/Pawn.h"
#include "Piece/PieceFactory.h"
#include "GameManager.h"

/*
* @param pos - coordinates of the pawn.
* @param manager - referance to the GameManager.
* @return a vector of all possible moves from current pos for a standard pawn.
*/
std::vector<coords> Pawn::getPossibleMoves(coords pos, GameManager& manager) const
{
	std::vector<coords> available;
	int direction = m_isWhite ? 1 : -1;

	coords move = std::pair<int, int>(pos.first + direction, pos.second - 1);
	coords move2 = std::pair<int, int>(pos.first + direction, pos.second);
	coords move3 = std::pair<int, int>(pos.first + direction, pos.second + 1);
	coords move4 = std::pair<int, int>(pos.first + (2*direction), pos.second);

	if (checkTile(move, manager, true)) available.push_back(move);
	if (checkTile(move2, manager, false)) available.push_back(move2);
	if (checkTile(move3, manager, true)) available.push_back(move3);
	if (!didMove() && checkTile(move2, manager, false) && checkTile(move4, manager, false)) available.push_back(move4);

	return available;
}

/*
* @param tile - coordinates of the position to check.
* @param manager - referance to the GameManager.
* @param eatOnly - pawn moves forward and eats to sides, flag to know what to check.
* @return True if the pawn can move to the given tile.
*/
bool Pawn::checkTile(coords tile, GameManager& manager, bool eatOnly) const
{
	if (tile.first < 0 || tile.first > 7 || tile.second < 0 || tile.second > 7) return false;

	auto board = manager.getBoard();
	if ((board[tile.first][tile.second] == nullptr) && !eatOnly) return true;
	if (board[tile.first][tile.second] == nullptr) return false;
	if ((!isSameSide(board[tile.first][tile.second]->getPiece())) && eatOnly) return true;

	return false;
}

/*
* Registers the pawn to the factory
*/
bool Pawn::m_isRegistered = PieceFactory::registerPiece('p', [](const char t) {
	return std::make_unique<Pawn>(t);
	});