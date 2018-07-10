#include "CreateOperand.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"
#include <stack>
#include <fstream>

void	file_input(std::stack<IOperand*> **stack, std::string file)
{
	std::cout << file << std::endl;
}

void	standard_input(std::stack<IOperand*> **stack)
{
	std::string 	file = "";
	std::string		command;

	while (1)
	{
		std::getline(std::cin, command);
		if (std::string(command) == ";;")
			break ;
		file = file + command + "\n";
	}
	file_input(stack, file);
}

int		main(int ac, char **av)
{
	if (ac != 2 && ac != 1)
		return 0;
	std::stack<IOperand*>	*stack = new std::stack<IOperand*>();
	if (ac == 1)
		standard_input(&stack);
	else
	{
		std::string		file = "";
		char			buf[4096];
		std::ifstream	input(av[1]);

		while (input.good())
		{
			input.getline(buf, sizeof(buf));
			file += std::string(buf) + "\n";
		}
		file_input(&stack, file);
	}
	delete stack;
	return 0;
}