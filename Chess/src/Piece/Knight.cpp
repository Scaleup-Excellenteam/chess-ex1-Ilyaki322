#pragma once
#include "Piece/Knight.h"
#include "Piece/PieceFactory.h"
#include "GameManager.h"

Knight::Knight(const char t, coords pos) : Piece(t, pos) {}

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

bool Knight::checkTile(coords tile, GameManager& manager) const
{
	if (tile.first < 0 || tile.first > 7 || tile.second < 0 || tile.second > 7) return false;

	auto board = manager.getBoard();
	if (board[tile.second][tile.first] == nullptr) return true;
	if (!isSameSide(board[tile.second][tile.first]->getPiece())) return true;

	return false;
}

bool Knight::m_isRegistered = PieceFactory::registerPiece('n', [](const char t, std::pair<int, int> pos) {
	return std::make_unique<Knight>(t, pos);
	});