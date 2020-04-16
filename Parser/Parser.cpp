#include "Parser.h"
#include <stack>

list<Phrase> Parser::ToPostfix(list<Phrase> listPhrase)
{
	stack<Phrase> stackPhrase;
	list<Phrase> postfix;

	if (!BalanceParentheses(listPhrase))
		throw "uncorrect";
	bool F = true;
	for (auto it = listPhrase.begin(); it != listPhrase.end(); ++it)
	{
		//cout << (*it).str << endl;
		if (it->str == "integral")
		{
			postfix.emplace_back(*it);
		}
		else if ((IsOperator(it->str)) || (it->str == "("))
		{
			if(F)
			{
				F = false;
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
						postfix.emplace_back(stackPhrase.top());
						stackPhrase.pop();
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
			}
			while (stackPhrase.top().str != "(")
			{
				postfix.emplace_back(stackPhrase.top());
				stackPhrase.pop();
			}
			stackPhrase.pop();
		}
		else
		{
			postfix.emplace_back(*it);
			F = true;
		}
	}

	while (!stackPhrase.empty())
	{
		postfix.emplace_back(stackPhrase.top());
		stackPhrase.pop();
	}
	return postfix;
}

bool Parser::BalanceParentheses(list<Phrase> listPhrase)
{
	if (listPhrase.empty())
		throw "phrase is empty";
	stack<char> check;
	auto it = listPhrase.begin();
	//поиск 1-ой скобки, если она закрывающаяся, то расстановка не корректна
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

	//если верхняя скобка открывающаяся, то расстановка некорректна
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

void Parser::Parse(string str, Table* manager)
{
	Formula formula(str);
	list<Phrase> listPhrases = formula.Parse();
	for (auto it = listPhrases.begin(); it != listPhrases.end(); ++it)
		cout << (*it).str << endl;
	//проверка на существование знака '=', интеграла или дифференциала
	auto it = listPhrases.begin();
	bool Flag = true;
	int countSigh = 0;
	while ((it != listPhrases.end()) && (Flag))
	{
		if (it->str == "=")
		{
			Flag = false;
		}
		else if (IsOperator(it->str))
		{
			countSigh++;
		}
		++it;
		if (it->str == "integral")
		{
			
		}
	}
	//если есть знак "="
	if (!Flag)
	{
		//если перед "=" есть операторы +-*/
		if (countSigh > 0)
			throw "uncorrect";
		CreateRecord(listPhrases, manager);
	}
	else
	{
		list<Phrase> postfixPhrase = ToPostfix(listPhrases);
	}
	
}

int Parser::PriorityOperator(string s)
{
	if (s == "(")
	{
		return 0;
	}
	else if (s == ")")
	{
		return 1;
	}
	else if ((s == "+") || (s == "-"))
	{
		return 2;
	}
	else if ((s == "/") || (s == "*"))
	{
		return 3;
	}
	else
		throw "uncorrect symbol";
}

bool Parser::IsOperator(string s)
{
	string oper = "+-*/";
	return (oper.find(s) == -1) ? false : true;
}

string Parser::Calculate(list<Phrase> postfixPhrases, Table* manager)
{
	string str = "";
	bool F = true;
	stack<Polynomial> tmpOperand;
	Polynomial tmp;
	auto it = postfixPhrases.begin();
	while ((++it) != postfixPhrases.end())
	{
		if (IsOperator(it->str))
		{
			bool Oper1find = false;
			bool Oper2find = false;
			Polynomial Oper1, Oper2;
			if (!tmpOperand.empty())
			{
				
				Oper2 = *manager->Find(tmpOperand.top().ToStr());;
				tmpOperand.pop();
				Oper2find = true;
			}
			if (!tmpOperand.empty())
			{
				Oper1 = *manager->Find(tmpOperand.top().ToStr());;
				tmpOperand.pop();
				Oper1find = true;
			}
			if (!(Oper1find && Oper2find))
				throw "False";
			if(it->str == "+")
			{
				tmp = Oper1 + Oper2;
			}
			else if(it->str == "-")
			{
				tmp = Oper1 - Oper2;
			}
			else if (it->str == "*")
			{
				//tmp = Oper1 * Oper2;
			}
			tmpOperand.push(tmp);
		}
	}
	Polynomial* pol = manager->Find(it->str);
	if (pol == nullptr)
	{
		if (IsOperator(it->str))
		{
			postfixPhrases.emplace_back(*it);
		}
		else
		{
			try
			{
				Polynomial pol2(it->str);
			}
			catch (...)
			{
				throw "cannot be converted to polynomial and no entry in the table";
			}
		}
	}
	return str;
}

string Parser::Dif(list<Phrase> phrase, char x)
{
	string res = "";
	phrase = ToPostfix(phrase);
	
	return res;
}

string Parser::Int(list<Phrase> phrase, char x)
{
	string res = "";
	phrase = ToPostfix(phrase);

	return res;
}

void Parser::CreateRecord(list<Phrase> listPhrases, Table* manager)
{
	list<Phrase> phrase;
	string name = "";
	auto it = listPhrases.begin();
	while (it->str != "=")
	{
		name += it->str;
		name += " ";
		++it;
	}

	while((++it) != listPhrases.end())
	{
		phrase.emplace_back(*it);
	}
	
	phrase = ToPostfix(phrase);
	string poly = Calculate(phrase, manager);
	Polynomial p(poly);
	
	manager->Insert(name, p);
}
