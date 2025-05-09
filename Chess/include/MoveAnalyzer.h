#pragma once
#include "GameManager.h"

class MoveAnalyzer {
public:
	MoveAnalyzer(GameManager& manager) : m_manager(manager) {}

private:
	int evaluateBoard();

	GameManager& m_manager;
};