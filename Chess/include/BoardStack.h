#pragma once
#include<vector>
#include<memory>

#include "Piece/Piece.h"

typedef std::pair<int, int> coords;

/*
* Struct to hold all relevant info for a specific game move.
*/
struct MoveLog {
	coords _lastWKing;
	coords _lastBKing;
	coords _startSquare;
	coords _targetSquare;
	std::unique_ptr<Piece> _targetPiece;

	MoveLog(MoveLog&& other) noexcept = default;
	MoveLog& operator=(MoveLog&& other) noexcept = default;

	MoveLog(const MoveLog&) = delete;
	MoveLog& operator=(const MoveLog&) = delete;

	MoveLog(coords lastW, coords lastB, coords start, coords target, std::unique_ptr<Piece> defeated)
		: _lastWKing(lastW), _lastBKing(lastB), _startSquare(start), _targetSquare(target),
		_targetPiece(std::move(defeated)) {}
};

/*
* This class acts as a move stack, pushes and pops moves.
* used to be able to reverse a few moves and not only one as in ex1.
*/
class BoardStack {
public:
	BoardStack() = default;

	void insert(MoveLog log);
	void clear();
	MoveLog lastMove();

private:

	std::vector<MoveLog> m_log;
};