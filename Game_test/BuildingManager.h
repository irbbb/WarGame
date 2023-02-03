#pragma once

#include "ECS/ECS.h"
#include <string>
#include "PlayerManager.h"
#include "Unit.h"

class BuildingManager {
public:
	static Entity* createBuilding(std::string textureId, PlayerManager* player, int xTile, int yTile, Manager* manager);
	static Unit::type getType(std::string textureId);
	static std::vector<std::string> getValidUnitsToGenerate(Unit::type type);
};
