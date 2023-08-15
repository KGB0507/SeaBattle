/////////////////////////////////////////////////////////////////////////////
//Sea Battle (Console game) v. 1.2
/////////////////////////////////////////////////////////////////////////////
//Copyright (c) Kirill Belozerov, 2022-2023. All Rights Reserved
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//Notes: yFire = y - 1, xFire = x - 1
/////////////////////////////////////////////////////////////////////////////

#define _CRT_SECURE_NO_WARNINGS
//#define DEBUG 1.2


#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>

const int N = 8;
const int NUMBEROFSHIPS = 5;


#pragma comment(lib, "winmm.lib")

using std::cout;
using std::endl;
using std::cin;


//COLOR:
//BLACK = 0
//BLUE = 1
//GREEN = 2
//CYAN = 3
//RED = 4
//PURPLE = 5
//YELLOW = 6
//WHITE = 7
//GRAY = 8
//LIGHTBLUE = 9
//LIGHTGREEN = 10
//LIGHTCYAN = 11
//LIGHTRED = 12
//LIGHTPURPLE = 13
//LIGHTYELLOW = 14
//LIGHTWHITE = 15

enum column
{
	A = 0,
	B = 1,
	C = 2,
	D = 3,
	E = 4,
	F = 5,
	G = 6,
	H = 7,
	I = 8,
	J = 9
};

void SetColor(int text, int bg)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}


int main()
{
	setlocale(LC_ALL, "rus");

	//iXFire, iYFire - inputed coordinates
	//xFire, yFire - transformed to the int type coordinates
	//x, y - variables for cycles (internal program logic)
	int x, y, xFire, yFire, count = 0, numberOfShots = 0;
	bool gameOver = false;

	//creating and initialization of the map
	int map[N][N];
	for (x = 0; x < N; x++)
	{
		for (y = 0; y < N; y++)
		{
			map[x][y] = 0;
		}
	}

	srand(time(NULL));
	//generating randomly placed ships (single-decked only)
	for (x = 0; x < N; x++)
	{
		for (y = 0; y < N; y++)
		{
			//checking other ships nearly this coordinates
			
			//fix warnings 
			if (map[x][y - 1] != 1 && map[x][y + 1] != 1 && map[x - 1][y] != 1 && map[x + 1][y] != 1 && map[x - 1][y - 1] != 1 && map[x + 1][y + 1] != 1 && map[x + 1][y - 1] != 1 && map[x - 1][y + 1] != 1)
			{
				map[x][y] = rand() % 2;
				if (map[x][y] == 1)
				{
					count++;
					if (count == NUMBEROFSHIPS)
					{
						break;
					}
				}
			}
			/////////////////
		}
		if (count == NUMBEROFSHIPS)
		{
			break;
		}
	}
	//making fire on the selected coordinates
	while (!gameOver)
	{
#ifndef DEBUG
		mciSendString(L"play music\\background.mp3", NULL, 0, NULL);
#endif
		//printing the map
		cout << endl << "    ";
		for (int i = 0; i < N; i++)
		{
			cout << i + 1 << " ";
		}

		cout << endl;

		for (int x = 0; x < N; x++)
		{
			cout << "  " << x + 1 << " ";
			for (int y = 0; y < N; y++)
			{
				switch (map[x][y])
				{
				case -2:
				{
					SetColor(9, 0);
					cout << "* "; // water shpash 
					SetColor(7, 0);
					break;
				}
				case -1:
				{
					SetColor(8, 0);
					cout << "@ "; // sinked ship
					SetColor(7, 0);
					break;
				}
				case 0:
				{
					SetColor(9, 0);
					cout << "~ "; // water
					SetColor(7, 0);
					break;
				}
				case 1:
				{
#ifndef DEBUG
					SetColor(9, 0);
					cout << "~ "; // ship
					SetColor(7, 0);
#else
					SetColor(7, 0);
					cout << "0 ";
					SetColor(7, 0);
#endif
					break;
				}
				}
			}
			cout << endl;
		}

		cout << endl <<endl;

		switch (count)
		{
		case 1:
		{
			cout << "Осталось " << count << " корабль" << endl;
			break;
		}
		case 2:
		{
			cout << "Осталось " << count << " корабля" << endl;
			break;
		}
		case 3:
		{
			cout << "Осталось " << count << " корабля" << endl;
			break;
		}
		case 4:
		{
			cout << "Осталось " << count << " корабля" << endl;
			break;
		}
		default:
		{
			cout << "Осталось " << count << " кораблей" << endl;
			break;
		}
		}


		cout << "Введите координаты для выстрела через пробел: ";
		cin >> xFire >> yFire;
		/*int inputColor{};
		std::cin >> inputColor;

		auto color{static_cast<Color>(inputColor) };*/
		/*switch (iYFire)
		{
		case "a":
		{
		}
		case "b":
		{
		}
		case "c":
		{
		}
		case "d":
		{
		}
		case E:
		{
		}
		case F:
		{
		}
		case G:
		{
		}
		case H:
		{
		}
		case I:
		{
		}
		case J:
		{
		}
		}*/
		if (xFire > N || xFire < 1 || yFire > N || yFire < 1)
		{
			system("cls");
			continue;
		}
		numberOfShots++;
		if (map[xFire - 1][yFire - 1] == 1)
		{
			map[xFire - 1][yFire - 1] = -1;
			count--;
			mciSendString(L"play music\\explosion.mp3 wait", NULL, 0, NULL);
			if (xFire == N && yFire == N)
			{
				for (x = xFire - 2; x <= xFire - 1; x++)
				{
					for (y = yFire - 2; y <= yFire - 1; y++)
					{
						if (map[x][y] != -1)
							map[x][y] = -2;
						if (x == xFire - 1 && y == yFire - 1)
							map[x][y] = -1;
					}
				}
			}
			else if (xFire == N) 
			{
				for (x = xFire - 2; x <= xFire - 1; x++)
				{
					for (y = yFire - 2; y <= yFire; y++)
					{
						if (map[x][y] != -1)
							map[x][y] = -2;
						if (x == xFire - 1 && y == yFire - 1)
							map[x][y] = -1;
					}
				}
			}
			else if (yFire == N) 
			{
				for (x = xFire - 2; x <= xFire; x++)
				{
					for (y = yFire - 2; y <= yFire - 1; y++)
					{
						if (map[x][y] != -1)
							map[x][y] = -2;
						if (x == xFire - 1 && y == yFire - 1)
							map[x][y] = -1;
					}
				}
			}
			else if (xFire == 1 && yFire == 1)
			{
				for (x = xFire - 1; x <= xFire; x++)
				{
					for (y = yFire - 1; y <= yFire; y++)
					{
						if (map[x][y] != -1)
							map[x][y] = -2;
						if (x == xFire - 1 && y == yFire - 1)
							map[x][y] = -1;
					}
				}
			}
			else 
			{
				for (x = xFire - 2; x <= xFire; x++)
				{
					for (y = yFire - 2; y <= yFire; y++)
					{
						if (map[x][y] != -1)
							map[x][y] = -2;
						if (x == xFire - 1 && y == yFire - 1)
							map[x][y] = -1;
					}
				}
			}
			if (count == 0)
				gameOver = true;
		}
		else
		{
			map[xFire - 1][yFire - 1] = -2;
			mciSendString(L"play music\\splash.mp3 wait", NULL, 0, NULL);
		}
		system("cls");
	}

	mciSendString(L"play music\\win.mp3", NULL, 0, NULL);
	cout << "Вы выиграли! Количество выстрелов: " << numberOfShots << endl;
	system("pause");
	return 0;
}