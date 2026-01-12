#include <iostream>
#include "Level.h"
#include <conio.h>
#include <Windows.h>

void drawPlayerInfo(int& playerHP, int& maxHP)
{
	std::cout << std::endl << playerHP << "/" << maxHP << std::endl;
}

int main()
{
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);

	int playerHP = 10;
	int maxHP = 10;
	

	std::vector<std::string> levels =
	{
		"levels/level1.txt",
		"levels/level2.txt",
		"levels/level3.txt"
	};

	int currentLevel = 0;

	Level level;
	level.showPrologue("levels/prologue.txt");
	level.loadFromFile(levels[currentLevel]);

	int playerX = level.playerStartX;
	int playerY = level.playerStartY;

	while (true)
	{
		system("cls");
		level.drawWithPlayer(playerX, playerY);
		drawPlayerInfo(playerHP, maxHP);

		bool enemy = false;
		if (level.getTile(playerX + 1, playerY) == 'E')
		{
			enemy = true;
		}
		if (level.getTile(playerX - 1, playerY) == 'E')
		{
			enemy = true;
		}
		if (level.getTile(playerX, playerY + 1) == 'E')
		{
			enemy = true;
		}
		if (level.getTile(playerX, playerY - 1) == 'E')
		{
			enemy = true;
		}

		char input = _getch();
		if (input == 'q')
		{
			break;
		}
		
		int xx = 0, yy = 0;
		if (input == 'w')
		{
			yy = -1;
		}
		if (input == 's')
		{
			yy = 1;
		}
		if (input == 'a')
		{
			xx = -1;
		}
		if (input == 'd')
		{
			xx = 1;
		}

		if (input == 'f')
		{
			if (enemy)
			{
				if (level.getTile(playerX + 1, playerY) == 'E')
				{
					level.setTile(playerX + 1, playerY, '.');
				}
				if (level.getTile(playerX - 1, playerY) == 'E')
				{
					level.setTile(playerX - 1, playerY, '.');
				}
				if (level.getTile(playerX, playerY + 1) == 'E')
				{
					level.setTile(playerX, playerY + 1, '.');
				}
				if (level.getTile(playerX, playerY - 1) == 'E')
				{
					level.setTile(playerX, playerY - 1, '.');
				}
			}
			if (enemy)
			{
				playerHP -= 1;
			}
		}

		int newX = playerX + xx;
		int newY = playerY + yy;

		if (newX < 0 || newX >= level.getWidth())
		{
			continue;
		}
		if (newY < 0 || newY >= level.getHeight()) 
		{ 
			continue;
		}

		if (level.getTile(newX, newY) == '#')
		{
			continue;
		}

		playerX = newX;
		playerY = newY;

		char tile = level.getTile(playerX, playerY);
		if (tile == '>')
		{
			++currentLevel;

			if (currentLevel >= levels.size())
			{
				std::cout << "ты прошел игру" << std::endl;
				break;
			}

			level.loadFromFile(levels[currentLevel]);
			playerX = level.playerStartX;
			playerY = level.playerStartY;
		}

		if (tile == '^')
		{
			--playerHP;
		}

		if (playerHP <= 0)
		{
			system("cls");
			std::cout << "ты умер..." << std::endl;
			_getch();
			break;
		}
		
		if (tile == 'E')
		{
			playerHP -= 2;
		}

		if (tile == '+')
		{
			playerHP += 3;
			if (playerHP > maxHP)
			{
				playerHP = maxHP;
				level.setTile(playerX, playerY, '.');
			}
		}

		
	}


	setlocale(LC_ALL, "Russian");
	return 0;
}
