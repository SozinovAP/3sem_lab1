#pragma once
#include "Monomial.h"
#include "list.h"
using namespace std;

class Polynomial
{
private:
	TList<Monomial> monomials;

public:
	Polynomial();
	Polynomial(const TList<Monomial> &mon);
	Polynomial(Polynomial& p);
	Polynomial(string s);

	Polynomial& operator-(Polynomial& p);
	Polynomial& operator+(Polynomial& p);
	Polynomial& operator+=(const Monomial &m);
	Polynomial& operator=(Polynomial & p);

	friend ostream & operator<<(ostream & stream, const Polynomial &p);
	friend istream & operator>>(istream & stream, Polynomial & p);

	string ToStr() const;
	bool HasX();
	bool HasY();
	bool HasZ();
	bool IsEmpty();
	void Sort();
	int Det(int x, int y, int z);
	Polynomial Dif(char v);
	Polynomial Integr(char v);
	int GetMonomialsCount();
};