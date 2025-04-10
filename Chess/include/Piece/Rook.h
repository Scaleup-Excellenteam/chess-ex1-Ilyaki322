#pragma once

#include "Piece.h"

class Rook : public Piece {
public:
	Rook(const char t, coords pos);

	int isMoveValid(coords pos, coords target, GameManager& manager) const override;
	bool isAttackingKing(coords pos, coords enemyKing, GameManager& manager) const override;

protected:
	std::vector<coords> getPossibleMoves(coords pos, GameManager& manager) const override;

private:
	void straightLineCheck(std::vector<coords>& availTargets, GameManager& manager,
		coords directon, coords start) const;

	static bool m_isRegistered;
};