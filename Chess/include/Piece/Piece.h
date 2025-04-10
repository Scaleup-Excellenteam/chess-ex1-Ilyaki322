#pragma once

#include <tuple>
#include <cctype>
#include <vector>

class GameManager;

typedef std::pair<int, int> coords;

class Piece {
protected:

	virtual std::vector<coords> getPossibleMoves(coords pos, GameManager& manager) const = 0;
	bool containCoords(std::vector<coords> vec, coords c) const;
	bool isSameSide(const char other) const;

	const bool m_isWhite;
	const char m_type;
	std::pair<int, int> m_pos; // not using??

public:

	Piece(const char t, coords pos) : m_type(t), m_pos(pos), m_isWhite(std::isupper(t)) {}
	virtual ~Piece() = default;
	virtual int isMoveValid(coords pos, coords target, GameManager& manager) const = 0;
	virtual bool isAttackingKing(coords pos, coords enemyKing, GameManager& manager) const = 0;

	char getPiece() const { return m_type; }
	bool isWhite() const { return m_isWhite; }


};