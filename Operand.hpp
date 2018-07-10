#pragma once

#include "IOperand.hpp"
#include <stdint.h>
#include "CreateOperand.hpp"
#include <cmath>

template<class T>
class	Operand : public IOperand
{
	public:
		Operand() {
			_val = std::to_string(0);	
		}
		Operand(T val) {
			_val = std::to_string(val);
		}
		Operand(std::string val) {
			_val = std::to_string(std::stod(val));
		}
		Operand( Operand const & cpy ) {
			*this = cpy;
		}
		Operand &			operator=( Operand const & cpy ) const {
			_val = cpy.toString();
			return *this;
		}
		int					getPrecision(void) const {
			return 2;
		}
		eOperandType		getType(void) const {
			return Double;
		}
		IOperand const *	operator+( IOperand const & rhs ) const {
			CreateOperand *cOp = new CreateOperand();
			IOperand const *ret = cOp->createOperand(this->getType(), std::to_string(stod(this->_val) + stod(rhs.toString())));

			delete(cOp);
			return ret;
		}
		IOperand const *	operator-( IOperand const & rhs ) const {
			CreateOperand *cOp = new CreateOperand();
			IOperand const *ret = cOp->createOperand(this->getType(), std::to_string(stod(this->_val) - stod(rhs.toString())));

			delete(cOp);
			return ret;
		}
		IOperand const *	operator*( IOperand const & rhs ) const {
			CreateOperand *cOp = new CreateOperand();
			IOperand const *ret = cOp->createOperand(this->getType(), std::to_string(stod(this->_val) * stod(rhs.toString())));

			delete(cOp);
			return ret;
		}
		IOperand const *	operator/( IOperand const & rhs ) const {
			CreateOperand *cOp = new CreateOperand();
			IOperand const *ret = cOp->createOperand(this->getType(), std::to_string(stod(this->_val) / stod(rhs.toString())));

			delete(cOp);
			return ret;
		}
		IOperand const *	operator%( IOperand const & rhs ) const {
			CreateOperand *cOp = new CreateOperand();
			IOperand const *ret = cOp->createOperand(this->getType(), std::to_string(std::fmod(stod(this->_val), stod(rhs.toString()))));

			delete(cOp);
			return ret;
		}
		std::string const &	toString(void) const {
			return _val;
		}
		~Operand(void) {}
	private:
		std::string		_val;
};
