#pragma once
#include "Table.h"

class TableTreeAVL:public Table
{
protected:
	class RecordTreeAVL : public Record
	{
	private:
		RecordTreeAVL* parent;
		RecordTreeAVL* leftChild;
		RecordTreeAVL* rightChild;
	public:
		int heightDiff;//left heght-right height

		RecordTreeAVL();
		RecordTreeAVL(std::string name, Polynomial polynomial);

		void SetChild(RecordTreeAVL* child, bool left);
		RecordTreeAVL* GetChild(bool left);
		RecordTreeAVL* GetParent();
		void Rotate(bool leftChild);
		bool isLeftChild;
	};

	RecordTreeAVL head;
	int height = 0;

	Record* FindRecord(std::string name) override;
	bool Balance(RecordTreeAVL* record);
	void Remove(RecordTreeAVL* record);
	void Clear(RecordTreeAVL* start);
private:
	const bool firstRecordLeft = true;
public:
	~TableTreeAVL();

	void Insert(std::string name, Polynomial& rec) override;
	void Remove(std::string name) override;
	void Clear() override;

	int GetHeight();
};

