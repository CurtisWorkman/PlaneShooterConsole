#include <iostream>
#include <conio.h>
#include <windows.h>

bool gameOver;
int score;
int width{ 40 }, height{ 17 };
int planeY, planeX;
int enemyY, enemyX;
int bulletX [10], bulletY [10];						//need to find way to make an array with 0 size, and append array every shoot.
int bulletNum{ 0 };
int enemyBulletX[10], enemyBulletY[10];						//need to find way to make an array with 0 size, and append array every shoot.
int enemyBulletNum{ 0 };
bool isEnemyDead;
int enemyShootWaitCounter;
int enemyDeadWaitCounter;
int enemySpawn;
int playerHealth;

enum eDirection
{
	STOP = 0, LEFT, RIGHT, SHOOT
};
eDirection dir;
eDirection prevDir;

enum eEnemyDirection
{
	ESTOP = 0, ELEFT, ERIGHT, ESHOOT
};
eEnemyDirection enemyDir;

void Setup()
{
	srand((int)time(0));
	gameOver = false;
	isEnemyDead = false;
	planeY = 15;
	planeX = width / 2;
	enemyY = 2;
	enemySpawn = rand() % 21 + 8;
	enemyX = enemySpawn;
	enemyDir = ERIGHT;
	enemyShootWaitCounter = 0;
	playerHealth = 3;
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

bool DrawEnemyBullet(int i, int j)
{
	for (int k = 0; k < sizeof(enemyBulletX) / sizeof(int); k++)
	{
		if (j == enemyBulletX[k] && i == enemyBulletY[k])
		{
			std::cout << '|';
			return true;
		}
	}
	return false;
}

bool DrawPlane(int i, int j)
{
	if (i == planeY && j == planeX)
	{
		std::cout << 'O';
		return true;
	}
	else if (i == planeY && j == planeX - 1)
	{
		std::cout << '<';
		return true;
	}
	else if (i == planeY && j == planeX + 1)
	{
		std::cout << '>';
		return true;
	}
	else if (i == planeY + 1 && j == planeX)
	{
		std::cout << '^';
		return true;
	}
	else
	{
		return false;
	}
}

void DrawGrid(int i, int j)
{
	if (j == 0 || j == width - 1)
	{
		std::cout << '#';
	}
	else
	{
		std::cout << ' ';
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
			bool foundObject = DrawBullet(i, j);

			if (!foundObject && !isEnemyDead)
			{
				foundObject = DrawEnemy(i, j);
			}

			if (!foundObject)
			{
				foundObject = DrawEnemyBullet(i, j);
			}

			if (!foundObject)
			{
				foundObject = DrawPlane(i, j);
			}

			if (!foundObject)
			{
				DrawGrid(i, j);
			}
		}
		std::cout << '\n';
	}

	for (int i = 0; i < width; i++)
	{
		std::cout << '#';
	}
	std::cout << '\n';
	std::cout << '\n';
	std::cout << "Score: " << score;
	std::cout << '\n';
	std::cout << '\n';
	for (int i = 0; i < playerHealth; i++)
	{
		std::cout << 'H';
	}
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

void EnemyAI()
{
	if (!isEnemyDead)
	{
		if (enemyX >= enemySpawn + 4)
		{
			enemyDir = ELEFT;
		}
		else if (enemyX <= enemySpawn - 4)
		{
			enemyDir = ERIGHT;
		}

		if (++enemyShootWaitCounter == 8)
		{
			enemyBulletX[enemyBulletNum] = enemyX;						//add to array
			enemyBulletY[enemyBulletNum] = enemyY + 1;
			if (++enemyBulletNum > 10)
			{
				enemyBulletNum = 0;
			}
			enemyShootWaitCounter = 0;
		}

		switch (enemyDir)
		{
		case ELEFT:
			enemyX--;
			break;
		case ERIGHT:
			enemyX++;
			break;
		default:
			break;
		}
	}
	else
	{
		if (++enemyDeadWaitCounter == 8)
		{
			enemySpawn = rand() % 21 + 8;
			isEnemyDead = false;
			enemyDeadWaitCounter = 0;
		}
	}

	for (int k = 0; k < sizeof(enemyBulletX) / sizeof(int); k++)
	{
		enemyBulletY[k] = enemyBulletY[k] + 2;
		if (enemyBulletY[k] == planeY && (enemyBulletX[k] == planeX || enemyBulletX[k] == planeX - 1 || enemyBulletX[k] == planeX + 1))
		{
			playerHealth--;
			if (playerHealth == 0)
			{
				gameOver = true;
			}
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
		if (++bulletNum > 10)
		{
			bulletNum = 0;
		}
		break;
	}

	for (int k = 0; k < sizeof(bulletX) / sizeof(int); k++)
	{
		bulletY[k] = bulletY[k] - 2;
		if (bulletY[k] == enemyY && (bulletX[k] == enemyX || bulletX[k] == enemyX + 1 || bulletX[k] == enemyX + 2 || bulletX[k] == enemyX - 1 || bulletX[k] == enemyX - 2))
		{
			isEnemyDead = true;
			score = score + 10;
		}
	}

	EnemyAI();

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
	system("CLS");
	std::cout << "Score: " << score << '\n';
	std::cout << R"(   _____          __  __ ______    ______      ________ _____  _ 
  / ____|   /\   |  \/  |  ____|  / __ \ \    / /  ____|  __ \| |
 | |  __   /  \  | \  / | |__    | |  | \ \  / /| |__  | |__) | |
 | | |_ | / /\ \ | |\/| |  __|   | |  | |\ \/ / |  __| |  _  /| |
 | |__| |/ ____ \| |  | | |____  | |__| | \  /  | |____| | \ \|_|
  \_____/_/    \_\_|  |_|______|  \____/   \/   |______|_|  \_(_))";
	Sleep(5000);
	return 0;
}
