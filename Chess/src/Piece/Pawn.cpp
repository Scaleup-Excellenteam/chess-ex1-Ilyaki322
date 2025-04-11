#pragma once
#include "Piece/Pawn.h"
#include "Piece/PieceFactory.h"
#include "GameManager.h"

Pawn::Pawn(const char t, coords pos) : Piece(t, pos) {}

std::vector<coords> Pawn::getPossibleMoves(coords pos, GameManager& manager) const
{
	std::vector<coords> available;
	int direction = m_isWhite ? 1 : -1;

	coords move = std::pair<int, int>(pos.first + direction, pos.second - 1);
	coords move2 = std::pair<int, int>(pos.first + direction, pos.second);
	coords move3 = std::pair<int, int>(pos.first + direction, pos.second + 1);

	if (checkTile(move, manager, true)) available.push_back(move);
	if (checkTile(move2, manager, false)) available.push_back(move2);
	if (checkTile(move3, manager, true)) available.push_back(move3);
	// check double forward

	return available;
}

bool Pawn::checkTile(coords tile, GameManager& manager, bool eatOnly) const
{
	if (tile.first < 0 || tile.first > 7 || tile.second < 0 || tile.second > 7) return false;

	auto board = manager.getBoard();
	if ((board[tile.first][tile.second] == nullptr) && !eatOnly) return true;
	if (board[tile.first][tile.second] == nullptr) return false;
	if ((!isSameSide(board[tile.first][tile.second]->getPiece())) && eatOnly) return true;

	return false;
}

bool Pawn::m_isRegistered = PieceFactory::registerPiece('p', [](const char t, std::pair<int, int> pos) {
	return std::make_unique<Pawn>(t, pos);
	});