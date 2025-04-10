#pragma once
#include "Piece/Piece.h"

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
