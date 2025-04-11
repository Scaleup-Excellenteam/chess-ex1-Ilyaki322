#pragma once
#include <cctype>
#include "Piece/PieceFactory.h"

std::map<char, func> PieceFactory::m_factoryMap;

bool PieceFactory::registerPiece(char c, func f)
{
	char key = (char)std::tolower(c);
	if (m_factoryMap.find(key) != m_factoryMap.end()) return false;

	m_factoryMap[key] = f;
	return true;
}

std::unique_ptr<Piece> PieceFactory::buildPiece(char c, std::pair<int, int> pos) {
	char key = (char)std::tolower(c);
	auto it = m_factoryMap.find(key);
	if (it == m_factoryMap.end()) {
		return nullptr;
	}
	return it->second(c, pos);
}
