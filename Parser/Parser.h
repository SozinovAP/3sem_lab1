#pragma once

#include "Formula.h"
#include "../TableManager.h"

static class Parser
{
private:
	static string ToPostfix(list<Phrase> listPhrase);
	static string GetFormula(string name);
	static bool BalanceParentheses(list<Phrase> listPhrase);
	static int PriorityOperator(string s);
	static bool IsOperator(string s);
public:
	
	static void Parse(string str, TableManager manager);
};

 
