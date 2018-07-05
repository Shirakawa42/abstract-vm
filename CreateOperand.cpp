#include "CreateOperand.hpp"

CreateOperand::CreateOperand()
{
	_functions[0] = &CreateOperand::createInt8;
	_functions[1] = &CreateOperand::createInt16;
	_functions[2] = &CreateOperand::createInt32;
	_functions[3] = &CreateOperand::createFloat;
	_functions[4] = &CreateOperand::createDouble;
}

IOperand const *	CreateOperand::createInt8( std::string const & val )
{
	return new Operand<int8_t>(std::stoi(val));
}

IOperand const *	CreateOperand::createInt16( std::string const & val )
{
	return new Operand<int16_t>(std::stoi(val));
}

IOperand const *	CreateOperand::createInt32( std::string const & val )
{
	return new Operand<int32_t>(std::stoi(val));
}

IOperand const *	CreateOperand::createFloat( std::string const & val )
{
	return new Operand<float>(std::stof(val));
}

IOperand const *	CreateOperand::createDouble( std::string const & val )
{
	return new Operand<double>(std::stod(val));
}

IOperand const *	CreateOperand::createOperand( eOperandType type, std::string const & val )
{
	return (this->*_functions[type])(val);
}
