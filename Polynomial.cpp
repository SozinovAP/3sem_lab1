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
	monoms = mon;
	name = n;
}

Polynomial::Polynomial(Polynomial & p)
{
	monoms = TList<Monomial>(p.monoms);
	name = p.name;
}

Polynomial& Polynomial::operator-(Polynomial& p)
{
	Polynomial *res = new Polynomial(p);
	for (int i = 0; i < (*res).monoms.GetLength(); i++)
		(*res).monoms[i].SetCoef(-(*res).monoms[i].GetCoef());
	for (int i = 0; i < monoms.GetLength(); i++)
	{
		(*res).AddMonom(monoms[i]);
	}
	return *res;
}

Polynomial& Polynomial::operator+(Polynomial & p)
{
	Polynomial *res = new Polynomial(p);

	for (int i = 0; i < monoms.GetLength(); i++)
	{
		(*res).AddMonom(monoms[i]);
	}
	return *res;
}

Polynomial& Polynomial::operator=(Polynomial & p)
{
	monoms = TList<Monomial>(p.monoms);

	return *this;
}

bool Polynomial::IsEmpty()
{
	return monoms.IsEmpty();
}

void Polynomial::Sort()
{
	monoms.Sort(false);
}

int Polynomial::Det(int x, int y, int z)
{
	int sum = 0;
	for (int i = 0; i < monoms.GetLength(); i++)
	{
		sum += monoms[i].GetCoef() * (pow(x, monoms[i].GetPowers() / 10000)) * (pow(y, monoms[i].GetPowers() / 100 % 100)) * (pow(z, monoms[i].GetPowers() % 100));
	}
	return sum;
}

void Polynomial::AddMonom(const Monomial &m)
{
	for (int i = 0; i < monoms.GetLength(); i++)
	{
		if (monoms[i] == m)
		{
			monoms[i].SetCoef(monoms[i].GetCoef() + m.GetCoef());
			return;
		}
	}
	monoms.Push_Back(m);
}

ostream & operator<<(ostream & stream, const Polynomial & p)
{
	for (int i = 0; i < p.monoms.GetLength(); i++)
	{
		if (i > 0)
		{
			stream << " ";
			if (p.monoms[i].GetCoef() > 0)
				stream << "+";
		}

		stream << p.monoms[i];
	}
	return stream;
}

istream & operator>>(istream & stream, Polynomial & p)
{
	p.monoms.Clear();
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
					p.AddMonom(Monomial(m));
				m = str[i];
			}
			else
			{
				m += str[i];
			}
		}
	}

	if (m.length() > 0) 
		p.AddMonom(Monomial(m));

	return stream;
}

bool Polynomial::HasX()
{
	bool x = false;
	for (int i = 0; i < monoms.GetLength(); i++)
		x = x || (monoms[i].GetPowers() / 10000);
	return x;
}

bool Polynomial::HasY()
{
	bool y = false;
	for (int i = 0; i < monoms.GetLength(); i++)
		y = y || (monoms[i].GetPowers() / 100 % 100);
	return y;
}

bool Polynomial::HasZ()
{
	bool z = false;
	for (int i = 0; i < monoms.GetLength(); i++)
		z = z || (monoms[i].GetPowers() % 100);
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
	for (int i = 0; i < monoms.GetLength(); i++)
	{
		res.monoms[i].SetCoef(res.monoms[i].GetCoef() * (res.monoms[i].GetPowers() / p % 100));
		res.monoms[i].SetPowers(res.monoms[i].GetPowers() - 1 * pow(100, v));
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
	for (int i = 0; i < monoms.GetLength(); i++)
	{
		res.monoms[i].SetCoef(res.monoms[i].GetCoef() / (res.monoms[i].GetPowers() / p % 100 + 1));
		res.monoms[i].SetPowers(res.monoms[i].GetPowers() + 1 * pow(100, v));
	}
	return res;
}
