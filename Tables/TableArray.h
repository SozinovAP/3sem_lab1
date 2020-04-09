#pragma once
#include "Table.h"

class TableArray : public Table
{

protected:
	struct RecordArray : public Record
	{
		int id;
		RecordArray()
		{
			id = -1;
		}
		RecordArray(std::string name, Polynomial polynomial, int id):Record(name,polynomial)
		{
			this->id = id;
		}
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
};

