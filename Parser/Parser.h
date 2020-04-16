#pragma once

#include "Formula.h"
#include "../TableManager.h"

static class Parser
{
private:
	static string ToPostfix(string);
	static bool IsFormula(string formula);
	static string GetFormula(string name);
public:
	
	static void Parse(string str, TableManager manager);
};
