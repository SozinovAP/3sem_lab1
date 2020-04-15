#include "HashTableList.h"


HashTableList::HashTableList(int msize) : Table()
{
	curList = 0;
	listPos = 0;
	size = msize;
	mas = new list<Record>[size];
}

HashTableList::~HashTableList()
{
	delete[] mas;
}

int HashTableList::hash(std::string name)	//вычисление хеша
{
	int pos = 0;

	for(auto i = 0; i < name.length(); ++i)
	{
		pos += static_cast<int>(name[i]);
	}
	
	return ((name.length() * pos) % size);
}

Record* HashTableList::FindRecord(std::string name)	//поиск записи
{
	Polynomial p;
	Record rec(name, p);

	int i = hash(name);	//индекс
	list<Record>::iterator it = mas[i].begin();
	while(it != mas[i].end())
	{
		if (*it == rec)
			return &(*it);
		++it;
	}
	return nullptr;
}

void HashTableList::Insert(std::string name, Polynomial& polynomial)	//вставка
{
	Record rec(name, polynomial);
	
	if (FindRecord(name) != nullptr)
	{
		throw "Item already exists";
	}
	
	int i = hash(name);
	mas[i].emplace_back(rec);
	DataCount++;
}

void HashTableList::Remove(std::string name)	//удаление
{
	int i = hash(name);
	if (mas[i].empty())
	{
		throw "No elements";
	}
	if (FindRecord(name) == nullptr)
	{
		throw "Item doesn't exists";
	}

	Polynomial pol;
	
	Record rec(name, pol);
	mas[i].erase(find(mas[i].begin(), mas[i].end(), rec));
	DataCount--;
}

void HashTableList::Clear()	//очистка таблицы
{
	delete[] mas;
	DataCount = 0;
	mas = new list<Record>[DataCount];
}

Table::iterator HashTableList::begin()
{
	int i = 0;
	while ((i < size))
	{
		if (!mas[i].empty())
		{
			curList = i;
			listPos = 0;
			return &(*mas[i].begin());
		}
		++i;
	}
	curList = size - 1;
	listPos = mas[size - 1].size() - 1;
	return &(*mas[size - 1].end());
}

Table::iterator HashTableList::end()
{
	int i = size - 1;
	while ((i >= 0))
	{
		if (!mas[i].empty())
		{
			return &(*mas[i].end());
		}

		--i;
	}
	return &(*mas[size - 1].end());
}
