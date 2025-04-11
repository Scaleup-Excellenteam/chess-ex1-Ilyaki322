#pragma once

#include "Piece.h"

class Queen : public Piece {

public:
	Queen(const char t, coords pos);

protected:
	std::vector<coords> getPossibleMoves(coords pos, GameManager& manager) const override;

private:
	static bool m_isRegistered;
};