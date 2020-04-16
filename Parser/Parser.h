#pragma once

#include "Formula.h"
#include "../TableManager.h"

static class Parser
{
private:
	static list<Phrase> ToPostfix(list<Phrase> listPhrase);
	static bool BalanceParentheses(list<Phrase> listPhrase);
	static int PriorityOperator(string s);
	static bool IsOperator(string s);
	static void	Calculate(list<Phrase> postfixPhrases);
public:
	
	static void Parse(string str, TableManager manager);
};


 
