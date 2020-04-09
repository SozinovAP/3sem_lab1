#pragma once

#include <string>
#include <iostream>
#include <cctype>

class Monomial
{
private:
	int coef;
	int powers;

public:
	Monomial(int coef = 0, int powers = 0);
	Monomial(const Monomial& monom);
	Monomial(const std::string &str);

	void SetCoef(int coef)
	{ 
		this->coef = coef; 
	}
	int GetCoef(void) const 
	{
		return coef; 
	}
	void SetPowers(int powers) 
	{ 
		this->powers = powers; 
	}
	int GetPowers(void) const 
	{ 
		return powers; 
	}
	Monomial& operator=(const Monomial &monom);
	int operator==(const Monomial &monom) 
	{
		return powers == monom.powers;
	}
	int operator<(const Monomial &monom) 
	{
		return powers < monom.powers;
	}

	friend std::ostream& operator<<(std::ostream &stream, const Monomial &m)
	{
		if (m.coef == 0) return stream;

		if (m.coef != 1)
		{
			if (m.coef == -1)
				stream << "-";
			else
				stream << m.coef;
		}
		if (m.coef == 1 && m.powers == 0)
		{
			stream << "1";
		}
		if (m.powers / 10000)
		{
			stream << "x";
			if (m.powers / 10000 != 1)
				stream << "^" << m.powers / 10000;
		}
		if (m.powers / 100 % 100)
		{
			stream << "y";
			if (m.powers / 100 % 100 != 1)
				stream << "^" << m.powers / 100 % 100;
		}
		if (m.powers % 10)
		{
			stream << "z";
			if (m.powers % 100 != 1)
				stream << "^" << m.powers % 100;
		}

		return stream;
	}
};

enum class input_exc
{
	wrong_var, wrong_pow, too_large_power, negative_power
};