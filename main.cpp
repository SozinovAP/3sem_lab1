#include "Visual/Visual.h"
#include "Tables/TableArray.h"
#include "Tables/TableTreeAVL.h"

#include<iostream>

#include "Tables/HashTableList.h"
using namespace std;


int main()
{
	Polynomial pol("xyz");
	HashTableList tn(10);
	tn.Insert("1", pol);
	tn.Insert("2", pol);
	tn.Insert("3", pol);
	HashTableList::iterator it = nullptr;
	cout << tn.begin()->GetName() << endl;
	//cout << tn.end()->GetName();
	/*for (it = tn.begin(); it != tn.end(); ++it)
	{
		cout << it->GetName() << endl;
	}*/
	int i;
	cin >> i;
	TableManager tableManager;
	TableTreeAVL ta;
	tableManager.AddTable(&ta);
	Visual visual(tableManager);

	Polynomial p("xyz");
	Polynomial p2("xy^2");
	tableManager.Insert("a", p);
	tableManager.Insert("b", p2);

	tableManager.Write("a.txt");

}