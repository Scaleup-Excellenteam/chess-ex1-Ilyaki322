#pragma once

#include "Piece.h"

class Pawn : public Piece {

public:
	Pawn(const char t, coords pos);

protected:
	std::vector<coords> getPossibleMoves(coords pos, GameManager& manager) const override;

private:
	bool checkTile(coords tile, GameManager& manager, bool eatOnly) const;

	static bool m_isRegistered;
};