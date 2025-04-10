#pragma once
#include "GameManager.h"
#include "Piece/PieceFactory.h"

#include <iostream>

GameManager::GameManager(string board)
	: m_whitePlayerTurn(true), m_defeatedLastTurn(nullptr), 
	m_srcLastTurn(std::pair<int,int>(-1, -1)), m_targetLastTurn(std::pair<int, int>(-1, -1)),
	m_whiteKing(std::pair<int, int>(-1, -1)), m_blackKing(std::pair<int, int>(-1, -1))
{
	PieceFactory pieceFactory;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			char currSymbol = board[j + i * BOARD_SIZE];
			if (currSymbol == '#') m_board[j][i] = nullptr;
			if (currSymbol == 'K') m_whiteKing = std::pair<int, int>(j, i);
			if (currSymbol == 'k') m_blackKing = std::pair<int, int>(j, i);
			else m_board[j][i] = pieceFactory.buildPiece(currSymbol, std::pair<int, int>(j, i));
		}
	}
}

int GameManager::evalPlayerMove(string playerInput)
{
	std::pair<char, char> src(playerInput[0], playerInput[1]);
	std::pair<char, char> target(playerInput[2], playerInput[3]);

	int turn = isPlayerTurn(src);
	if (turn != -1) return turn;

	coords srcInt = inputToCoords(std::pair<char, char>(playerInput[0], playerInput[1]));
	coords targetInt = inputToCoords(std::pair<char, char>(playerInput[2], playerInput[3]));

	int pieceLogic = evalPiece(srcInt, targetInt);
	if (pieceLogic != -1) return pieceLogic;

	playMove(srcInt, targetInt);

	return checkCheck();
}

const std::unique_ptr<Piece>(&GameManager::getBoard() const)[BOARD_SIZE][BOARD_SIZE]
{
	return m_board;
}

std::pair<int, int> GameManager::inputToCoords(std::pair<char, char> input)
{
	int col = input.first - 'a';
	int row = (input.second - '0') - 1;

	return std::pair<int, int>(col, row);
}

int GameManager::isPlayerTurn(std::pair<char, char> input)
{
	auto pos = inputToCoords(input);

	if (m_board[pos.second][pos.first] == nullptr) return 11;

	char piece = m_board[pos.second][pos.first]->getPiece();

	if ((std::isupper(piece) && m_whitePlayerTurn) ||
		 (!std::isupper(piece) && !m_whitePlayerTurn)) return -1;

	return 12;
}

int GameManager::evalPiece(coords src, coords target)
{
	return m_board[src.second][src.first]->isMoveValid(src, target, *this);
}

void GameManager::playMove(coords src, coords target)
{
	if (m_board[target.second][target.first] != nullptr)
		m_defeatedLastTurn = std::move(m_board[target.second][target.first]);
	else m_defeatedLastTurn = nullptr;

	m_board[target.second][target.first] = std::move(m_board[src.second][src.first]);
	m_board[src.second][src.first] = nullptr;

	if (m_whiteKing == src) m_whiteKing = target;
	if (m_blackKing == src) m_blackKing = target;
	m_srcLastTurn = src;
	m_targetLastTurn = target;
}

void GameManager::undoLastMove()
{
	m_board[m_srcLastTurn.second][m_srcLastTurn.first] = std::move(m_board[m_targetLastTurn.second][m_targetLastTurn.first]);

	if (m_whiteKing == m_targetLastTurn) m_whiteKing = m_srcLastTurn;
	if (m_blackKing == m_targetLastTurn) m_blackKing = m_srcLastTurn;

	if (m_defeatedLastTurn != nullptr) {
		m_board[m_targetLastTurn.second][m_targetLastTurn.first] = std::move(m_defeatedLastTurn);
	}
}

int GameManager::checkCheck()
{
	debugPrint();
	if ((m_whitePlayerTurn && isKingUnderAttack(m_whiteKing, true))) //||
		//(!m_whitePlayerTurn && isKingUnderAttack(m_blackKing, false))) {
	{
		undoLastMove();
		std::cout << "\n";
		debugPrint();
		return 31;
	}

	if ((m_whitePlayerTurn && isKingUnderAttack(m_blackKing, false)) ||
		(!m_whitePlayerTurn && isKingUnderAttack(m_whiteKing, true))) {
		m_whitePlayerTurn = !m_whitePlayerTurn;
		return 41;
	}

	m_whitePlayerTurn = !m_whitePlayerTurn;
	return 42;
}

bool GameManager::isKingUnderAttack(coords kingPos, bool isWhite)
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (m_board[j][i] == nullptr) continue;
			if (m_board[j][i]->isWhite() != isWhite) {
				if (m_board[j][i]->isAttackingKing(std::pair<int, int>(j, i), kingPos, *this)) return true;
			}
		}
	}

	return false;
}

void GameManager::debugPrint()
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (m_board[j][i] == nullptr) std::cout << "# ";
			if (m_board[j][i] != nullptr) std::cout << m_board[j][i]->getPiece() << " ";
		}
		std::cout << "\n";
	}
}
