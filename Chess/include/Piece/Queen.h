#pragma once

#include "Piece.h"

/*
  Implements Piece.
  Standard chess Queen logic.
*/
class Queen : public Piece {

public:
	Queen(const char t) : Piece(t) {};

protected:
	std::vector<coords> getPossibleMoves(coords pos, GameManager& manager) const override;

private:
	static bool m_isRegistered;
};