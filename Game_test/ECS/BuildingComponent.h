#pragma once

#include "Components.h"
#include "../PlayerManager.h"

class BuildingComponent : public Component {
public:
	BuildingComponent(PlayerManager* p) {
		player = p;
	}

	PlayerManager* player;
	bool emptyBuilding = true;
};