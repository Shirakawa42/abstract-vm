#include "CreateOperand.hpp"
#include "IOperand.hpp"
#include "Operand.hpp"
#include <stack>
#include <fstream>
#include "mutantstack.hpp"
#include "Parser.hpp"

int		main(int ac, char **av)
{
	if (ac != 2 && ac != 1)
		return 0;
	try 
	{
		if (ac == 1)
			Parser parser = Parser();
		else
			Parser parser = Parser(av);
	}
	catch (std::exception const & e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}