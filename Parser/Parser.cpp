#include "Parser.h"


Parser::Parser()
{
	formula = "";
	postfix = "";
}

Parser::Parser(string formula)
{
	if (IsFormula(formula))
	{
		this->formula = formula;
	}
	else
	{
		this->formula = GetFormula(formula);
	}

	this->postfix = ToPostfix();	
}
	

string Parser::ToPostfix()
{
	string tmp = formula;
	return tmp;
}

bool Parser::IsFormula(string formula)
{
	return true;
}

string Parser::GetFormula(string name)
{
	string tmp = "";
	return tmp;
}
