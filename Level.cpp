#include "Level.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <synchapi.h>

void Level::showPrologue(const std::string& filename)
{
	system("cls");
	std::ifstream file(filename);
	std::string line;

	while (std::getline(file, line))
	{
		std::cout << line << std::endl;
	}
	file.close();

	std::cout << std::endl << "нажмите любую кнопку для продолжения...";
	_getch();

}

bool Level::loadFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cout << "ошибка в чтении файла: " << filename << std::endl;
		return false;
	}

	map.clear();
	std::string line;

	while (std::getline(file, line))
	{
		map.push_back(line);
	}

	file.close();

	height = map.size();
	width = map[0].size();
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (map[y][x] == '@')
			{
				playerStartX = x;
				playerStartY = y;
				map[y][x] = '.';
			}
		}
	}
	return true;
}

void Level::draw() const
{
	for (int i = 0; i < map.size(); ++i)
	{
		std::string row = map[i];
		std::cout << row << std::endl;
	}
	
}

void Level::drawWithPlayer(int playerX, int playerY) const
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (x == playerX && y == playerY)
			{
				std::cout << '@';
			}
			else
			{
				std::cout << map[y][x];
			}
		}
		std::cout << std::endl;
	}
}

char Level::getTile(int x, int y) const
{
	return map[y][x];
}

void Level::setTile(int x, int y, char tile)
{
	map[y][x] = tile;
}

int Level::getWidth() const
{
	return width;
}

int Level::getHeight() const
{
	return height;
}
