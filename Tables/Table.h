#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <iostream>
#include <fstream>
#include "Polynomial.h"

class Table
{
protected:
	
	//сруктура хранения записи
	class Record
	{
	protected:
		std::string name;
	public:
		Polynomial polynomial;

		Record() {}
		Record(std::string name, Polynomial polynomial);
		std::string GetName();
	};

	int DataCount;//количетсво записей
	virtual Record* FindRecord(std::string name) = 0;
public:
	Table();

	int GetCount() const;												//получить количетсво записей

	virtual void Insert(std::string name, Polynomial& polynomial) = 0;	//вставка записи
	virtual void Remove(std::string name) = 0;							//удаление записи
	virtual void Clear() = 0;											//очистка
	Polynomial* Find(std::string name);									//поиск записи, nullptr если не найдена
	void Replace(std::string name, Polynomial& polynomial);				//замена записи

	//Проверки
	bool IsEmpty() const;							//проверка на пустоту

	//итераторы

	//файлы
	void Read(std::string pFileName);						//чтение из файла
	void Write(std::string pFileName);						//запись в файла

};

#endif TABLE_H