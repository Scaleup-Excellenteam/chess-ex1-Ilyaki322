#include "GameManager.h"
#include "Piece/PieceFactory.h"

/*
* Inits the game board with Pieces
* @param board - the start state of the board as given in the exercise.
*/
GameManager::GameManager(string board)
	: m_whitePlayerTurn(true), m_defeatedLastTurn(nullptr), m_lastMoving(nullptr),
	m_srcLastTurn(std::pair<int,int>(-1, -1)), m_targetLastTurn(std::pair<int, int>(-1, -1)),
	m_whiteKing(std::pair<int, int>(-1, -1)), m_blackKing(std::pair<int, int>(-1, -1))
{
	PieceFactory pieceFactory;
	std::cout << board;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			char currSymbol = board[j + i * BOARD_SIZE];
			if (currSymbol == '#') m_board[i][j] = nullptr;
			else m_board[i][j] = pieceFactory.buildPiece(currSymbol);
			if (currSymbol == 'K') m_whiteKing = std::pair<int, int>(i, j);
			if (currSymbol == 'k') m_blackKing = std::pair<int, int>(i, j);
		}
	}
}

/*
* Takes the user input, checks it and returns a ResponseCode.
* @param playerInput - 4sized string that contains coords for user move
* for example e4d5 or A2F5. must be in range of the game board 1-8 a-h
* @return A corresponding ResponseCode for the graphics engine.
*/
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

	playMove2(srcInt, targetInt);
	int res = checkCheck();

	if (res == (int)RC_LEADS_TO_MATE) {
		undoLastMove2();
		return res;
	}

	m_whitePlayerTurn = !m_whitePlayerTurn;
	if (m_lastMoving) m_lastMoving->moved();

	return res;
}

/*
* @return The Const game board array
*/
const std::unique_ptr<Piece>(&GameManager::getBoard() const)[BOARD_SIZE][BOARD_SIZE]
{
	return m_board;
}

/*
* Translates the user input to board indices
* @param input - char,char pair for board positions eg: e4, d5, ...
* @return An int,int pair as board indices to use with the m_board array.
*/
std::pair<int, int> GameManager::inputToCoords(std::pair<char, char> input)
{
	int row = input.first - 'a';
	int col = (input.second - '0') - 1;

	return std::pair<int, int>(row, col);
}

/*
* Takes the source tile of player input, and checks if the piece on this tile
* belongs to the player.
* @param input - first half of the player input, eg: e4, d5, ...
* @return A corresponding ResponseCode for the graphics engine.
*/
int GameManager::isPlayerTurn(std::pair<char, char> input)
{
	auto pos = inputToCoords(input);

	if (m_board[pos.first][pos.second] == nullptr) return RC_TILE_EMPTY;

	char piece = m_board[pos.first][pos.second]->getPiece();

	if ((std::isupper(piece) && m_whitePlayerTurn) ||
		 (!std::isupper(piece) && !m_whitePlayerTurn)) return RC_NEXT_CHECK;

	return RC_TILE_OPPONENT;
}

/*
* Checks if the piece in 'src' can move to 'target'
* @param src - the coordinations of the piece to move.
* @param target - the coordinations where to move the piece.
* @return A corresponding ResponseCode for the graphics engine.
*/
int GameManager::evalPiece(coords src, coords target)
{
	return m_board[src.first][src.second]->isMoveValid(src, target, *this);
}

