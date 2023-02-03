#include "BuildingManager.h"
#include "Game.h"
#include "ECS/Components.h"

Entity* BuildingManager::createBuilding(std::string textureId, PlayerManager* player, int xTile, int yTile, Manager* manager) {
	Entity* city = &manager->addEntity();

	city->addComponent<TransformComponent>(xTile * SCALED_TILE_SIZE, yTile * SCALED_TILE_SIZE, 32, 32, 2);
	city->addComponent<SpriteComponent>(textureId);
	city->addComponent<BuildingComponent>(player, getType(textureId));
	city->addComponent<MouseControllerBuilding>();
	city->addGroup(Game::groupBuildings);

	return city;
}

Unit::type BuildingManager::getType(std::string textureId) {
	if (textureId == "city") {
		return Unit::land;
	}
	if (textureId == "airport") {
		return Unit::air;
	}
	if (textureId == "port") {
		return Unit::water;
	}
	return Unit::land;
}

std::vector<std::string> BuildingManager::getValidUnitsToGenerate(Unit::type type) {
	switch (type) {
	case Unit::land:
		return Game::unitManager->getLandUnits();
	case Unit::air:
		return Game::unitManager->getAirUnits();
	case Unit::water:
		return Game::unitManager->getWaterUnits();
	}
	return *(new std::vector<std::string>());
}