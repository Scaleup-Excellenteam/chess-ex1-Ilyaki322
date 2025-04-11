#pragma once

#include "Piece.h"

/*
  Implements Piece.
  Standard chess Rook logic.
*/
class Rook : public Piece 
{
public:
	Rook(const char t) : Piece(t) {};

protected:
	std::vector<coords> getPossibleMoves(coords pos, GameManager& manager) const override;

private:
	static bool m_isRegistered;
};