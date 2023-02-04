#include "PlayerManager.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include <sstream>
#include "MovementMap.h"
#include "BuildingManager.h"
#include "Game.h"

extern Manager manager;

PlayerManager::PlayerManager(){
	player = &manager.addEntity();
	uiManager = new UIManager();
	selectedUnit = nullptr;
	gold = 20;
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
	// Player stats
	uiManager->addRect(CAMERA_WIDTH - CAMERA_WIDTH / 4, CAMERA_HEIGHT - 70, CAMERA_WIDTH / 4, 70, 0xFF000000);
	uiManager->addText("Player", CAMERA_WIDTH - CAMERA_WIDTH / 4 + 10, CAMERA_HEIGHT - 60, "Text", "arial", white);
	
	// Unit stats
	uiManager->addRect(0, CAMERA_HEIGHT - 70, CAMERA_WIDTH / 4, 70, 0xFF000000);
	uiManager->addText("Unit Health", 10, CAMERA_HEIGHT - 60, "Unit health", "arial", white);
	uiManager->addText("Unit Movement Range", 10, CAMERA_HEIGHT - (60 - FONT_SIZE), "Unit Movement Range", "arial", white);
}

void PlayerManager::updateUI() {
	std::stringstream player;
	std::stringstream unitHealth;
	std::stringstream unitMovementRange;

	player << "Player gold: " << gold;
	
	if (selectedUnit != nullptr) {
		unitHealth << "Health: " << selectedUnit->getComponent<UnitComponent>().health;
		unitMovementRange << "Movement Range: " << selectedUnit->getComponent<UnitComponent>().movementRange;
	}

	uiManager->updateUiText("Player", player.str());
	uiManager->updateUiText("Unit Health", unitHealth.str());
	uiManager->updateUiText("Unit Movement Range", unitMovementRange.str());
}

void PlayerManager::addUnit(std::string textureID, int xTile, int yTile, void* building) {
	int costUnit = Game::unitManager->getUnit(textureID)->getCost();

	if (gold < costUnit) {
		return;
	}

	gold -= Game::unitManager->getUnit(textureID)->getCost();

	Entity* unit = Game::unitManager->createUnit(textureID, this, xTile, yTile);
	
	unit->getComponent<UnitComponent>().setBuilding((BuildingComponent*)building);

	units.emplace_back(unit);
}

void PlayerManager::addBuilding(std::string id, int xTile, int yTile) {
	buildings.emplace_back(BuildingManager::createBuilding(id, this, xTile, yTile, &manager));
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
	
	char unitType = selectedUnit->getComponent<UnitComponent>().type;
	std::string unitName = selectedUnit->getComponent<UnitComponent>().name;

	for (int y = 0; y < HEIGHT_MAP; y++) {
		for (int x = 0; x < WIDTH_MAP; x++) {
			char tileType = Game::map->getTileType(x, y);
			if (Game::unitManager->isValidTileType(tileType, unitType, unitName) && !Game::map->isTileOccupied(x, y)) {
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