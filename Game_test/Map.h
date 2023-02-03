#pragma once

#include "Game.h"
#include <string>
#include <bitset>
#include "Constants.h"


class Map {
public:
	Map(std::string tID, int mapScale, int tileSize);
	~Map();

	void LoadMap(std::string path, int xSize, int ySize);
	void AddTile(int xSrc, int ySrc, int xPos, int yPos);
	void freeTile(int xTile, int yTile);
	bool occupyTile(int xTile, int yTile);
	bool isTileOccupied(int xTile, int yTile);

private:
	std::string textureID;
	std::bitset<HEIGHT_MAP * WIDTH_MAP> occupiedTiles;
	int mapScale;
	int tileSize;
	int scaledSize;
};