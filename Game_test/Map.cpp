#include "Map.h"
#include <fstream>
#include "ECS/ECS.h"
#include "ECS/Components.h"

extern Manager manager;

Map::Map(std::string tID, int mapScale, int tileSize) : textureID(tID), mapScale(mapScale), tileSize(tileSize) {
	scaledSize = mapScale * tileSize;
}

Map::~Map(){}

void Map::LoadMap(std::string path, int xSize, int ySize) {
	char c;
	std::fstream mapFile;
	mapFile.open(path);

	int xSrc, ySrc;

	// Each tile is represented by two char, where first is y in tileset and second is x
	for (int y = 0; y < ySize; y++) {
		for (int x = 0; x < xSize; x++) {
			mapFile.get(c);
			ySrc = atoi(&c) * tileSize;
			mapFile.get(c);
			xSrc = atoi(&c) * tileSize;
			AddTile(xSrc, ySrc, x * scaledSize, y * scaledSize);
			// Ignore coma between tiles
			mapFile.ignore();
		}
	}

	mapFile.close();

}

void Map::AddTile(int xSrc, int ySrc, int xPos, int yPos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(xSrc, ySrc, xPos, yPos, tileSize, mapScale, textureID);
	tile.addGroup(Game::groupMap);
}

void Map::freeTile(int xTile, int yTile) {
	occupiedTiles[xTile + yTile * WIDTH_MAP] = 0;
}

bool Map::occupyTile(int xTile, int yTile) {
	if (occupiedTiles[xTile + yTile * WIDTH_MAP] == 0) {
		occupiedTiles[xTile + yTile * WIDTH_MAP] = 1;
		return true;
	}
	return false;

}

bool Map::isTileOccupied(int xTile, int yTile) {
	return occupiedTiles[xTile + yTile * WIDTH_MAP];
}