#include "CreateOperand.hpp"
#include "Operand.hpp"
#include "AVMException.hpp"
#include <climits>
#include <cfloat>

CreateOperand::CreateOperand()
{
	_functions[0] = &CreateOperand::createInt8;
	_functions[1] = &CreateOperand::createInt16;
	_functions[2] = &CreateOperand::createInt32;
	_functions[3] = &CreateOperand::createFloat;
	_functions[4] = &CreateOperand::createDouble;
}

void			CreateOperand::checkOverflow(eOperandType const type, std::string const & val)
{
	if (type <= Int32)
	{
		long long 	fat = std::stoll(val);

		if ((type == Int32 && fat > INT_MAX) || (type == Int16 && fat > SHRT_MAX) || (type == Int8 && fat > SCHAR_MAX))
			throw AVMException("Error: Overflow");
		else if ((type == Int32 && fat < INT_MIN) || (type == Int16 && fat < SHRT_MIN) || (type == Int8 && fat < SCHAR_MIN))
			throw AVMException("Error: Underflow");
	}
	else
	{
		long double 	fat = std::stold(val);

		if ((type == Float && fat > FLT_MAX) || (type == Double && fat > DBL_MAX))
			throw AVMException("Error: Overflow");
		if ((type == Float && fat < -FLT_MAX) || (type == Double && fat < -DBL_MAX))
			throw AVMException("Error: Underflow");
	}
}

IOperand const *	CreateOperand::createInt8( std::string const & val ) const
{
	return new Operand<int8_t>(std::stoi(val), Int8);
}

IOperand const *	CreateOperand::createInt16( std::string const & val ) const
{
	return new Operand<int16_t>(std::stoi(val), Int16);
}

IOperand const *	CreateOperand::createInt32( std::string const & val ) const
{
	return new Operand<int32_t>(std::stoi(val), Int32);
}

IOperand const *	CreateOperand::createFloat( std::string const & val ) const
{
	return new Operand<float>(std::stof(val), Float);
}

IOperand const *	CreateOperand::createDouble( std::string const & val ) const
{
	return new Operand<double>(std::stod(val), Double);
}

IOperand const *	CreateOperand::createOperand( eOperandType type, std::string const & val )
{
	checkOverflow(type, val);
	return (this->*_functions[type])(val);
}