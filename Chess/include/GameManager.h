#pragma once
#include "Chess.h"
#include "Piece/Piece.h"
#include "BoardStack.h"
#include <memory>
#include <string>

enum responseCode {
	RC_NEXT_CHECK = -1,
	RC_TILE_EMPTY = 11,
	RC_TILE_OPPONENT = 12,
	RC_FRIENDLY_FIRE = 13,
	RC_ILLEGAL = 21,
	RC_LEADS_TO_MATE = 31,
	RC_OK_CHECK = 41,
	RC_OK = 42
};

constexpr int BOARD_SIZE = 8;

typedef std::pair<int, int> coords;

/*
  Responsible for general game rules, overall player mistakes, such as wrong tile selection.
  Or rules that apply to multiple pieces, such as check.
  Contains the game 'board', location of the kings for convenience, and backup data to undo if necessary.
*/
class GameManager {
public:

	GameManager(string board);

	int evalPlayerMove(string playerInput);
	void playMove2(coords src, coords target);
	void undoLastMove2();
	int checkCheck(); // hehe

	string printBest();

	const std::vector<std::vector<std::pair<coords, coords>>> getAllMoves(bool white);

	const std::unique_ptr<Piece>(&getBoard() const)[BOARD_SIZE][BOARD_SIZE];
	
	const int getTurnCounter() const { return m_turnCounter; }

private:
	void initBoard(const std::string board);

	coords inputToCoords(std::pair<char, char> input);
	std::pair<char, char> coordsToInput(std::pair<int, int> coord);

	int isPlayerTurn(std::pair<char, char> input);
	int evalPiece(coords src, coords target);

	void playMove(coords src, coords target);
	void undoLastMove();

	bool isKingUnderAttack(coords kingPos, bool isWhite);

	std::unique_ptr<Piece> m_board[BOARD_SIZE][BOARD_SIZE];

	bool m_whitePlayerTurn;
	int m_turnCounter;

	coords m_whiteKing;
	coords m_blackKing;

	Piece* m_lastMoving; // to turn moved flag

	// backup for rollbacks incase of illegal moves
	std::unique_ptr<Piece> m_defeatedLastTurn;
	coords m_srcLastTurn;
	coords m_targetLastTurn;

	BoardStack m_logStack;
};