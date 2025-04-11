#pragma once
#include <functional>
#include <map>
#include <memory>

#include "Piece.h"

typedef std::function<std::unique_ptr<Piece>(char c)> func;

/*
  Standard factory for piece creation.
*/
class PieceFactory {
public:
	static bool registerPiece(char c, func f);
	std::unique_ptr<Piece> buildPiece(char c);

private:
	static std::map<char, func> m_factoryMap;
};