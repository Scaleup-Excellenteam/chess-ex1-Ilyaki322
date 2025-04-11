#pragma once
#include "Piece/Knight.h"
#include "Piece/PieceFactory.h"
#include "GameManager.h"

/*
* @param pos - coordinates of the knight.
* @param manager - referance to the GameManager.
* @return a vector of all possible moves from current pos for a standard knight.
*/
std::vector<coords> Knight::getPossibleMoves(coords pos, GameManager& manager) const
{
	std::vector<coords> available;

	coords move = std::pair<int, int>(pos.first - 2, pos.second - 1);
	if (checkTile(move, manager)) available.push_back(move);

	move = std::pair<int, int>(pos.first - 1, pos.second - 2);
	if (checkTile(move, manager)) available.push_back(move);

	move = std::pair<int, int>(pos.first + 1, pos.second - 2);
	if (checkTile(move, manager)) available.push_back(move);

	move = std::pair<int, int>(pos.first + 1, pos.second + 2);
	if (checkTile(move, manager)) available.push_back(move);

	move = std::pair<int, int>(pos.first - 1, pos.second + 2);
	if (checkTile(move, manager)) available.push_back(move);

	move = std::pair<int, int>(pos.first + 2, pos.second - 1);
	if (checkTile(move, manager)) available.push_back(move);

	move = std::pair<int, int>(pos.first + 2, pos.second + 1);
	if (checkTile(move, manager)) available.push_back(move);

	move = std::pair<int, int>(pos.first - 2, pos.second + 1);
	if (checkTile(move, manager)) available.push_back(move);

	return available;
}

/*
* @param tile - coordinates of the position to check.
* @param manager - referance to the GameManager.
* @return True if the knight can move to the given tile.
*/
bool Knight::checkTile(coords tile, GameManager& manager) const
{
	if (tile.first < 0 || tile.first > 7 || tile.second < 0 || tile.second > 7) return false;

	auto board = manager.getBoard();
	if (board[tile.first][tile.second] == nullptr) return true;
	if (!isSameSide(board[tile.first][tile.second]->getPiece())) return true;

	return false;
}

/*
* Registers the knight to the factory
*/
bool Knight::m_isRegistered = PieceFactory::registerPiece('n', [](const char t) {
	return std::make_unique<Knight>(t);
	});