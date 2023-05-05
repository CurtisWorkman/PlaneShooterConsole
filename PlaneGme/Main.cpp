#include <iostream>
#include <conio.h>
#include <windows.h>

bool gameOver;
int width{ 40 }, height{ 17 };
int planeY, planeX;
int enemyY, enemyX;
int bulletX [10], bulletY [10];						//need to find way to make an array with 0 size, and append array every shoot.
int bulletNum{ 0 };
bool isDead;

enum eDirection
{
	STOP = 0, LEFT, RIGHT, SHOOT
};
eDirection dir;
eDirection prevDir;

void Setup()
{
	gameOver = false;
	isDead = false;
	planeY = 15;
	planeX = width / 2;
	enemyY = 2;
	enemyX = width / 2;
}

bool DrawBullet(int i, int j)
{
	for (int k = 0; k < sizeof(bulletX) / sizeof(int); k++)
	{
		if (j == bulletX[k] && i == bulletY[k])
		{
			std::cout << '|';
			return true;
		}
	}
	return false;
} 

bool DrawEnemy(int i, int j)
{
	if (i == enemyY && j == enemyX)
	{
		std::cout << 'o';
		return true;
	}
	else if (i == enemyY && j == enemyX + 1)
	{
		std::cout << '>';
		return true;
	}
	else if (i == enemyY && j == enemyX + 2)
	{
		std::cout << '>';
		return true;;
	}
	else if (i == enemyY && j == enemyX - 1)
	{
		std::cout << '<';
		return true;
	}
	else if (i == enemyY && j == enemyX - 2)
	{
		std::cout << '<';
		return true;
	}
	else
	{
		return false;
	}
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
			bool foundBullet = DrawBullet(i, j);

			bool foundEnemy = false;
			if (!foundBullet && !isDead)
			{
				foundEnemy = DrawEnemy(i, j);
			}

			if (!foundBullet && !foundEnemy)
			{
				if (j == 0 || j == width - 1)
				{
					std::cout << '#';
				}
				else if (i == planeY && j == planeX)
				{
					std::cout << 'O';
				}
				else if (i == planeY && j == planeX - 1)
				{
					std::cout << '<';
				}
				else if (i == planeY && j == planeX + 1)
				{
					std::cout << '>';
				}
				else if (i == planeY + 1 && j == planeX)
				{
					std::cout << '^';
				}
				else
				{
					std::cout << ' ';
				}
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
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			prevDir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			prevDir = RIGHT;
			break;
		case ' ':
			dir = SHOOT;
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
	case LEFT:
		if (planeX - 2 == 0)
		{
			break;
		}
		else
		{
			planeX--;
			break;;
		}
	case RIGHT:
		if (planeX + 3  == width)
		{
			break;
		}
		else
		{
			planeX++;
			break;
		}
	case SHOOT:
		dir = prevDir;
		bulletX[bulletNum] = planeX;						//add to array
		bulletY[bulletNum] = planeY - 1;
		bulletNum++;
		break;
	}

	for (int k = 0; k < sizeof(bulletX) / sizeof(int); k++)
	{
		bulletY[k] = bulletY[k] - 2;
		if (bulletY[k] == enemyY && bulletX[k] == enemyX)
		{
			isDead = true;
		}
	}															//for loop through all elements of array.
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
