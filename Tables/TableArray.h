#pragma once
#include "Table.h"

class TableArray : public Table
{

protected:
	class RecordArray : public Record
	{
	public:
		int id;
		RecordArray();
		RecordArray(std::string name, Polynomial polynomial, int id);
	};

	Record* FindRecord(std::string name) override;
private:
	RecordArray* records;
	int length;
public:
	TableArray(int startLength=0);
	~TableArray();

	void Insert(std::string name, Polynomial& rec) override;
	void Remove(std::string name) override;
	void Clear() override;
};

