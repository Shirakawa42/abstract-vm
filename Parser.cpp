#include "Parser.hpp"
#include <fstream>
#include "CreateOperand.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"

Parser::Parser()
{
	_stack = new MutantStack<const IOperand*>(); 
	_commands[0] = &Parser::push;
	_commands[1] = &Parser::pop;
	_commands[2] = &Parser::dump;
	_commands[3] = &Parser::assert;
	_commands[4] = &Parser::add;
	_commands[5] = &Parser::sub;
	_commands[6] = &Parser::mul;
	_commands[7] = &Parser::div;
	_commands[8] = &Parser::mod;
	_commands[9] = &Parser::print;
	_commands[10] = &Parser::exit;
	_cOp = new CreateOperand;

	std::string 	file = "";
	std::string		command;

	while (1)
	{
		std::getline(std::cin, command);
		if (std::string(command) == ";;")
			break ;
		file = file + command + "\n";
	}
	parseFile(file);
}

Parser::Parser(char **av)
{
	_stack = new MutantStack<const IOperand*>();
	_commands[0] = &Parser::push;
	_commands[1] = &Parser::pop;
	_commands[2] = &Parser::dump;
	_commands[3] = &Parser::assert;
	_commands[4] = &Parser::add;
	_commands[5] = &Parser::sub;
	_commands[6] = &Parser::mul;
	_commands[7] = &Parser::div;
	_commands[8] = &Parser::mod;
	_commands[9] = &Parser::print;
	_commands[10] = &Parser::exit;
	_cOp = new CreateOperand;
	
	std::string		file = "";
	char			buf[4096];
	std::ifstream	input(av[1]);

	while (input.good())
	{
		input.getline(buf, sizeof(buf));
		file += std::string(buf) + "\n";
	}
	parseFile(file);
}

Parser::~Parser()
{
	delete _stack;
	delete _cOp;
}

static eOperandType	convert(std::string const & str)
{
	if (str == "int8")
		return Int8;
	else if (str == "int16")
		return Int16;
	else if (str == "int32")
		return Int32;
	else if (str == "float")
		return Float;
	else if (str == "double")
		return Double;
	throw AVMException("Error: \"" + str + "\" is not a recognized type.");
}

int 	Parser::push(std::string const & file, int i)
{
	std::string		type = "";
	std::string		value = "";

	while (file[i] && (file[i] == ' ' || file[i] == '\n') && file[i] != ';')
		i++;
	while (file[i] && file[i] != '(' && file[i] != ';')
		type += file[i++];
	if (!file[i])
		throw AVMException("Error: \"push\" called without or with a wrong value !");
	else if (file[i] != ';')
		i++;
	while (file[i] && file[i] != ')' && file[i] != ';')
		value += file[i++];
	if (file[i] != ')')
		throw AVMException("Error: \"push\" called without a closing \")\" !");
	_stack->push(_cOp->createOperand(convert(type), value));
	return i;
}

int 	Parser::pop(std::string const & file, int i)
{
	(void)file;
	if (!_stack->empty())
		_stack->pop();
	else
		throw AVMException("Error: \"pop\" on empty stack !");
	return i;
}

int 	Parser::dump(std::string const & file, int i)
{
	(void)file;
	MutantStack<const IOperand*>			*cpy = _stack;
	MutantStack<const IOperand*>::iterator	it = cpy->end();
	it--;
	while (it != cpy->begin())
	{
		std::cout << (*it)->toString() << std::endl;
		it--;
	}
	std::cout << (*it)->toString() << std::endl;
	return i;
}

int 	Parser::assert(std::string const & file, int i)
{
	std::string		type = "";
	std::string		value = "";

	while (file[i] && (file[i] == ' ' || file[i] == '\n') && file[i] != ';')
		i++;
	while (file[i] && file[i] != '(' && file[i] != ';')
		type += file[i++];
	if (!file[i])
		throw AVMException("Error: \"assert\" called without or with a wrong value !");
	else if (file[i] != ';')
		i++;
	while (file[i] && file[i] != ')' && file[i] != ';')
		value += file[i++];
	if (file[i] != ')')
		throw AVMException("Error: \"assert\" called without a closing \")\" !");
	if (!_stack->empty() && value == _stack->top()->toString() && convert(type) == _stack->top()->getType())
		return i;
	else if (!_stack->empty())
		throw AVMException("Error: \"assert\" does not correspond.");
	else
		throw AVMException("Error: \"assert\" on empty stack !");
}

