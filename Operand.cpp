#include "Operand.hpp"

template<class T> Operand<T>::Operand()
{
	_val = std::to_string(0);
}

template<class T> Operand<T>::Operand(T val)
{
	_val = std::to_string(val);
}

template<class T> Operand<T>::Operand(std::string val)
{
	_val = std::to_string(std::stod(val));
}

template<class T> Operand<T>::Operand( Operand<T> const & cpy )
{
	*this = cpy;
}

template<class T> Operand<T> &			Operand<T>::operator=( Operand<T> const & cpy )
{
	_val = cpy.toString();
	return *this;
}

template<class T> int					Operand<T>::getPrecision(void) const
{
	return 2;
}

template<class T> eOperandType		Operand<T>::getType(void) const
{
	return Double;
}

template<class T> IOperand const *	Operand<T>::operator+( IOperand const & rhs ) const
{
	_val = std::to_string(std::stoi(_val) + std::stoi(rhs.toString()));
	return this;
}

template<class T> IOperand const *	Operand<T>::operator-( IOperand const & rhs ) const
{
	_val = std::to_string(std::stoi(_val) - std::stoi(rhs.toString()));
	return this;
}

template<class T> IOperand const *	Operand<T>::operator*( IOperand const & rhs ) const
{
	_val = std::to_string(std::stoi(_val) * std::stoi(rhs.toString()));
	return this;
}

template<class T> IOperand const *	Operand<T>::operator/( IOperand const & rhs ) const
{
	_val = std::to_string(std::stoi(_val) / std::stoi(rhs.toString()));
	return this;
}

template<class T> IOperand const *	Operand<T>::operator%( IOperand const & rhs ) const
{
	_val = std::to_string(std::stoi(_val) % std::stoi(rhs.toString()));
	return this;
}

template<class T> std::string const &	Operand<T>::toString(void) const
{
	return _val;
}

template<class T> Operand<T>::~Operand(void)
{
	
}
