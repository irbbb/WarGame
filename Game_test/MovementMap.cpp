#include "MovementMap.h"
#include <fstream>
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include "Game.h"

extern Manager manager;

MovementMap::MovementMap() {
	mapNeedUpdate = false;
}

void MovementMap::LoadMap(std::bitset<HEIGHT_MAP * WIDTH_MAP> bs) {
	auto& movementTiles(manager.getGroup(Game::groupMovementTile));
	for (auto& mt : movementTiles) {
		mt->destroy();
	}
	manager.refresh();

	for (int y = 0; y < HEIGHT_MAP; y++) {
		for (int x = 0; x < WIDTH_MAP; x++) {
			if (bs[x + y * 20] == 1) {
				AddTile(0, 0, x * SCALED_TILE_SIZE, y * SCALED_TILE_SIZE);
			}
		}
	}
}

void MovementMap::AddTile(int xSrc, int ySrc, int xPos, int yPos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(xSrc, ySrc, xPos - Game::camera.x, yPos - Game::camera.y, TILE_SIZE, SCALE, "movementAvailableTile");
	tile.addGroup(Game::groupMovementTile);
}

void MovementMap::mapUpdateRequest() {
	mapNeedUpdate = true;
}

bool MovementMap::isPendingUpdate() {
	return mapNeedUpdate;
}

