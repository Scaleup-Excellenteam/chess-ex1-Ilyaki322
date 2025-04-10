#pragma once
#include "Chess.h"
#include "Piece/Piece.h"
#include <memory>

constexpr int BOARD_SIZE = 8;

typedef std::pair<int, int> coords;

class GameManager {
public:

	GameManager(string board);

	int evalPlayerMove(string playerInput);

	const std::unique_ptr<Piece>(&getBoard() const)[BOARD_SIZE][BOARD_SIZE];

private:
	coords inputToCoords(std::pair<char, char> input);

	int isPlayerTurn(std::pair<char, char> input);
	int evalPiece(coords src, coords target);

	void playMove(coords src, coords target);
	void undoLastMove();

	int checkCheck(); // hehe
	bool isKingUnderAttack(coords kingPos, bool isWhite);

	void debugPrint();


	std::unique_ptr<Piece> m_board[BOARD_SIZE][BOARD_SIZE];

	bool m_whitePlayerTurn;
	coords m_whiteKing;
	coords m_blackKing;

	std::unique_ptr<Piece> m_defeatedLastTurn;
	coords m_srcLastTurn;
	coords m_targetLastTurn;
};