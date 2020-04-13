#include "Visual/Visual.h"
#include "Tables/TableArray.h"
#include "Tables/TableTreeAVL.h"

#include<iostream>
using namespace std;


int main()
{
	TableManager tableManager;
	TableTreeAVL ta;
	tableManager.AddTable(&ta);
	Visual visual(tableManager);
}