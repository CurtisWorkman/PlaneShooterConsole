#include <iostream>
#include <conio.h>
#include <windows.h>

bool gameOver{ false };
int width{ 70 }, height{ 20 };
int planeY, planeX;
int bulletX, bulletY;						//should be integer arrays to allow multiple bullets. Then loop through the arrays to show how many bullets.

enum eDirection
{
	STOP, UP, DOWN, SHOOT
};
eDirection dir;


void Setup()
{
	planeY = height / 2;
	planeX = 15;
}


void Draw()
{
	system("CLS");

	for (int i = 0; i < width; i++)
	{
		std::cout << '#';
	}
	std::cout << '\n';

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
			{
				std::cout << '#';
			}
			else if (i == planeY && j == planeX)
			{
				std::cout << 'O';
			}
			else if (i == bulletY && j == bulletX)				//for loop through all elements in bullet array.
			{
				std::cout << '-';
			}
			else
			{
				std::cout << ' ';
			}
		}
		std::cout << '\n';
	}

	for (int i = 0; i < width; i++)
	{
		std::cout << '#';
	}
	std::cout << '\n';
}

void Input()
{
	if (_kbhit)
	{
		switch (_getch())
		{
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 't':
			bulletX = planeX + 1;						//add to array
			bulletY = planeY;
			break;
		default:
			break;
		}
	}
}

void Logic()
{
	switch (dir)
	{
	case UP:
		if (planeY - 1 == 0)
		{
			break;
		}
		else
		{
			planeY--;
			break;
		}
	case DOWN:
		if (planeY + 1 == height)
		{
			break;
		}
		else
		{
			planeY++;
			break;
		}
	default:
		break;
	}

	bulletX++;										//for loop through all elements of array.
}

int main()
{
	Setup();

	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(100);
	}
	return 0;
}
