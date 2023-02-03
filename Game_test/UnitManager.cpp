#include "UnitManager.h"
#include "ECS/Components.h"
#include "Constants.h"

extern Manager manager;

UnitManager::UnitManager() {
	units.emplace("tank", new Unit("tank", 20, Unit::land, 3));
	units.emplace("soldier", new Unit("soldier", 10, Unit::land, 4));
	units.emplace("helicopter", new Unit("helicopter", 10, Unit::air, 6));
}

UnitManager::~UnitManager() {

}

Unit* UnitManager::getUnit(std::string id) {
	return units[id];
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