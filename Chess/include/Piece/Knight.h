#pragma once

#include "Piece.h"

class Knight : public Piece {

public:
	Knight(const char t, coords pos);

protected:
	std::vector<coords> getPossibleMoves(coords pos, GameManager& manager) const override;

private:
	bool checkTile(coords tile, GameManager& manager) const;
	static bool m_isRegistered;
};