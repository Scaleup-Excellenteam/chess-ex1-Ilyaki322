#pragma once
#include "Piece/Queen.h"
#include "Piece/PieceFactory.h"
#include "GameManager.h"

Queen::Queen(const char t, coords pos) : Piece(t, pos) {}

std::vector<coords> Queen::getPossibleMoves(coords pos, GameManager& manager) const
{
	std::vector<coords> available;

	getSlidingMoves(available, manager, std::pair<int, int>(1, 1), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(-1, -1), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(-1, 1), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(1, -1), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(0, 1), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(1, 0), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(-1, 0), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(0, -1), pos);

	return available;
}

bool Queen::m_isRegistered = PieceFactory::registerPiece('q', [](const char t, std::pair<int, int> pos) {
	return std::make_unique<Queen>(t, pos);
	});