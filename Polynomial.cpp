#include "Polynomial.h"
#include <algorithm>
#include <math.h>

using namespace std;

Polynom::Polynom()
{
	name = "";
}


Polynomial::Polynomial(const TList<Monom> &mon, string n)
{
	monoms = mon;
	name = n;
}

Polynom::Polynom(Polynom & p)
{
	monoms = TList<Monom>(p.monoms);
	name = p.name;
}

Polynom& Polynom::operator-(Polynom& p)
{
	Polynom *res = new Polynom(p);
	for (int i = 0; i < (*res).monoms.GetLength(); i++)
		(*res).monoms[i].SetCoef(-(*res).monoms[i].GetCoef());
	for (int i = 0; i < monoms.GetLength(); i++)
	{
		(*res) += monoms[i];
	}
	return *res;
}

Polynom& Polynom::operator+(Polynom & p)
{
	Polynom *res = new Polynom(p);

	for (int i = 0; i < monoms.GetLength(); i++)
	{
		(*res) += monoms[i];
	}
	return *res;
}

Polynom& Polynom::operator=(Polynom & p)
{
	monoms = TList<Monom>(p.monoms);

	return *this;
}

bool Polynom::IsEmpty()
{
	return monoms.IsEmpty();
}

void Polynom::Sort()
{
	monoms.Sort(false);
}

int Polynom::Det(int x, int y, int z)
{
	int sum = 0;
	for (int i = 0; i < monoms.GetLength(); i++)
	{
		sum += monoms[i].GetCoef() * (pow(x, monoms[i].GetPowers() / 10000)) * (pow(y, monoms[i].GetPowers() / 100 % 100)) * (pow(z, monoms[i].GetPowers() % 100));
	}
	return sum;
}

Polynomial& Polynomial::operator+=(const Monom &m)
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

ostream & operator<<(ostream & stream, const Polynom & p)
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

istream & operator>>(istream & stream, Polynom & p)
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
					p += Monom(m);
				m = str[i];
			}
			else
			{
				m += str[i];
			}
		}
	}

	if (m.length() > 0) 
		p += Monom(m);

	return stream;
}

bool Polynom::HasX()
{
	bool x = false;
	for (int i = 0; i < monoms.GetLength(); i++)
		x = x || (monoms[i].GetPowers() / 10000);
	return x;
}

bool Polynom::HasY()
{
	bool y = false;
	for (int i = 0; i < monoms.GetLength(); i++)
		y = y || (monoms[i].GetPowers() / 100 % 100);
	return y;
}

bool Polynom::HasZ()
{
	bool z = false;
	for (int i = 0; i < monoms.GetLength(); i++)
		z = z || (monoms[i].GetPowers() % 100);
	return z;
}

void Polynom::SetName(string n)
{
	name = n;
}

string Polynom::GetName()
{
	return name;
}

Polynom Polynom::Dif(char v)
{
	Polynom res = *this;
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

Polynom Polynom::Integr(char v)
{
	Polynom res = *this;
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
