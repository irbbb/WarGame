#include "UnitManager.h"
#include "ECS/Components.h"
#include "Constants.h"

extern Manager manager;

UnitManager::UnitManager() {
	unitNames.push_back("tank");
	landUnitNames.push_back("tank");
	units.emplace("tank", new Unit("tank", 20, Unit::land, 3, 2));
	
	landUnitNames.push_back("soldier");
	unitNames.push_back("soldier");
	units.emplace("soldier", new Unit("soldier", 10, Unit::land, 4, 1));
	
	airUnitNames.push_back("helicopter");
	unitNames.push_back("helicopter");
	units.emplace("helicopter", new Unit("helicopter", 10, Unit::air, 6, 3));
}

UnitManager::~UnitManager() {

}

Unit* UnitManager::getUnit(std::string id) {
	return units[id];
}

std::vector<std::string> UnitManager::getAllUnits() {
	return unitNames;
}

std::vector<std::string> UnitManager::getLandUnits() {
	return landUnitNames;
}

std::vector<std::string> UnitManager::getWaterUnits() {
	return waterUnitNames;
}

std::vector<std::string> UnitManager::getAirUnits() {
	return airUnitNames;
}

Entity* UnitManager::createUnit(std::string id, PlayerManager* player, int xTile, int yTile) {
	Entity* unit = &manager.addEntity();

	unit->addComponent<TransformComponent>(xTile * SCALED_TILE_SIZE, yTile * SCALED_TILE_SIZE, 32, 32, 2);
	unit->addComponent<SpriteComponent>(id);
	unit->addComponent<UnitComponent>(units[id], player);
	unit->addComponent<MouseControllerUnit>();
	unit->addGroup(Game::groupUnits);

	return unit;
}