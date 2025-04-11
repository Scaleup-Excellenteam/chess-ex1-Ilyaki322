#pragma once

#include "Piece.h"

class Bishop : public Piece {

public:
	Bishop(const char t, coords pos);

protected:
	std::vector<coords> getPossibleMoves(coords pos, GameManager& manager) const override;

private:
	static bool m_isRegistered;
};