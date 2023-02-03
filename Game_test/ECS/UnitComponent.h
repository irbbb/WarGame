#pragma once

#include "Components.h"
#include "../PlayerManager.h"
#include "Map.h"
#include "../Game.h"
#include "../Constants.h"
#include "../Unit.h"

class UnitComponent : public Component {
public:
	TransformComponent* transform;
	PlayerManager* player;
	std::string name;
	int health;
	int movementRange;
	BuildingComponent* building; //Indicates in what building is placed or none

	UnitComponent(Unit* u, PlayerManager* p){
		name = u->getName();
		health = u->getHealth();
		movementRange = u->getMovementRange();

		transform = nullptr;
		player = p;

		building = nullptr;
	};

	~UnitComponent() {};

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		Game::map->occupyTile(transform->position.x / SCALED_TILE_SIZE, transform->position.y / SCALED_TILE_SIZE);
	};

	void update() override {};

	void draw() override {};

	void setBuilding(BuildingComponent* b) {
		building = b;
	}

};