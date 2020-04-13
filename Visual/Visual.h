#pragma once
#include <string>
#include "TConsole.h"
#include "../TableManager.h"


class Visual
{
private:
	
	enum class menus
	{
		Formula,
		DeletePolynom,
		SaveToFile,
		LoadFromFile,
		Exit,
		menusCount
	};

	std::string menuStrings[(int)menus::menusCount] = {
		"Ввести формулу",
		"Удалить полином",
		"Сохранить в файл",
		"Загрузить из файла",
		"Выйти"
	};
	char allowedChars[11]{' ','=','+','-','*','^','.','(',')','\'',','};

	TConsole console;
	int tableXPos;
	Vector2i consoleSize;

	

	menus curMenuPos;

	bool OnMenuPressed();
	void InputOnMenu();
	void DrawMenu();

	std::string InputStr(std::string info);

	TableManager tableManager;
public:
	Visual(TableManager& tableManager);
	
	void UpdatePolynoms();

	

};

