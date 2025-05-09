#include "BoardStack.h"

void BoardStack::insert(MoveLog log)
{
	m_log.emplace_back(std::move(log));
}

void BoardStack::clear()
{
	m_log.clear();
}

MoveLog BoardStack::lastMove()
{
	MoveLog last = std::move(m_log.back());
	m_log.pop_back();
	return last;
}
