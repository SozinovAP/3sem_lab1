#pragma once
#include "Tables/Table.h"
#include "List.h"

class TableManager
{
private:
	TList<Table*> tables;

public:

	void Insert(std::string name, Polynomial& rec);
	void Remove(std::string name);
	void Clear();

	int GetCount() const;
	Polynomial* Find(std::string name);
	void Replace(std::string name, Polynomial& polynomial);
	bool IsEmpty() const;

	void Read(std::string pFileName);
	void Write(std::string pFileName);

	void AddTable(Table* table);
	Table* GetTable(int num);
	int GetTablesCount();
};

