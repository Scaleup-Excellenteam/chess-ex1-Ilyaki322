#pragma once
#include "Piece/Rook.h"
#include "Piece/PieceFactory.h"
#include "GameManager.h"

Rook::Rook(const char t, coords pos) : Piece(t, pos) {}

int Rook::isMoveValid(coords pos, coords target, GameManager& manager) const
{
	auto board = manager.getBoard();
	if (board[target.second][target.first] != nullptr) {
		auto targetPiece = board[target.second][target.first]->getPiece();
		if (isSameSide(targetPiece)) return 13;
	}
	
	if (containCoords(getPossibleMoves(pos, manager), target)) return -1;

	return 21;
}

bool Rook::isAttackingKing(coords pos, coords enemyKing, GameManager& manager) const
{
	return (containCoords(getPossibleMoves(pos, manager), enemyKing));
}

std::vector<coords> Rook::getPossibleMoves(coords pos, GameManager& manager) const
{
	std::vector<coords> available;

	straightLineCheck(available, manager, std::pair<int, int>(0, 1), pos);
	straightLineCheck(available, manager, std::pair<int, int>(1, 0), pos);
	straightLineCheck(available, manager, std::pair<int, int>(-1, 0), pos);
	straightLineCheck(available, manager, std::pair<int, int>(0, -1), pos);

	return available;
}

void Rook::straightLineCheck(std::vector<coords>& availTargets, GameManager& manager,
	coords directon, coords start) const
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

bool Rook::m_isRegistered = PieceFactory::registerPiece('r', [](const char t, std::pair<int, int> pos) {
	return std::make_unique<Rook>(t, pos);
	});