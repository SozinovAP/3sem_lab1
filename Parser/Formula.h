#ifndef FORMULA
#define FORMULA
#include <string>
#include "../Polynomial.h"
#include <list>
#include "Phrase.h"

using namespace std;

class Formula
{
private:

	string inputFormula;

public:

	Formula(string str)
	{
		this->inputFormula = str;
	}
	list<Phrase> Parse()
	{
		string str = inputFormula;

		list<Phrase> phrases;

		string prevPhrase;
		for (int i = 0; i < str.length(); i++)
		{
			int j;

			bool itsSign = false;
			std::string signStr;

			for (j = 0; j < (int)SignType::signsCount; j++)
			{
				signStr = Phrase::signStrs[j];
				if (str.length()-i >= signStr.length() && str.substr(i, signStr.length()) == signStr)
				{
					itsSign = true;
					break;
				}
			}

			
			if (!itsSign && str[i] != ' ')
			{
				prevPhrase += str[i];
			}

			if (itsSign || str[i] == ' ' || i + 1 == str.length())
			{
				if (prevPhrase != "")
				{
					phrases.push_back(Phrase(PhraseType::str, prevPhrase));
					prevPhrase = "";
				}
			}

			if (itsSign)
			{
				phrases.push_back(Phrase(PhraseType::sign, signStr));
				i += signStr.length() - 1;
			}

		}
		
		
		return phrases;
	}

};

#endif FORMULA