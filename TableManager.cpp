#include "TableManager.h"


void TableManager::Insert(std::string name, Polynomial& rec)
{
	for (int i = 0; i < tables.GetLength(); i++)
	{
		tables.Get(i)->Insert(name, rec);
	}
}

void TableManager::Remove(std::string name)
{
	for (int i = 0; i < tables.GetLength(); i++)
	{
		tables.Get(i)->Remove(name);
	}
}

void TableManager::Clear()
{
	for (int i = 0; i < tables.GetLength(); i++)
	{
		tables.Get(i)->Clear();
	}
}

int TableManager::GetCount() const
{
	if (tables.GetLength() == 0)
	{
		return 0;
	}
	int first = tables.Get(0)->GetCount();
	for (int i = 1; i < tables.GetLength(); i++)
	{
		if (first != tables.Get(i)->GetCount())
		{
			throw "Table getcount returns not equal values";
		}
	}

	return first;
}

Polynomial* TableManager::Find(std::string name)
{
	if (tables.GetLength() == 0)
	{
		return nullptr;
	}
	Polynomial* first = tables.Get(0)->Find(name);
	for (int i = 1; i < tables.GetLength(); i++)
	{
		if (*first != *tables.Get(i)->Find(name))
		{
			throw "Table finds returns not equal values";
		}
	}

	return first;
}

void TableManager::Replace(std::string name, Polynomial& polynomial)
{
	for (int i = 0; i < tables.GetLength(); i++)
	{
		tables.Get(i)->Replace(name, polynomial);
	}
}

bool TableManager::IsEmpty() const
{
	if (tables.GetLength() == 0)
	{
		return true;
	}
	bool first = tables.Get(0)->IsEmpty();
	for (int i = 1; i < tables.GetLength(); i++)
	{
		if (first != tables.Get(i)->IsEmpty())
		{
			throw "Table isemptys returns not equal values";
		}
	}

	return first;
}

void TableManager::Read(std::string pFileName)
{
	
}

void TableManager::Write(std::string pFileName)
{
	int lastPointPos = pFileName.find_last_of('.');
	string extention = ".txt";
	if (lastPointPos != -1)
	{
		extention = lastPointPos == -1 ? ".txt" : pFileName.substr(lastPointPos);
		pFileName = pFileName.substr(0, lastPointPos);
	}
	for (int i = 0; i < tables.GetLength(); i++)
	{
		string className = typeid(*tables.Get(i)).name();
		className.replace(className.find("class "), 6, "");
		tables.Get(i)->Write(pFileName + "." + className + extention);
	}
}

void TableManager::AddTable(Table* table)
{
	tables.Push_Back(table);
}

Table* TableManager::GetTable(int num)
{
	return tables.Get(num);
}

int TableManager::GetTablesCount()
{
	return tables.GetLength();
}