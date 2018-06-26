#include "Operand.hpp"

template<class T> Operand<T>::Operand() {}

 template<class T> Operand<T>::Operand(T val) {  }
 template<class T> Operand<T>::Operand(std::string val);
 template<class T> Operand<T>::Operand( Operand const & cpy );
 template<class T> Operand<T>::Operand &			operator=( Operand const & cpy );
 template<class T> IOperand const *	Operand<T>::createOperand( eOperandType type, std::string const & value ) const;
 template<class T> int					Operand<T>::getPrecision(void) const = 0; // Precision of the type of the instance
 template<class T> eOperandType		Operand<T>::getType(void) const = 0; // Type of the instance
 template<class T> IOperand const *	Operand<T>::operator+( IOperand const & rhs ) const = 0; // Sum
 template<class T> IOperand const *	Operand<T>::operator-( IOperand const & rhs ) const = 0; // Difference
 template<class T> IOperand const *	Operand<T>::operator*( IOperand const & rhs ) const = 0; // Product
 template<class T> IOperand const *	Operand<T>::operator/( IOperand const & rhs ) const = 0; // Quotient
 template<class T> IOperand const *	Operand<T>::operator%( IOperand const & rhs ) const = 0; // Modulo
 template<class T> std::string const &	Operand<T>::toString(void) const = 0; // String representation of the instance
 template<class T> Operand<T>::~IOperand(void);
