#ifndef PHRASE
#define PHRASE

#include <string>
#include "../Monomial.h"

enum class PhraseType
{
	str,
	sign
};

enum class SignType
{
	plus,
	minus,
	equal,
	multiply,
	bracketopen,
	bracketclose,
	integral,
	signsCount
};

struct Phrase
{
	static const std::string signStrs[(int)SignType::signsCount];

	PhraseType phraseType;
	std::string str;

	Phrase(PhraseType phraseType, std::string str="")
	{
		this->phraseType = phraseType;
		this->str = str;
	}

};

#ifndef PhraseCpp
#define PhraseCpp

const std::string Phrase::signStrs[(int)SignType::signsCount] = { "+","-","=","*","(",")","integral" };
#endif//TODO: !PhraseCpp

#endif PHRASE