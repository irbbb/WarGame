#pragma once

#include "../Game.h"
#include "Components.h"
#include "../Constants.h"
#include "../BuildingManager.h"

class MouseControllerPlayer : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_MOUSEMOTION) {
			transform->position = Vector2D((Game::event.motion.x + Game::camera.x) / SCALED_TILE_SIZE * SCALED_TILE_SIZE, 
								(Game::event.motion.y + Game::camera.y) / SCALED_TILE_SIZE * SCALED_TILE_SIZE);
		}
	}
};

class MouseControllerUnit : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	UnitComponent* unit;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		unit = &entity->getComponent<UnitComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_MOUSEBUTTONDOWN) {

			int xPosScreen = Game::event.button.x + Game::camera.x;
			int yPosScreen = Game::event.button.y + Game::camera.y;

			int xTileScreen = xPosScreen / SCALED_TILE_SIZE;
			int yTileScreen = yPosScreen / SCALED_TILE_SIZE;

			int xTileTransform = transform->position.x / SCALED_TILE_SIZE;
			int yTileTransform = transform->position.y / SCALED_TILE_SIZE;

			switch (Game::event.button.button) {
			case SDL_BUTTON_LEFT:
				// If an unit is in the same tile as click and selected unit is different from this unit, select it
				if (Vector2D::sameTile(transform->position, Vector2D(xPosScreen, yPosScreen))) {
					if (unit->player->selectedUnit != entity) {
						unit->player->selectUnit(entity);
					}
				}
				else if (unit->player->selectedUnit == entity && unit->player->selUnitMov[xTileScreen + yTileScreen * WIDTH_MAP] && Game::map->occupyTile(xTileScreen, yTileScreen)) {
					if (unit->building != nullptr) {
						unit->building->emptyBuilding = true;
					}

					BuildingComponent* building = (BuildingComponent*) unit->player->getBuilding(xTileScreen * SCALED_TILE_SIZE, yTileScreen * SCALED_TILE_SIZE);
					unit->setBuilding(building);
					if (building != nullptr) {
						building->emptyBuilding = false;
					}
					// Free last position tile
					Game::map->freeTile(xTileTransform, yTileTransform);
					// Set last position tile to clicked tile
					transform->position = Vector2D(xTileScreen * SCALED_TILE_SIZE, yTileScreen * SCALED_TILE_SIZE);
					// Deselect unit when moved
					unit->player->selectUnit(nullptr);
				}
				break;
			default:
				break;
			}
		}
	}
};

class MouseControllerBuilding : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	BuildingComponent* building;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
		building = &entity->getComponent<BuildingComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_MOUSEBUTTONDOWN) {

			int xPosScreen = Game::event.button.x + Game::camera.x;
			int yPosScreen = Game::event.button.y + Game::camera.y;

			int xTileScreen = xPosScreen / SCALED_TILE_SIZE;
			int yTileScreen = yPosScreen / SCALED_TILE_SIZE;

			int xTileTransform = transform->position.x / SCALED_TILE_SIZE;
			int yTileTransform = transform->position.y / SCALED_TILE_SIZE;

			std::vector<std::string> posibleUnits = BuildingManager::getValidUnitsToGenerate(building->typeBuilding);

			switch (Game::event.button.button) {
			case SDL_BUTTON_LEFT:
				if (xTileScreen == xTileTransform && yTileScreen == yTileTransform) {
					for (auto const& u : posibleUnits) {
						std::cout << u << std::endl;
					}
					if (building->emptyBuilding) {
						std::cout << building->typeBuilding << std::endl;
						building->player->addUnit(posibleUnits[0], xTileTransform, yTileTransform, building);
						building->emptyBuilding = false;
					}
				}
				break;
			default:
				break;
			}
		}
	}
};