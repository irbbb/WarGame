#include "PlayerManager.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include <sstream>
#include "MovementMap.h"
#include "BuildingManager.h"
#include "Game.h"
#include <queue>
#include <tuple>
#include <unordered_map>
#include "KeyHasher.h"

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
	uiManager->addText("Unit Name", 10, CAMERA_HEIGHT - 60, "Unit name", "arial", white);
	uiManager->addText("Unit Health", 10, CAMERA_HEIGHT - (60 - FONT_SIZE), "Unit health", "arial", white);
	uiManager->addText("Unit Movement Range", 10, CAMERA_HEIGHT - (60 - FONT_SIZE * 2), "Unit Movement Range", "arial", white);
}

void PlayerManager::updateUI() {
	std::stringstream player;
	std::stringstream unitName;
	std::stringstream unitHealth;
	std::stringstream unitMovementRange;

	player << "Player gold: " << gold;
	
	if (selectedUnit != nullptr) {
		unitName << selectedUnit->getComponent<UnitComponent>().name;
		unitHealth << "Health: " << selectedUnit->getComponent<UnitComponent>().health;
		unitMovementRange << "Movement Range: " << selectedUnit->getComponent<UnitComponent>().movementRange;
	}

	uiManager->updateUiText("Player", player.str());
	uiManager->updateUiText("Unit Name", unitName.str());
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
	unsigned char mRange = selectedUnit->getComponent<UnitComponent>().movementRange;
	
	char unitType = selectedUnit->getComponent<UnitComponent>().type;
	std::string unitName = selectedUnit->getComponent<UnitComponent>().name;

	// Create a queue to insert tiles that has to be checked.
	// Contains a tuple with tile position and remaining moves
	std::queue<std::tuple<Vector2D, unsigned char>> queue;

	// Create a map to insert valid tiles, with its remaining moves
	std::unordered_map<Vector2D, unsigned char, std::hash<Vector2D>> moves;

	// Insert into queue adyacent tiles to actual position and unit movement range
	if (unitPos.x > 0) {
		queue.push(std::make_tuple(Vector2D(unitPos.x - SCALED_TILE_SIZE, unitPos.y), mRange));
	}
	if (unitPos.x < WIDTH_MAP * SCALED_TILE_SIZE) {
		queue.push(std::make_tuple(Vector2D(unitPos.x + SCALED_TILE_SIZE, unitPos.y), mRange));
	}
	if (unitPos.y > 0) {
		queue.push(std::make_tuple(Vector2D(unitPos.x, unitPos.y - SCALED_TILE_SIZE), mRange));
	}
	if (unitPos.y < HEIGHT_MAP * SCALED_TILE_SIZE) {
		queue.push(std::make_tuple(Vector2D(unitPos.x, unitPos.y + SCALED_TILE_SIZE), mRange));
	}

	// While exists possible tiles
	while (!queue.empty()) {
		Vector2D tile = std::get<0>(queue.front());
		unsigned char remainingMoves = std::get<1>(queue.front());
		queue.pop();

		char tileType = Game::map->getTileType(tile.x / SCALED_TILE_SIZE, tile.y / SCALED_TILE_SIZE);

		// If tile has moves left
		if (remainingMoves > 0) {
			// And is valid type of tile and not occupied
			if (Game::unitManager->isValidTileType(tileType, unitType, unitName) && !Game::map->isTileOccupied(tile.x / SCALED_TILE_SIZE, tile.y / SCALED_TILE_SIZE)) {
				// Insert in valid moves list
				moves.emplace(tile, remainingMoves - 1);

				// Add to queue adyacents tiles to the valid one
				if (tile.x > 0) {
					queue.push(std::make_tuple(Vector2D(tile.x - SCALED_TILE_SIZE, tile.y), remainingMoves - 1));
				}
				if (tile.x < WIDTH_MAP * SCALED_TILE_SIZE) {
					queue.push(std::make_tuple(Vector2D(tile.x + SCALED_TILE_SIZE, tile.y), remainingMoves - 1));
				}
				if (tile.y > 0) {
					queue.push(std::make_tuple(Vector2D(tile.x, tile.y - SCALED_TILE_SIZE), remainingMoves - 1));
				}
				if (tile.y < HEIGHT_MAP * SCALED_TILE_SIZE) {
					queue.push(std::make_tuple(Vector2D(tile.x, tile.y + SCALED_TILE_SIZE), remainingMoves - 1));
				}
			}
		}
	}

	// Iterate over all valid tiles and set valid into movementBitMap
	for (auto& m : moves) {
		selUnitMov[m.first.x / SCALED_TILE_SIZE + m.first.y / SCALED_TILE_SIZE * WIDTH_MAP] = 1;
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