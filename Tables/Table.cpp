#include "Table.h"

using namespace std;

Table::Record::Record(std::string name, Polynomial polynomial)
{
	this->name = name;
	this->polynomial = polynomial;
}
string Table::Record::GetName()
{
	return name;
}

Table::Table()
{
	DataCount = 0;
}

int Table::GetCount() const			//получить количетсво записей
{
	return DataCount;
}

Polynomial* Table::Find(string name)
{
	Record* result = FindRecord(name);
	return (result == nullptr ? nullptr : &(result->polynomial));
}
void Table::Replace(std::string name, Polynomial& polynomial)
{
	Record* result = FindRecord(name);
	if (result == nullptr)
	{
		throw "Item for replace not found";
	}

	result->polynomial = polynomial;
}


bool Table::IsEmpty() const				//проверка на пустоту
{
	return (DataCount == 0);
}

void Table::Read(string pFileName)
{
	ifstream file;
	file.open(pFileName);

	if (!file.fail())
	{
		while (!file.eof())
		{
			//TODO: чтение из файла 
		}
		file.close();
	}
	else cout << "File does not exist" << endl;
}

void Table::Write(string pFileName)
{
	ofstream file;
	file.open(pFileName);

	//TODO: запись в файл
		
	file.close();
}