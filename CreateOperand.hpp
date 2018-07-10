#pragma once

#include "IOperand.hpp"
#include <string>
#include <iostream>


class	CreateOperand
{
	public:
		CreateOperand();
		IOperand const *	createInt8( std::string const & val );
		IOperand const *	createInt16( std::string const & val );
		IOperand const *	createInt32( std::string const & val );
		IOperand const *	createFloat( std::string const & val );
		IOperand const *	createDouble( std::string const & val );
		IOperand const *	createOperand( eOperandType type, std::string const & value );
	private:
		typedef IOperand const *(CreateOperand::*funcs)(const std::string &);
		funcs _functions[5];
};
