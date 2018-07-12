#pragma once

#include <exception>

class AVMException : public std::exception
{
	public:
		AVMException() {}
		AVMException(std::string error) : _error(error) {}
		AVMException(const AVMException &) {}
		virtual ~AVMException() {}
		const AVMException & operator = (const AVMException &) { return *this; }
		virtual const char *what() const throw ()
		{
			return _error.c_str();
		}
	private:
		std::string	_error;
};