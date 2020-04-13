#include "Visual.h"
#include <conio.h>
#include <algorithm>

#define COMMAND_KEYS 224
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DELETE 83

#define KEY_TAB 9
#define KEY_ENTER 13
#define KEY_SPACE 32
#define KEY_BACKSPACE 8

using namespace std;


string Visual::InputStr(string info)
{
	int argNum = 0;
	cout << info << ": ";
	int startX = console.WhereX();

	string result = "";

	while (true)
	{
		int input = _getch();
		if (input == COMMAND_KEYS)
		{
			int arrow = _getch();
			if (arrow == KEY_LEFT)
			{
				int whereX = console.WhereX();
				if (whereX > startX)
				{
					console.GotoXY(whereX - 1, console.WhereY());
				}
			}
			else if (arrow == KEY_RIGHT)
			{
				int whereX = console.WhereX();
				if (whereX < startX+result.length())
				{
					console.GotoXY(whereX + 1, console.WhereY());
				}
			}
			else if (arrow == KEY_DELETE)
			{
				int erasePos = console.WhereX() - startX;
				if (erasePos < result.length())
				{
					result.erase(erasePos, 1);
					int whereX = console.WhereX();
					cout << result.substr(erasePos) << ' ';
					console.GotoXY(whereX, console.WhereY());
				}
			}
		}
		else if (input == KEY_TAB)
		{
			int curPos = console.WhereX() - startX;
			string leftStr = result.substr(0, curPos);
			int argNum = count(leftStr.begin(), leftStr.end(), ' ') + 1;
			int argStart = leftStr.find_last_of(' ') + 1;

			string arg = result.substr(argStart, curPos - argStart);
		}
		else if (input == KEY_ENTER)
		{
			console.GotoXY(0, console.WhereY());
			console.ClrEol();
			return result;
		}
		else if (input == KEY_BACKSPACE)
		{
			int erasePos = console.WhereX() - startX;
			if (erasePos > 0)
			{
				result.erase(erasePos-1, 1);
				int whereX = console.WhereX() - 1;
				console.GotoXY(whereX, console.WhereY());
				cout << result.substr(erasePos-1) << ' ';
				console.GotoXY(whereX, console.WhereY());
			}
		}
		else if (isalpha(input) || isdigit(input) || std::find(std::begin(allowedChars), std::end(allowedChars), input) != std::end(allowedChars))
		{
			char inputChar = (char)input;
			int insertPos = console.WhereX() - startX;
			result.insert(insertPos, 1, inputChar);
			int whereX = console.WhereX();
			cout << result.substr(insertPos);
			console.GotoXY(whereX + 1, console.WhereY());
		}
	}
	
	throw "Must not be there";
}

bool Visual::OnMenuPressed()
{
	switch (curMenuPos)
	{
	case menus::Formula:
		console.GotoXY(0, consoleSize.y - 1);
		{
			string str = InputStr("¬ведите формулу");
			//Formula f(str);
			//f.Parse();
		}
		break;
	case menus::DeletePolynom:

		console.GotoXY(0, consoleSize.y - 1);
		{
			string str = InputStr("¬ведите им€ полинома");
		}

		break;
	case menus::SaveToFile:
		break;
	case menus::LoadFromFile:
		break;
	case menus::Exit:
		return true;
	default:
		break;
	}
	return false;
}

void Visual::InputOnMenu()
{
	int c = _getch();
	int arrow;
	bool exit = false;
	switch (c)
	{
	case KEY_ENTER:
		exit = OnMenuPressed();
		break;
	case COMMAND_KEYS:
		arrow = _getch();
		switch (arrow)
		{
		case KEY_DOWN:
			curMenuPos = (menus)(((int)curMenuPos + 1) % (int)menus::menusCount);
			DrawMenu();
			break;
		case KEY_UP:
			curMenuPos = (menus)(((int)curMenuPos + (int)menus::menusCount - 1) % (int)menus::menusCount);
			DrawMenu();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
	if (!exit)
	{
		InputOnMenu();
	}
}

Visual::Visual(TableManager& tableManager)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//console.Window(120, 50);
	consoleSize = console.GetWindowSize();

	tableXPos = (int)(consoleSize.x * 2.0 / 3.0);
	console.GotoXY(0, consoleSize.y-1);

	curMenuPos = (menus)0;

	this->tableManager = tableManager;

	UpdatePolynoms();
	DrawMenu();

	InputOnMenu();
}

void Visual::UpdatePolynoms()
{
	Vector2i lastPos = console.Where();
	bool wasLVertical = console.IsLVertical();
	bool wasUnderscore = console.IsUnderscore();

	console.SetUnderscore(false);
	for (int i = 0; i <= consoleSize.y; i++)
	{
		console.GotoXY(tableXPos, i);
		if (i == consoleSize.y)
		{
			console.SetUnderscore(true);
		}
		console.SetLVertical(true);
		//cout first symbol
		cout << "a";
		console.SetLVertical(false);
		//cout others
		cout << "bcd";
	}
	console.SetLVertical(wasLVertical);
	console.SetUnderscore(wasUnderscore);
	console.GotoXY(lastPos);
}

void Visual::DrawMenu()
{
	Vector2i lastPos = console.Where();
	Colors prevTextColor = console.GetTextColor();
	Colors prevBackgroundColor = console.GetBackgroundColor();
	for (int i = 0; i < (int)menus::menusCount; i++)
	{
		console.GotoXY(0, i);
		console.SetBackgroundColor((int)curMenuPos == i ? Colors::COLOR_WHITE : Colors::COLOR_BLACK);
		console.SetTextColor((int)curMenuPos == i ? Colors::COLOR_BLACK : Colors::COLOR_WHITE);

		cout << i << "." << menuStrings[i] << ".";
	}
	console.SetBackgroundColor(prevBackgroundColor);
	console.SetTextColor(prevTextColor);
	console.GotoXY(lastPos);
}






