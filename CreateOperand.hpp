#pragma once

#include "IOperand.hpp"
#include <string>
#include <iostream>


class	CreateOperand
{
	public:
		CreateOperand();
		IOperand const *	createOperand( eOperandType type, std::string const & value );
		void				checkOverflow(eOperandType const type, std::string const & val);
	private:
		IOperand const *	createInt8( std::string const & val ) const;
		IOperand const *	createInt16( std::string const & val ) const;
		IOperand const *	createInt32( std::string const & val ) const;
		IOperand const *	createFloat( std::string const & val ) const;
		IOperand const *	createDouble( std::string const & val ) const;
		typedef IOperand const *(CreateOperand::*funcs)(const std::string &) const;
		funcs _functions[5];
};