#pragma once

#include "Piece.h"

/*
  Implements Piece.
  Standard chess Bishop logic.
*/
class Bishop : public Piece {

public:
	Bishop(const char t) : Piece(t) {};

protected:
	std::vector<coords> getPossibleMoves(coords pos, GameManager& manager) const override;

private:
	static bool m_isRegistered;
};