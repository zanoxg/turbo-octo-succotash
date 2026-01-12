#pragma once
#include <vector>
#include <string>

class Level {
public:
	void showPrologue(const std::string& filename);
	
	bool loadFromFile(const std::string& filename);
	void draw() const;

	void drawWithPlayer(int playerX, int playerY) const;

	char getTile(int x, int y) const;
	void setTile(int x, int y, char tile);

	int getWidth() const;
	int getHeight() const;

	int playerStartX;
	int playerStartY;

private:
	std::vector<std::string> map;
	int width = 0;
	int height = 0;
};