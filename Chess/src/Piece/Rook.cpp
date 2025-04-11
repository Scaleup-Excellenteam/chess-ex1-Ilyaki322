#pragma once
#include "Piece/Rook.h"
#include "Piece/PieceFactory.h"
#include "GameManager.h"

/*
* @param pos - coordinates of the rook.
* @param manager - referance to the GameManager.
* @return a vector of all possible moves from current pos for a standard rook.
*/
std::vector<coords> Rook::getPossibleMoves(coords pos, GameManager& manager) const
{
	std::vector<coords> available;

	getSlidingMoves(available, manager, std::pair<int, int>(0, 1), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(1, 0), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(-1, 0), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(0, -1), pos);

	return available;
}

/*
* Registers the rook to the factory
*/
bool Rook::m_isRegistered = PieceFactory::registerPiece('r', [](const char t) {
	return std::make_unique<Rook>(t);
	});