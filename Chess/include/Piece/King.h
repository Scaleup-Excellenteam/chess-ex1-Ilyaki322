#pragma once
#include "Piece/Piece.h"

class GameManager;

class King : public Piece {

public:
	King(const char t, coords pos);

protected:
	std::vector<coords> getPossibleMoves(coords pos, GameManager& manager) const override;

private:
	bool checkTile(coords tile, GameManager& manager) const;
	static bool m_isRegistered;
};