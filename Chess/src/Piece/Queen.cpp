#include "Piece/Queen.h"
#include "Piece/PieceFactory.h"
#include "GameManager.h"

/*
* @param pos - coordinates of the queen.
* @param manager - referance to the GameManager.
* @return a vector of all possible moves from current pos for a standard queen.
*/
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

/*
* Registers the queen to the factory
*/
bool Queen::m_isRegistered = PieceFactory::registerPiece('q', [](const char t) {
	return std::make_unique<Queen>(t);
	});