#include "BuildingManager.h"
#include "Game.h"
#include "ECS/Components.h"

Entity* BuildingManager::createBuilding(std::string textureId, PlayerManager* player, int xTile, int yTile, Manager* manager) {
	Entity* city = &manager->addEntity();

	city->addComponent<TransformComponent>(xTile * SCALED_TILE_SIZE, yTile * SCALED_TILE_SIZE, 32, 32, 2);
	city->addComponent<SpriteComponent>(textureId);
	city->addComponent<BuildingComponent>(player);
	city->addComponent<MouseControllerBuilding>();
	city->addGroup(Game::groupBuildings);

	return city;
}