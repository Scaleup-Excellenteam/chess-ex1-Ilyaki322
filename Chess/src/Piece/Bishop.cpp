#pragma once
#include "Piece/Bishop.h"
#include "Piece/PieceFactory.h"
#include "GameManager.h"

Bishop::Bishop(const char t, coords pos) : Piece(t, pos) {}

std::vector<coords> Bishop::getPossibleMoves(coords pos, GameManager& manager) const
{
	std::vector<coords> available;

	getSlidingMoves(available, manager, std::pair<int, int>(1, 1), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(-1, -1), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(-1, 1), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(1, -1), pos);

	return available;
}

bool Bishop::m_isRegistered = PieceFactory::registerPiece('b', [](const char t, std::pair<int, int> pos) {
	return std::make_unique<Bishop>(t, pos);
	});