#pragma once

#include "IOperand.hpp"
#include <stdint.h>
#include "CreateOperand.hpp"

template<class T>
class	Operand : public IOperand
{
	public:
		Operand();
		Operand(T val);
		Operand(std::string val);
		Operand( Operand const & cpy );
		Operand &			operator=( Operand const & cpy );
		int					getPrecision(void) const; // Precision of the type of the instance
		eOperandType		getType(void) const; // Type of the instance
		IOperand const *	operator+( IOperand const & rhs ) const; // Sum
		IOperand const *	operator-( IOperand const & rhs ) const; // Difference
		IOperand const *	operator*( IOperand const & rhs ) const; // Product
		IOperand const *	operator/( IOperand const & rhs ) const; // Quotient
		IOperand const *	operator%( IOperand const & rhs ) const; // Modulo
		std::string const &	toString(void) const; // String representation of the instance
		~Operand(void);
	protected:
		std::string		_val;
};
