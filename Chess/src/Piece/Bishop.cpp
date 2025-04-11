#pragma once
#include "Piece/Bishop.h"
#include "Piece/PieceFactory.h"
#include "GameManager.h"

/*
* @param pos - coordinates of the bishop.
* @param manager - referance to the GameManager.
* @return a vector of all possible moves from current pos for a standard bishop.
*/
std::vector<coords> Bishop::getPossibleMoves(coords pos, GameManager& manager) const
{
	std::vector<coords> available;

	getSlidingMoves(available, manager, std::pair<int, int>(1, 1), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(-1, -1), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(-1, 1), pos);
	getSlidingMoves(available, manager, std::pair<int, int>(1, -1), pos);

	return available;
}

/*
* Registers the bishop to the factory
*/
bool Bishop::m_isRegistered = PieceFactory::registerPiece('b', [](const char t) {
	return std::make_unique<Bishop>(t);
	});