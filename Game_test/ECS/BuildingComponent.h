#pragma once

#include "Components.h"
#include "../PlayerManager.h"
#include "../Unit.h"

class BuildingComponent : public Component {
public:
	BuildingComponent(PlayerManager* p, Unit::type type) {
		player = p;
		typeBuilding = type;
	}

	PlayerManager* player;
	Unit::type typeBuilding;
	bool emptyBuilding = true;
};