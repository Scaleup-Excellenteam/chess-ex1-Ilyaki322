#pragma once
#include "GameManager.h"

typedef std::pair<int, int> coords;

class MoveAnalyzer {
public:
	MoveAnalyzer(GameManager& manager) : m_manager(manager), m_depth(2) {}

	std::pair<coords, coords> findBestMove(bool isWhite);

private:
	int evaluateBoard();
	int minmax(int depth, int alpha, int beta, bool maximizingPlayer);
	bool isGameOver(std::vector<std::vector<std::pair<coords, coords>>>& allMoves);

	GameManager& m_manager;
	const int m_depth;
};