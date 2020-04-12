#include "TableArray.h"

TableArray::RecordArray::RecordArray()
{
	id = -1;
}
TableArray::RecordArray::RecordArray(std::string name, Polynomial polynomial, int id):Record(name, polynomial)
{
	this->id = id;
}

Table::Record* TableArray::FindRecord(std::string name)
{
	for (size_t i = 0; i < DataCount; i++)
	{
		if (records[i].GetName() == name)
		{
			return (records+i);
		}
	}

	return nullptr;
}

TableArray::TableArray(int startLength)
{
	length = startLength;
	records = new RecordArray[length];
}

TableArray::~TableArray()
{
	delete[] records;
}

void TableArray::Insert(std::string name, Polynomial& polynomial)
{
	RecordArray* foundRecord = (RecordArray*)FindRecord(name);

	if (foundRecord != nullptr)
	{
		throw "Item already exists";
	}

	
	if (DataCount < length)
	{
		RecordArray tmp(name, polynomial, DataCount);
		records[DataCount] = tmp;
		DataCount++;
	}
	else
	{
		// if DataCount==length update records
		RecordArray* newRecords = new RecordArray[length+1];
		for (int i=0; i < length; i++)
		{
			newRecords[i] = records[i];
		}
		RecordArray tmp(name, polynomial, length);
		newRecords[length] = tmp;
		length++;
		DataCount++;
		delete[] records;
		records = newRecords;
	}
}

void TableArray::Remove(std::string name)
{
	RecordArray* foundRecord = (RecordArray*)FindRecord(name);
	if (foundRecord == nullptr)
	{
		throw "Item doesn't exist";
	}

	int stId = foundRecord->id;
	DataCount--;
	for (int i = stId; i < DataCount; i++)
	{
		records[i] = records[i + 1];
		records[i].id = i;
	}
	
}

void TableArray::Clear()
{
	delete[] records;
	DataCount = 0;
	length = 0;
	records = new RecordArray[length];
	
}
