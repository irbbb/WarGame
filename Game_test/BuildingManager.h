#pragma once

#include "ECS/ECS.h"
#include <string>
#include "PlayerManager.h"

class BuildingManager {
public:
	static Entity* createBuilding(std::string textureId, PlayerManager* player, int xTile, int yTile, Manager* manager);

};
