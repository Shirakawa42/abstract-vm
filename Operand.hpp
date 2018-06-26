#include "IOperand.hpp"

template<class T>
class	Operand : public IOperand
{
	public:
		Operand();
		Operand(T val);
		Operand(std::string val);
		Operand( Operand const & cpy );
		Operand &			operator=( Operand const & cpy );
		IOperand const *	createOperand( eOperandType type, std::string const & value ) const;
		int					getPrecision(void) const = 0; // Precision of the type of the instance
		eOperandType		getType(void) const = 0; // Type of the instance
		IOperand const *	operator+( IOperand const & rhs ) const = 0; // Sum
		IOperand const *	operator-( IOperand const & rhs ) const = 0; // Difference
		IOperand const *	operator*( IOperand const & rhs ) const = 0; // Product
		IOperand const *	operator/( IOperand const & rhs ) const = 0; // Quotient
		IOperand const *	operator%( IOperand const & rhs ) const = 0; // Modulo
		std::string const &	toString(void) const = 0; // String representation of the instance
		~IOperand(void);
	protected:
		std::string		_val;
};
