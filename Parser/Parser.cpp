#include "Parser.h"
#include <stack>

string Parser::ToPostfix(list<Phrase> listPhrase)
{
	stack<Phrase> stackPhrase;
	string postfix = "";

	if (!BalanceParentheses(listPhrase))
		throw "uncorrect";
	bool F = true;
	for (auto it = listPhrase.begin(); it != listPhrase.end(); ++it)
	{
		//cout << (*it).str << endl;
		if (it->str == "integral")
		{
			postfix += "integral ";
		}
		else if ((IsOperator(it->str)) || (it->str == "("))
		{
			if(F)
			{
				F = false;
				postfix += " ";
			}
			if((stackPhrase.empty()) || (it->str == "("))
			{
				stackPhrase.push(*it);
			}
			else
			{
				if (Parser::PriorityOperator(it->str) > Parser::PriorityOperator(stackPhrase.top().str))
				{
					stackPhrase.push(*it);
				}
				else
				{
					while ((!stackPhrase.empty()) && (Parser::PriorityOperator(stackPhrase.top().str)) >= Parser::PriorityOperator(it->str))
					{
						postfix += stackPhrase.top().str;
						stackPhrase.pop();
						postfix += " ";
					}
					stackPhrase.push(*it);
				}
			}
		}
		else if (it->str == ")")
		{
			if (F)
			{
				F = false;
				postfix += " ";
			}
			while (stackPhrase.top().str != "(")
			{
				postfix += stackPhrase.top().str;
				stackPhrase.pop();
				postfix += " ";
			}
			stackPhrase.pop();
		}
		else
		{
			postfix += it->str;
			F = true;
		}
	}

	postfix += " ";
	while (!stackPhrase.empty())
	{
		postfix += stackPhrase.top().str;
		stackPhrase.pop();
		postfix += " ";
	}
	return postfix;
}


string Parser::GetFormula(string name)
{
	string tmp = "";
	return tmp;
}

bool Parser::BalanceParentheses(list<Phrase> listPhrase)
{
	if (listPhrase.empty())
		throw "list is empty";
	stack<char> check;
	auto it = listPhrase.begin();
	//поиск 1-ой скобки, если она закрывающа€с€, то расстановка не корректна
	while((it != listPhrase.end()) && (check.empty()))
	{
		if ((*it).str == "(")
		{
			check.push('(');
		}
		else if ((*it).str == ")")
		{
			return false;
		}
		++it;
	}
	//добавление всех скобок в стек
	while((it != listPhrase.end()))
	{
		if ((*it).str == "(")
		{
			check.push('(');
		}
		else if ((*it).str == ")")
		{
			check.push(')');
		}
		++it;
	}

	//если верхн€€ скобка открывающа€с€, то расстановка некорректна
	if ((!check.empty()) && (check.top() == '('))
		return false;
	int count = 0;
	//проверка баланса скобок
	while (!check.empty())
	{
		char c = check.top();
		if (c == ')')
		{
			count--;
		}
		else
		{
			count++;
		}
		check.pop();
	}
	return (count == 0) ? true : false;
}

void Parser::Parse(string str, TableManager manager)
{
	Formula formula(str);
	list<Phrase> listPhrases = formula.Parse();
	string s = Parser::ToPostfix(listPhrases);
	for (auto it = listPhrases.begin(); it != listPhrases.end(); ++it)
	{
		cout << (*it).str << endl;
		//if (true)
	}
	cout << s;
}

int Parser::PriorityOperator(string s)
{
	if (s == "(")
		return 0;
	else if (s == ")")
		return 1;
	else if ((s == "+") || (s == "-"))
		return 2;
	else if ((s == "/") || (s == "*"))
		return 3;
}

bool Parser::IsOperator(string s)
{
	string oper = "+-*/";
	return (oper.find(s) == -1) ? false : true;
}
