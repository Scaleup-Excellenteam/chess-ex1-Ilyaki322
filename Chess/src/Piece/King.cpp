#pragma once
#include "Piece/King.h"
#include "Piece/PieceFactory.h"
#include "GameManager.h"

#include <iostream>
King::King(const char t, coords pos) : Piece(t, pos) {}

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

bool King::checkTile(coords tile, GameManager& manager) const
{
	if (tile.first < 0 || tile.first > 7 || tile.second < 0 || tile.second > 7) return false;

	auto board = manager.getBoard();
	if (board[tile.first][tile.second] == nullptr) return true;
	if (!isSameSide(board[tile.first][tile.second]->getPiece())) return true;

	return false;
}

bool King::m_isRegistered = PieceFactory::registerPiece('k', [](const char t, std::pair<int, int> pos) {
	return std::make_unique<King>(t, pos);
	});
