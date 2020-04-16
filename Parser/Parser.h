#ifndef PARSER
#define PARSER

#include "Phrase.h"
#include "Formula.h"

using namespace std;

class Parser
{
private:
	string formula;
	string postfix;

public:
	Parser();
	Parser(string formula);

	string ToPostfix();
	bool IsFormula(string formula);
	string GetFormula(string name);
};

#endif PARSER