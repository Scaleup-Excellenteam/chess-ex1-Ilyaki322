#pragma once

#include <exception>
#include <string>

/*
* An exception to indicate the the setup string for the board is invalid.
*/
class NoKingsFoundException : public std::exception {
public:

	NoKingsFoundException() : m_message("No Kings on the Board, Make sure your board is setup correctly.") {}
	const char* what() const noexcept override
	{
		return m_message.c_str();
	}

private:

	const std::string m_message;
};