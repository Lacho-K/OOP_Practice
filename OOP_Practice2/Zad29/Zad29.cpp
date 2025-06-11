#include <iostream>
#include <sstream>
#include <cctype>
#include <cstring>
#include "Constant.h"
#include "Read.h"
#include "BinaryOperation.h"
#include "Conditional.h"

Formula* readFormula(std::istream& in)
{
	char token[32];
	in >> token;

	if (strcmp(token, "if") == 0)
	{
		Formula* condition = readFormula(in);

		in >> token;
		if (strcmp(token, "then") != 0)
			throw std::runtime_error("Expected 'then'");

		Formula* thenBranch = readFormula(in);

		in >> token;
		if (strcmp(token, "else") != 0)
			throw std::runtime_error("Expected 'else'");

		Formula* elseBranch = readFormula(in);

		return new Conditional(condition, thenBranch, elseBranch);
	}
	else if (strcmp(token, "Read") == 0)
	{
		return new Read();
	}
	else if (token[0] == '(')
	{
		Formula* left = readFormula(in);

		char op;
		in >> op;

		Formula* right = readFormula(in);

		in >> token;
		if (strcmp(token, ")") != 0)
			throw std::runtime_error("Expected ')'");

		return new BinaryOperation(op, left, right);
	}
	else if (isdigit(token[0]) || token[0] == '-')
	{
		return new Constant(atof(token));
	}
	else
	{
		throw std::runtime_error("Unknown token");
	}
}

Formula* readFormula()
{
	char buffer[256];
	std::cin.getline(buffer, 256);
	std::istringstream iss(buffer);
	return readFormula(iss);
}



int main()
{
	Formula* f;
	f = readFormula();

	std::cout << f->value();

	delete f;
}