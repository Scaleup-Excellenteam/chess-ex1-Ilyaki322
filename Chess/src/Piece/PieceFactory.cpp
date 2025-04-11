#pragma once
#include <cctype>
#include "Piece/PieceFactory.h"

/*
* Registers a piece to the factory, called from each individual piece that wants
* to register
* @param c - key by which to create a piece.
* @param f - creation function: std::function<std::unique_ptr<Piece>(char c)>
* @return true if the registration was successful.
*/
bool PieceFactory::registerPiece(char c, func f)
{
	char key = (char)std::tolower(c);
	if (m_factoryMap.find(key) != m_factoryMap.end()) return false;

	m_factoryMap[key] = f;
	return true;
}

/*
* Creates the requested piece.
* @param c - key for the requested piece.
* @return Unique pointer to the requested piece
*/
std::unique_ptr<Piece> PieceFactory::buildPiece(char c) {
	char key = (char)std::tolower(c);
	auto it = m_factoryMap.find(key);
	if (it == m_factoryMap.end()) {
		return nullptr;
	}
	return it->second(c);
}

std::map<char, func> PieceFactory::m_factoryMap;
