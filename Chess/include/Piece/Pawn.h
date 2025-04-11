#pragma once

#include "Piece.h"

/*
  Implements Piece.
  Standard chess Pawn logic.
  !!Currently does NOT support promotion and en-passant!!
*/
class Pawn : public Piece {

public:
	Pawn(const char t) : Piece(t) {};

protected:
	std::vector<coords> getPossibleMoves(coords pos, GameManager& manager) const override;

private:
	bool checkTile(coords tile, GameManager& manager, bool eatOnly) const;

	static bool m_isRegistered;
};