/*
* Plays the move src->target.
* Also backsup incase undo is needed.
* @param src - the coordinations of the piece to move.
* @param target - the coordinations where to move the piece.
*/
void GameManager::playMove(coords src, coords target)
{
	// check if something is 'eaten' back it up.
	if (m_board[target.first][target.second] != nullptr)
		m_defeatedLastTurn = std::move(m_board[target.first][target.second]);
	else m_defeatedLastTurn = nullptr;

	// move src -> target
	m_board[target.first][target.second] = std::move(m_board[src.first][src.second]);
	m_board[src.first][src.second] = nullptr;

	// save kings locations
	if (m_whiteKing == src) m_whiteKing = target;
	if (m_blackKing == src) m_blackKing = target;

	// backup last turn
	m_srcLastTurn = src;
	m_targetLastTurn = target;

	// save piece that moved (to toggle moved() flag later if needed).
	m_lastMoving = m_board[target.first][target.second].get();
}
void GameManager::playMove2(coords src, coords target)
{
	std::unique_ptr<Piece> defeated = nullptr;
	if (m_board[target.first][target.second] != nullptr)
		defeated = std::move(m_board[target.first][target.second]);

	MoveLog log{
		m_whiteKing,
		m_blackKing,
		src,
		target,
		std::move(defeated)
	};
	m_logStack.insert(std::move(log));

	// move src -> target
	m_board[target.first][target.second] = std::move(m_board[src.first][src.second]);
	m_board[src.first][src.second] = nullptr;

	// save kings locations
	if (m_whiteKing == src) m_whiteKing = target;
	if (m_blackKing == src) m_blackKing = target;

	// save piece that moved (to toggle moved() flag later if needed).
	m_lastMoving = m_board[target.first][target.second].get();
}

/*
* If we found that the last move caused a checkmate we undo.
*/
void GameManager::undoLastMove()
{
	m_board[m_srcLastTurn.first][m_srcLastTurn.second] = std::move(m_board[m_targetLastTurn.first][m_targetLastTurn.second]);

	if (m_whiteKing == m_targetLastTurn) m_whiteKing = m_srcLastTurn;
	if (m_blackKing == m_targetLastTurn) m_blackKing = m_srcLastTurn;

	if (m_defeatedLastTurn != nullptr) {
		m_board[m_targetLastTurn.first][m_targetLastTurn.second] = std::move(m_defeatedLastTurn);
	}
}
void GameManager::undoLastMove2()
{
	MoveLog last = m_logStack.lastMove();
	m_whiteKing = last._lastWKing;
	m_blackKing = last._lastBKing;

	m_board[last._startSquare.first][last._startSquare.second] = std::move(m_board[last._targetSquare.first][last._targetSquare.second]);

	if (last._targetPiece != nullptr) {
		m_board[last._targetSquare.first][last._targetSquare.second] = std::move(last._targetPiece);
	}
}

/*
* Checks if last move caused a checkmate
* @return A corresponding ResponseCode for the graphics engine.
*/
int GameManager::checkCheck()
{
	// Played move checkmated himself, undo.
	if ((m_whitePlayerTurn && isKingUnderAttack(m_whiteKing, true)) ||
		(!m_whitePlayerTurn && isKingUnderAttack(m_blackKing, false))) {
		return RC_LEADS_TO_MATE;
	}

	// Player checked the enemy player.
	if ((m_whitePlayerTurn && isKingUnderAttack(m_blackKing, false)) ||
		(!m_whitePlayerTurn && isKingUnderAttack(m_whiteKing, true))) {
		return RC_OK_CHECK;
	}

	// No checks.
	return RC_OK;
}

const std::vector<std::vector<std::pair<coords, coords>>> GameManager::getAllMoves(bool white)
{
	std::vector<std::vector<std::pair<coords, coords>>> moves;

	for (int i = 0; i < BOARD_SIZE; i++) 
	for (int j = 0; j < BOARD_SIZE; j++) {
		if (m_board[i][j] == nullptr) continue;
		if (m_board[i][j]->isWhite() == white) {
			coords start = { i,j };
			auto possibleMoves = m_board[i][j]->getPossibleMoves(start, *this);
			std::vector<std::pair<coords, coords>> validMoves;
			for (const auto& m : possibleMoves) {
				playMove2(start, m);
				std::pair<coords, coords> move(start, m);
				if (checkCheck() != RC_LEADS_TO_MATE) validMoves.emplace_back(move);
				undoLastMove2();
			}
			moves.push_back(validMoves);
		}
	}

	return moves;
}

/*
* Checks if any of the pieces attack the opposite king
* @param kingPos - the coordinates of the king we want to check
* @param isWhite - the color of the king: white-true, black-false.
* @return true if given king is under attack.
*/
bool GameManager::isKingUnderAttack(coords kingPos, bool isWhite)
{
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (m_board[i][j] == nullptr) continue;
			if (m_board[i][j]->isWhite() != isWhite) {
				if (m_board[i][j]->isAttackingKing(std::pair<int, int>(i, j), kingPos, *this)) return true;
			}
		}
	}

	return false;
}
