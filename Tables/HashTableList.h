#ifndef HASH_TABLE_LIST
#define HASH_TABLE_LIST

#include "Table.h"
#include <list>

using namespace std;


class HashTableList : public Table
{
private:
	list<Record>* mas;
	int size;
	int curList;
	int listPos;
	int hash(std::string name);	//вычисление хеша

public:
	
	HashTableList(int msize = 25);
	~HashTableList();

	Record* FindRecord(std::string name) override;	//поиск записи

	void Insert(std::string name, Polynomial& polynomial) override;	//вставка
	void Remove(std::string name) override;	//удаление
	void Clear() override;	//очистка таблицы

	//итераторы
	iterator begin();
	iterator end();

};

#endif HASH_TABLE_LIST
