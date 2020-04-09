#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <iostream>
#include <fstream>
#include "Polynomial.h"

//сруктура хранения записи





class Table
{
protected:
	
	struct Record
	{
		std::string name;
		Polynomial polynomial;
	};

	int DataCount;//количетсво записей
	virtual Record* FindRecord(std::string name) = 0;
public:
	Table();
	~Table();

	int GetCount() const;						//получить количетсво записей

	Polynomial* Find(std::string name);			//поиск записи, nullptr если не найдена
	virtual void Insert(const Record &rec) = 0;		//вставка записи
	virtual void Remove(std::string name) = 0;		//удаление записи
	virtual void Replace(std::string name, const Polynomial& rec) = 0;		//удаление записи
	
	//Проверки
	bool IsEmpty() const;							//проверка на пустоту

	//итераторы

	//файлы
	void Read(std::string pFileName);						//чтение из файла
	void Write(std::string pFileName);						//запись в файла

};

#endif TABLE_H