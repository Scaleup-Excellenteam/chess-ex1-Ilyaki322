#pragma once
#include "Piece/Piece.h"

class GameManager;

/*
  Implements Piece.
  Standard chess King logic.
  !!Currently does NOT support castling!!
*/
class King : public Piece {

public:
	King(const char t) : Piece(t) {};

protected:
	std::vector<coords> getPossibleMoves(coords pos, GameManager& manager) const override;

private:
	bool checkTile(coords tile, GameManager& manager) const;
	static bool m_isRegistered;
};