int 	Parser::add(std::string const & file, int i)
{
	(void)file;
	const IOperand		*op1;
	const IOperand		*op2;

	if (_stack->size() < 2)
		throw AVMException("Error: \"add\" with less than 2 values in stack !");
	op1 = _stack->top();
	_stack->pop();
	op2 = _stack->top();
	_stack->pop();
	const IOperand	*ret = *op1 + *op2;
	_stack->push(ret);
	delete op1;
	delete op2;
	return i;
}

int 	Parser::sub(std::string const & file, int i)
{
	(void)file;
	const IOperand		*op1;
	const IOperand		*op2;

	if (_stack->size() < 2)
		throw AVMException("Error: \"sub\" with less than 2 values in stack !");
	op1 = _stack->top();
	_stack->pop();
	op2 = _stack->top();
	_stack->pop();
	const IOperand	*ret = *op2 - *op1;
	_stack->push(ret);
	delete op1;
	delete op2;
	return i;
}

int 	Parser::mul(std::string const & file, int i)
{
	(void)file;
	const IOperand		*op1;
	const IOperand		*op2;

	if (_stack->size() < 2)
		throw AVMException("Error: \"mul\" with less than 2 values in stack !");
	op1 = _stack->top();
	_stack->pop();
	op2 = _stack->top();
	_stack->pop();
	const IOperand	*ret = *op1 * *op2;
	_stack->push(ret);
	delete op1;
	delete op2;
	return i;
}

int 	Parser::div(std::string const & file, int i)
{
	(void)file;
	const IOperand		*op1;
	const IOperand		*op2;

	if (_stack->size() < 2)
		throw AVMException("Error: \"div\" with less than 2 values in stack !");
	op1 = _stack->top();
	_stack->pop();
	op2 = _stack->top();
	_stack->pop();
	const IOperand	*ret = *op2 / *op1;
	_stack->push(ret);
	delete op1;
	delete op2;
	return i;
}

int 	Parser::mod(std::string const & file, int i)
{
	(void)file;
	const IOperand		*op1;
	const IOperand		*op2;

	if (_stack->size() < 2)
		throw AVMException("Error: \"mod\" with less than 2 values in stack !");
	op1 = _stack->top();
	_stack->pop();
	op2 = _stack->top();
	_stack->pop();
	const IOperand	*ret = *op2 % *op1;
	_stack->push(ret);
	delete op1;
	delete op2;
	return i;
}

int 	Parser::print(std::string const & file, int i)
{
	(void)file;
	const IOperand		*op;

	if (_stack->size() == 0)
		throw AVMException("Error: \"print\" on empty stack !");
	op = _stack->top();
	if ((*op).getType() != Int8)
		throw AVMException("Error: \"print\" on wrong type !");
	std::cout << char(std::stoi((*op).toString()));
	return i;
}

int 	Parser::exit(std::string const & file, int i)
{
	(void)file;
	(void)i;
	std::exit(0);
}

void	Parser::parseFile(std::string file)
{
	int 		j = file.length();
	std::string	commands[] = {
		"push",
		"pop",
		"dump",
		"assert",
		"add",
		"sub",
		"mul",
		"div",
		"mod",
		"print",
		"exit"
	};
	std::string	command;
	std::string	*find;

	for (int i = 0 ; i < j ; i++)
	{
		command = "";
		while (i < j && (file[i] == ' ' || file[i] == '\n') && file[i] != ';')
			i++;
		if (i < j && file[i] == ';')
			while (i < j && file[i] != '\n')
				i++;
		else
		{
			while (i < j && file[i] != ' ' && file[i] != '\n' && file[i] != ';')
				command += file[i++];
			find = std::find(std::begin(commands), std::end(commands), command);
			if (find != std::end(commands))
				i = (this->*_commands[std::distance(commands, find)])(file, i);
			else if (command != "")
				throw AVMException("Unknown instruction: " + command);
		}
	}
	throw AVMException("Error: No exit instruction");
}