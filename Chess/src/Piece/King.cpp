#pragma once
#include "Piece/King.h"
#include "Piece/PieceFactory.h"
#include "GameManager.h"

/*
* @param pos - coordinates of the king.
* @param manager - referance to the GameManager.
* @return a vector of all possible moves from current pos for a standard king.
*/
std::vector<coords> King::getPossibleMoves(coords pos, GameManager& manager) const
{
	std::vector<coords> moves;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (i == 0 && j == 0) continue;
			coords tile = std::pair<int, int>(pos.first + i, pos.second + j);
			if (checkTile(tile, manager)) {
				moves.push_back(tile);
			}
		}
	}
	return moves;
}

/*
* @param tile - coordinates of the position to check.
* @param manager - referance to the GameManager.
* @return True if the king can move to the given tile.
*/
bool King::checkTile(coords tile, GameManager& manager) const
{
	if (tile.first < 0 || tile.first > 7 || tile.second < 0 || tile.second > 7) return false;

	auto board = manager.getBoard();
	if (board[tile.first][tile.second] == nullptr) return true;
	if (!isSameSide(board[tile.first][tile.second]->getPiece())) return true;

	return false;
}

/*
* Registers the king to the factory
*/
bool King::m_isRegistered = PieceFactory::registerPiece('k', [](const char t) {
	return std::make_unique<King>(t);
	});
