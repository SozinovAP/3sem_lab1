#include "Polynomial.h"
#include <algorithm>
#include <math.h>

using namespace std;

Polynomial::Polynomial()
{
	name = "";
}

Polynomial::Polynomial(const TList<Monomial> &mon, string n)
{
	monomials = mon;
	name = n;
}

Polynomial::Polynomial(Polynomial & p)
{
	monomials = TList<Monomial>(p.monomials);
	name = p.name;
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

	return *this;
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
		if (monomials[i] == m)
		{
			monomials[i].SetCoef(monomials[i].GetCoef() + m.GetCoef());
			return *this;
		}
	}
	monomials.Push_Back(m);
	return *this;
}

ostream & operator<<(ostream & stream, const Polynomial & p)
{
	for (int i = 0; i < p.monomials.GetLength(); i++)
	{
		if (i > 0)
		{
			stream << " ";
			if (p.monomials[i].GetCoef() > 0)
				stream << "+";
		}

		stream << p.monomials[i];
	}
	return stream;
}

istream & operator>>(istream & stream, Polynomial & p)
{
	p.monomials.Clear();
	string str;
	getline(stream, str);

	int f=0;
	while ((f = str.find(" ", f)) != string::npos)
	{
		str.erase(f, 1);
	}

	f = 0;
	while ((f = str.find("+-", f)) != string::npos)
	{
		str.erase(f, 1);
	}

	f = 0;
	while ((f = str.find("*", f)) != string::npos)
	{
		str.erase(f, 1);
	}

	string m = "";

	for (int i = 0; i < str.length(); i++)
	{
		if (m.length() == 0 && str[i] == '-')
		{
			m += str[i];
			i++;
			m += str[i];
		}
		else
		{
			if (str[i] == '-' || str[i] == '+')
			{
				if (m.length() > 1 || (m[i] != '-' && m[i] != '+'))
					p += Monomial(m);
				m = str[i];
			}
			else
			{
				m += str[i];
			}
		}
	}

	if (m.length() > 0) 
		p += Monomial(m);

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

void Polynomial::SetName(string n)
{
	name = n;
}

string Polynomial::GetName()
{
	return name;
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
