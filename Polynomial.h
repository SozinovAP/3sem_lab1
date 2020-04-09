#pragma once
#include "Monomial.h"
#include "list.h"
using namespace std;

class Polynom
{
private:
	TList<Monom> monoms;
	string name;

public:
	Polynomial();
	Polynomial(const TList<Monom> &mon, string n);
	Polynomial(Polynomial& p);

	Polynomial& operator-(Polynomial& p);
	Polynomial& operator+(Polynomial& p);
	Polynomial& operator+=(const Monom &m);
	Polynomial& operator=(Polynomial & p);

	friend std::ostream & operator<<(std::ostream & stream, const Polynom &p);
	friend std::istream & operator>>(std::istream & stream, Polynom & p);

	bool HasX();
	bool HasY();
	bool HasZ();
	bool IsEmpty();
	void Sort();
	int Det(int x, int y, int z);
	void SetName(string n);
	string GetName();
	Polynom Dif(char v);
	Polynom Integr(char v);
};