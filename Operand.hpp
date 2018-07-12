#pragma once

#include "IOperand.hpp"
#include <stdint.h>
#include "CreateOperand.hpp"
#include <cmath>
#include <sstream>
#include <iomanip>
#include "AVMException.hpp"

template<class T>
class	Operand : public IOperand
{
	public:
		Operand() {
			_val = std::to_string(0);
			_type = Int8;	
		}
		Operand(T val, eOperandType type) {
			std::string tmp = std::to_string(val);
			_type = type;
			std::stringstream	s;

			if (_type == Int8)
				s << std::fixed << std::setprecision(0) << (int)val;
			else if (_type <= Int32)
				s << std::fixed << std::setprecision(0) << val;
			else if (_type >= Float)
				s << std::fixed << std::setprecision(2) << val;
			_val = s.str();
		}
		Operand(std::string val, eOperandType type) {
			_val = std::to_string(std::stod(val));
			_type = type;
		}
		Operand( Operand const & cpy ) {
			*this = cpy;
		}
		Operand &			operator=( Operand const & cpy ) const {
			_val = cpy.toString();
			return *this;
		}
		int					getPrecision(void) const {
			return static_cast<int>(_type);
		}
		eOperandType		getType(void) const {
			return _type;
		}
		IOperand const *	operator+( IOperand const & rhs ) const {
			eOperandType	type;
			CreateOperand *cOp = new CreateOperand();

			if (this->getPrecision() < rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();
			if (type >= Float)
				cOp->checkOverflow(type, std::to_string(stold(this->_val) + stold(rhs.toString())));
			else
				cOp->checkOverflow(type, std::to_string(stoll(this->_val) + stoll(rhs.toString())));
			IOperand const *ret = cOp->createOperand(this->getType(), std::to_string(stod(this->_val) + stod(rhs.toString())));

			delete(cOp);
			return ret;
		}
		IOperand const *	operator-( IOperand const & rhs ) const {
			eOperandType	type;
			CreateOperand *cOp = new CreateOperand();
			if (this->getPrecision() < rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();
			if (type >= Float)
				cOp->checkOverflow(type, std::to_string(stold(this->_val) - stold(rhs.toString())));
			else
				cOp->checkOverflow(type, std::to_string(stoll(this->_val) - stoll(rhs.toString())));
			IOperand const *ret = cOp->createOperand(this->getType(), std::to_string(stod(this->_val) - stod(rhs.toString())));

			delete(cOp);
			return ret;
		}
		IOperand const *	operator*( IOperand const & rhs ) const {
			eOperandType	type;
			CreateOperand *cOp = new CreateOperand();
			if (this->getPrecision() < rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();
			if (type >= Float)
				cOp->checkOverflow(type, std::to_string(stold(this->_val) * stold(rhs.toString())));
			else
				cOp->checkOverflow(type, std::to_string(stoll(this->_val) * stoll(rhs.toString())));
			IOperand const *ret = cOp->createOperand(this->getType(), std::to_string(stod(this->_val) * stod(rhs.toString())));

			delete(cOp);
			return ret;
		}
		IOperand const *	operator/( IOperand const & rhs ) const {
			eOperandType	type;
			CreateOperand *cOp = new CreateOperand();
			if (this->getPrecision() < rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();
			if (stod(rhs.toString()) == 0)
				throw AVMException("Error: division by 0 !");
			if (type >= Float)
				cOp->checkOverflow(type, std::to_string(stold(this->_val) / stold(rhs.toString())));
			else
				cOp->checkOverflow(type, std::to_string(stoll(this->_val) / stoll(rhs.toString())));
			IOperand const *ret = cOp->createOperand(this->getType(), std::to_string(stod(this->_val) / stod(rhs.toString())));

			delete(cOp);
			return ret;
		}
		IOperand const *	operator%( IOperand const & rhs ) const {
			eOperandType	type;
			CreateOperand *cOp = new CreateOperand();

			if (this->getPrecision() < rhs.getPrecision())
				type = this->getType();
			else
				type = rhs.getType();
			if (stod(rhs.toString()) == 0)
				throw AVMException("Error: modulo by 0 !");
			if (type >= Float)
				cOp->checkOverflow(type, std::to_string(std::fmod(stold(this->_val), stold(rhs.toString()))));
			else
				cOp->checkOverflow(type, std::to_string(stoll(this->_val) % stoll(rhs.toString())));
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
		eOperandType	_type;
};
