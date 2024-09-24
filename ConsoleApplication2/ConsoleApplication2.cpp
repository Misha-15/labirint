#include <iostream>
#include <windows.h> 
#include <conio.h>
using namespace std;


enum KeyCodes { ENTER = 13, ESCAPE = 27, LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80, SPACEBAR = 32 };
enum Colors { DARKGREEN = 2, RED = 12, YELLOW = 14, BLUE = 9 };
enum Objects { HALL, WALL, COIN, ENEMY };


int main()
{
	int coins = 0;

	system("title ЛАБИРИНТ!");
	srand(time(0));
	rand();


	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 100;
	SetConsoleCursorInfo(h, &info);

	const int WIDTH = 50;
	const int HEIGHT = 15;
	int location[HEIGHT][WIDTH] = {};


	for (int y = 0; y < HEIGHT; y++) 
	{
		for (int x = 0; x < WIDTH; x++) 
		{
			location[y][x] = rand() % 4; 

			
			if (x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1)
				location[y][x] = WALL;

			
			if (x == 0 && y == 2 || x == WIDTH - 1 && y == HEIGHT - 3)
				location[y][x] = HALL;

			if (location[y][x] == ENEMY) {
				int prob = rand() % 10; 
				if (prob != 0) 
					location[y][x] = HALL;
			}
		}
	}

	for (int y = 0; y < HEIGHT; y++) 
	{
		for (int x = 0; x < WIDTH; x++)
		{
			switch (location[y][x]) {
			case HALL: 
				cout << " ";
				break;
			case WALL: 
				SetConsoleTextAttribute(h, DARKGREEN);
				cout << (char)177; 
				break;
			case COIN: 
				SetConsoleTextAttribute(h, YELLOW);
				cout << (char)15; 
				break;
			case ENEMY: 
				SetConsoleTextAttribute(h, RED);
				cout << (char)1;
				break;
			default:
				cout << location[y][x];
				break;
			}
		}
		cout << "\n";
	}
	COORD position;
	position.X = 1;
	position.Y = 2;
	SetConsoleCursorPosition(h, position);
	SetConsoleTextAttribute(h, BLUE);
	cout << (char)1;
	while (true) {
		int code = _getch(); 
		if (code == 224)
			code = _getch(); 
		SetConsoleCursorPosition(h, position);
		SetConsoleTextAttribute(h, BLUE);
		cout << " ";

		switch (code) {
		case ENTER:
			break;
		case SPACEBAR:
			break;
		case ESCAPE:
			break;
		case RIGHT:
			if (location[position.Y][position.X + 1] != WALL)
				position.X++;
			break;
		case LEFT:
			if (position.X > 0 || location[position.Y][position.X - 1] != WALL)
				position.X--;
			break;
		case UP:
			break;
		case DOWN:
			break;
		default:
			cout << code << "\n";
			break;
		}

		SetConsoleCursorPosition(h, position);
		SetConsoleTextAttribute(h, BLUE);
		cout << (char)1;

		if (location[position.Y][position.X] == COIN) {
			coins++;
			cout << coins << "\n";
			location[position.Y][position.X] = HALL;
		}
	}
}