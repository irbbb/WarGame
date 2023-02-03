#pragma once

#include "../Game.h"
#include "Components.h"
#include "../Constants.h"

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

			switch (Game::event.button.button) {
			case SDL_BUTTON_LEFT:
				// If an unit is in the same tile as click and selected unit is different from this unit, select it
				if (Vector2D::sameTile(transform->position, Vector2D(xPosScreen, yPosScreen))) {
					if (unit->player->selectedUnit != entity) {
						unit->player->selectUnit(entity);
					}
				}
				else if (
				// Check if this unit is the selected unit,
				unit->player->selectedUnit == entity && 
				// can move to the clicked tiled
				unit->player->selUnitMov[xPosScreen / SCALED_TILE_SIZE + yPosScreen / SCALED_TILE_SIZE * WIDTH_MAP] &&
				// and move it to clicked tile, but if tile is occupied not
				Game::map->occupyTile(xPosScreen / SCALED_TILE_SIZE, yPosScreen / SCALED_TILE_SIZE))
				{
					if (unit->building != nullptr) {
						unit->building->emptyBuilding = true;
						BuildingComponent* building = (BuildingComponent*) unit->player->getBuilding(transform->position.x, transform->position.y);
						unit->setBuilding(building);
					}
					// Free last position tile
					Game::map->freeTile(transform->position.x / SCALED_TILE_SIZE, transform->position.y / SCALED_TILE_SIZE);
					// Set last position tile to clicked tile
					transform->position = Vector2D(xPosScreen / SCALED_TILE_SIZE * SCALED_TILE_SIZE,
						yPosScreen / SCALED_TILE_SIZE * SCALED_TILE_SIZE);
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

			switch (Game::event.button.button) {
			case SDL_BUTTON_LEFT:
				if (building->emptyBuilding) {
					building->player->addUnit("helicopter", transform->position.x / SCALED_TILE_SIZE, transform->position.y / SCALED_TILE_SIZE, building);
					building->emptyBuilding = false;
				}
				break;
			default:
				break;
			}
		}
	}
};