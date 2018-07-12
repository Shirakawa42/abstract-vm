#pragma once

#include "IOperand.hpp"
#include "mutantstack.hpp"
#include "CreateOperand.hpp"
#include "AVMException.hpp"

class Parser
{
	public:
		Parser();
		Parser(char **av);
		~Parser();
		void	parseFile(std::string file);
	private:
		int		push(std::string const &, int);
		int		pop(std::string const &, int);
		int		dump(std::string const &, int);
		int		assert(std::string const &, int);
		int		add(std::string const &, int);
		int		sub(std::string const &, int);
		int		mul(std::string const &, int);
		int		div(std::string const &, int);
		int		mod(std::string const &, int);
		int		print(std::string const &, int);
		int		exit(std::string const &, int);
		typedef int (Parser::*Commands)(std::string const &, int);
		MutantStack<const IOperand*>		*_stack;
		Commands					_commands[11];
		CreateOperand				*_cOp;
};