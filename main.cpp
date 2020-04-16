#include "Visual/Visual.h"
#include "Tables/TableArray.h"
#include "Tables/TableTreeAVL.h"
#include<iostream>
#include "Parser/Parser.h"

using namespace std;


int main()
{
	/*TableManager tableManager;
	TableTreeAVL ta;
	tableManager.AddTable(&ta);
	Visual visual(tableManager);

	Polynomial p("xyz");
	Polynomial p2("xy^2");
	tableManager.Insert("a", p);
	tableManager.Insert("b", p2);
	
	tableManager.Write("a.txt");*/
	string str;
	TableManager sa;
	getline(cin, str);
	Parser::Parse(str, sa);

	
}