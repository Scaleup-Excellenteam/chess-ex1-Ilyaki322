#pragma once

#include <exception>
#include <string>

/*
* an exception class to indicate that we are trying to access an empty data structure.
*/
class EmptyStructureException : public std::exception {
public:

	EmptyStructureException(const std::string name) : m_structName(name), m_message(name + ": is empty") {}
	const char* what() const noexcept override
	{
		return m_message.c_str();
	}

private:

	const std::string m_structName;
	const std::string m_message;
};