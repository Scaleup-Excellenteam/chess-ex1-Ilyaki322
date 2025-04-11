#pragma once
#include "Piece/Rook.h"
#include "Piece/PieceFactory.h"
#include "GameManager.h"

Rook::Rook(const char t, coords pos) : Piece(t, pos) {}

std::vector<coords> Rook::getPossibleMoves(coords pos, GameManager& manager) const
{
	std::vector<coords> available;

	getSlidingMoves(available, manager, std::pair<int, int>(0, 1), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(1, 0), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(-1, 0), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(0, -1), pos);

	return available;
}

bool Rook::m_isRegistered = PieceFactory::registerPiece('r', [](const char t, std::pair<int, int> pos) {
	return std::make_unique<Rook>(t, pos);
	});