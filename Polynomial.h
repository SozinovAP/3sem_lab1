#pragma once
#include "Monomial.h"
#include "list.h"
using namespace std;

class Polynomial
{
private:
	TList<Monomial> monoms;
	string name;

public:
	Polynomial();
	Polynomial(const TList<Monomial> &mon, string n);
	Polynomial(Polynomial& p);

	Polynomial& operator-(Polynomial& p);
	Polynomial& operator+(Polynomial& p);
	Polynomial& operator=(Polynomial & p);

	friend std::ostream & operator<<(std::ostream & stream, const Polynomial &p);
	friend std::istream & operator>>(std::istream & stream, Polynomial & p);

	bool HasX();
	bool HasY();
	bool HasZ();
	bool IsEmpty();
	void Sort();
	int Det(int x, int y, int z);
	void AddMonom(const Monomial &m);
	void SetName(string n);
	string GetName();
	Polynomial Dif(char v);
	Polynomial Integr(char v);
};