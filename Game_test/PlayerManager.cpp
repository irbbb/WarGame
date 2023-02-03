#include "PlayerManager.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include <sstream>
#include "MovementMap.h"

extern Manager manager;

PlayerManager::PlayerManager(){
	player = &manager.addEntity();
	uiManager = new UIManager();
	selectedUnit = nullptr;
}

void PlayerManager::createPlayer() {
	player->addComponent<TransformComponent>(384, 320, 32, 32, 2);
	player->addComponent<SpriteComponent>("player");
	player->addComponent<MouseControllerPlayer>();
	player->addComponent<KeyboardController>(this);
	player->addGroup(Game::groupPlayers);
}

void PlayerManager::createUI() {
	SDL_Color white = { 255, 255, 255 };
	uiManager->addText("Pos", 10, 10, "Text", "arial", white);
}

void PlayerManager::updateUI() {
	std::stringstream ss;

	if (selectedUnit != nullptr) {
		ss << "Player selected unit: " << selectedUnit->getComponent<UnitComponent>().name;
		ss << ", Health: " << selectedUnit->getComponent<UnitComponent>().health; 
		ss << ", Movement range: " << selectedUnit->getComponent<UnitComponent>().movementRange;
		ss << ", Building: " << selectedUnit->getComponent<UnitComponent>().building;
	}
	else {
		ss << "Player selected unit: None";
	}

	uiManager->updateUiText("Pos", ss.str());
}

void PlayerManager::addUnit(std::string textureID, int xTile, int yTile, void* building) {
	Entity* unit = Game::unitManager->createUnit(textureID, this, xTile, yTile);
	
	unit->getComponent<UnitComponent>().setBuilding((BuildingComponent*)building);

	units.emplace_back(unit);
}

void PlayerManager::addBuilding(std::string id, int xTile, int yTile) {

	Entity* city = &manager.addEntity();

	city->addComponent<TransformComponent>(xTile * SCALED_TILE_SIZE, yTile * SCALED_TILE_SIZE, 32, 32, 2);
	city->addComponent<SpriteComponent>(id);
	city->addComponent<BuildingComponent>(this);
	city->addComponent<MouseControllerBuilding>();
	city->addGroup(Game::groupBuildings);

	buildings.emplace_back(city);
}

void PlayerManager::selectUnit(Entity* unit) {
	// When new unit is selected remove last movements availables;
	if (unit != selectedUnit) {
		selUnitMov = 0x0;
	}
	selectedUnit = unit;
	if (selectedUnit != nullptr) {
		calculateAvailableMoves();
	}
}

void PlayerManager::calculateAvailableMoves() {
	Vector2D unitPos = selectedUnit->getComponent<TransformComponent>().position;
	int mRange = selectedUnit->getComponent<UnitComponent>().movementRange;
	
	for (int y = 0; y < HEIGHT_MAP; y++) {
		for (int x = 0; x < WIDTH_MAP; x++) {
			if (!Game::map->isTileOccupied(x, y)) {
				if (mRange >= abs(unitPos.x / SCALED_TILE_SIZE - x) + abs(unitPos.y / SCALED_TILE_SIZE - y)) {
					selUnitMov[x + y * WIDTH_MAP] = 1;
				}
			}
		}
	}

	Game::movementMap->mapUpdateRequest();
}

Entity* PlayerManager::getPlayer() {
	return player;
}

void* PlayerManager::getBuilding(int xPos, int yPos) {
	for (Entity* b : buildings) {
		if (b->getComponent<TransformComponent>().position == Vector2D(xPos, yPos)) {
			return (void *)&b->getComponent<BuildingComponent>();
		}
	}
	return nullptr;
}