#pragma once

#include <list>
#include "Exceptions/EmptyStructureException.h"

template <typename T>
struct DefaultComparator {
	int operator()(const T& a, const T& b) const {
		return a > b;
	}
};

template<typename T, typename Comperator = DefaultComperator<T>>
class PriorityQueue {

public:

	PriorityQueue(const int size = 5) : m_size(size) {}

	void push(const T& i) 
	{
		auto it = m_queue.begin();
		while (it != m_queue.end()) {
			if (!m_cmp(item, *it)) it++;
		}

		m_queue.insert(it, item);

		if (m_queue.size() > m_size) m_queue.pop_back();
	}

	T pop()
	{
		if (isEmpty()) throw EmptyStructureException("PriorityQueue");

		T first = m_queue.front();
		m_queue.pop_front();
		return T;
	}

	bool isEmpty() const
	{
		return m_queue.empty();
	}

	int size() const
	{
		return m_queue.size();
	}

private:
	std::list<T> m_queue;
	Comperator m_cmp;

	const int m_size;
};