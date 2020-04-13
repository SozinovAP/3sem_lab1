#include "Polynomial.h"
#include <algorithm>
#include <math.h>

using namespace std;

Polynomial::Polynomial()
{
}

Polynomial::Polynomial(const TList<Monomial> &mon)
{
	monomials = mon;
}

Polynomial::Polynomial(Polynomial & p)
{
	monomials = TList<Monomial>(p.monomials);
}

Polynomial::Polynomial(string s)
{
	Polynomial p;

	int f = 0;
	while ((f = s.find(" ", f)) != string::npos)
	{
		s.erase(f, 1);
	}

	f = 0;
	while ((f = s.find("+-", f)) != string::npos)
	{
		s.erase(f, 1);
	}

	f = 0;
	while ((f = s.find("*", f)) != string::npos)
	{
		s.erase(f, 1);
	}

	string m = "";

	for (int i = 0; i < s.length(); i++)
	{
		if (m.length() == 0 && s[i] == '-')
		{
			m += s[i];
			i++;
			m += s[i];
		}
		else
		{
			if (s[i] == '-' || s[i] == '+')
			{
				if (m.length() > 1 || (m[i] != '-' && m[i] != '+'))
					monomials.Push_Back(Monomial(m));
				m = s[i];
			}
			else
			{
				m += s[i];
			}
		}
	}

	if (m.length() > 0)
		monomials.Push_Back(Monomial(m));
	this->Sort();
}

Polynomial& Polynomial::operator-(Polynomial& p)
{
	Polynomial *res = new Polynomial(p);
	for (int i = 0; i < (*res).monomials.GetLength(); i++)
		(*res).monomials[i].SetCoef(-(*res).monomials[i].GetCoef());
	for (int i = 0; i < monomials.GetLength(); i++)
	{
		(*res) += monomials[i];
	}
	return *res;
}

Polynomial& Polynomial::operator+(Polynomial & p)
{
	Polynomial *res = new Polynomial(p);

	for (int i = 0; i < monomials.GetLength(); i++)
	{
		(*res) += monomials[i];
	}
	return *res;
}

Polynomial& Polynomial::operator=(Polynomial & p)
{
	monomials = TList<Monomial>(p.monomials);
	this->Sort();
	return *this;
}

bool Polynomial::operator==(Polynomial & p)
{
	if (monomials.GetLength() != p.monomials.GetLength())
		return false;
	for (int i = 0; i < monomials.GetLength(); i++)
	{
		if (monomials[i] != p.monomials[i])
			return false;
	}

	return true;
}

bool Polynomial::operator!=(Polynomial & p)
{
	if (monomials.GetLength() != p.monomials.GetLength())
		return true;
	for (int i = 0; i < monomials.GetLength(); i++)
	{
		if (monomials[i] != p.monomials[i])
			return true;
	}

	return false;
}

bool Polynomial::IsEmpty()
{
	return monomials.IsEmpty();
}

void Polynomial::Sort()
{
	monomials.Sort(false);
}

int Polynomial::Det(int x, int y, int z)
{
	int sum = 0;
	for (int i = 0; i < monomials.GetLength(); i++)
	{
		sum += monomials[i].GetCoef() * (pow(x, monomials[i].GetPowers() / 10000)) * (pow(y, monomials[i].GetPowers() / 100 % 100)) * (pow(z, monomials[i].GetPowers() % 100));
	}
	return sum;
}

Polynomial& Polynomial::operator+=(const Monomial &m)
{
	for (int i = 0; i < monomials.GetLength(); i++)
	{
		if (monomials[i].GetPowers == m.GetPowers)
		{
			monomials[i].SetCoef(monomials[i].GetCoef() + m.GetCoef());
			return *this;
		}
	}
	monomials.Push_Back(m);
	this->Sort();
	return *this;
}

ostream & operator<<(ostream & stream, const Polynomial & p)
{
	return (stream << p.ToStr());
}

istream & operator>>(istream & stream, Polynomial & p)
{
	p.monomials.Clear();
	string str;
	getline(stream, str);
	Polynomial tmp(str);
	p = tmp;
	p.Sort();
	return stream;
}

bool Polynomial::HasX()
{
	bool x = false;
	for (int i = 0; i < monomials.GetLength(); i++)
		x = x || (monomials[i].GetPowers() / 10000);
	return x;
}

bool Polynomial::HasY()
{
	bool y = false;
	for (int i = 0; i < monomials.GetLength(); i++)
		y = y || (monomials[i].GetPowers() / 100 % 100);
	return y;
}

bool Polynomial::HasZ()
{
	bool z = false;
	for (int i = 0; i < monomials.GetLength(); i++)
		z = z || (monomials[i].GetPowers() % 100);
	return z;
}

Polynomial Polynomial::Dif(char v)
{
	Polynomial res = *this;
	int p;
	//if (v == 'x' || v == 'X')
	v = abs((v % 32) - 26); // x=2   y=1    z=0
	p = pow(100, v);
	for (int i = 0; i < monomials.GetLength(); i++)
	{
		res.monomials[i].SetCoef(res.monomials[i].GetCoef() * (res.monomials[i].GetPowers() / p % 100));
		res.monomials[i].SetPowers(res.monomials[i].GetPowers() - 1 * pow(100, v));
	}
	return res;
}

Polynomial Polynomial::Integr(char v)
{
	Polynomial res = *this;
	int p;
	//if (v == 'x' || v == 'X')
	v = abs((v % 32) - 26); // x=2   y=1    z=0
	p = pow(100, v);
	for (int i = 0; i < monomials.GetLength(); i++)
	{
		res.monomials[i].SetCoef(res.monomials[i].GetCoef() / (res.monomials[i].GetPowers() / p % 100 + 1));
		res.monomials[i].SetPowers(res.monomials[i].GetPowers() + 1 * pow(100, v));
	}
	return res;
}

int Polynomial::GetMonomialsCount()
{
	return monomials.GetLength();
}

string Polynomial::ToStr() const
{
	string s;
	for (int i = 0; i < monomials.GetLength(); i++)
	{
		if (i > 0)
		{
			s += " ";
			if (monomials[i].GetCoef() > 0)
				s += "+";
		}

		s += monomials[i].toStr();
	}
	return s;
}
