#pragma once

#include "Piece.h"

class Rook : public Piece {

public:
	Rook(const char t, coords pos);

protected:
	std::vector<coords> getPossibleMoves(coords pos, GameManager& manager) const override;

private:
	static bool m_isRegistered;
};