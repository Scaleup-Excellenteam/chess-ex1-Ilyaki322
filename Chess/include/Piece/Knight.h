#pragma once

#include "Piece.h"

/*
  Implements Piece.
  Standard chess Knight logic.
*/
class Knight : public Piece {

public:
	Knight(const char t) : Piece(t) {};

protected:
	std::vector<coords> getPossibleMoves(coords pos, GameManager& manager) const override;

private:
	bool checkTile(coords tile, GameManager& manager) const;
	static bool m_isRegistered;
};