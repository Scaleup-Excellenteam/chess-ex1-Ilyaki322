#pragma once
#include "Piece/Piece.h"
#include "GameManager.h"

void Piece::getSlidingMoves(std::vector<coords>& availTargets, GameManager& manager, coords directon, coords start) const
{
	auto& board = manager.getBoard();
	coords temp = start;
	temp.first += directon.first;
	temp.second += directon.second;
	while (temp.first >= 0 && temp.first < BOARD_SIZE && temp.second >= 0 && temp.second < BOARD_SIZE) {

		if (board[temp.first][temp.second] == nullptr) {
			availTargets.push_back(temp);
		}
		else if (!isSameSide(board[temp.first][temp.second]->getPiece())) {
			availTargets.push_back(temp);
			return;
		}
		else return;

		temp.first += directon.first;
		temp.second += directon.second;
	}
}

bool Piece::containCoords(std::vector<coords> vec, coords c) const
{
	for (const auto& i : vec) {
		if (i == c) return true;
	}

	return false;
}

bool Piece::isSameSide(const char other) const
{
	return (m_isWhite && std::isupper(other)) || (!m_isWhite && !std::isupper(other));
}

int Piece::isMoveValid(coords pos, coords target, GameManager& manager) const
{
	auto board = manager.getBoard();
	if (board[target.first][target.second] != nullptr) {
		auto targetPiece = board[target.first][target.second]->getPiece();
		if (isSameSide(targetPiece)) return 13;
	}

	if (containCoords(getPossibleMoves(pos, manager), target)) return -1;

	return RC_ILLEGAL;
}

bool Piece::isAttackingKing(coords pos, coords enemyKing, GameManager& manager) const
{
	return (containCoords(getPossibleMoves(pos, manager), enemyKing));
}
