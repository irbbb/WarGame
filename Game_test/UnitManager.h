#pragma once

#include "Unit.h"
#include "ECS/ECS.h"
#include <map>
#include <string>
#include "PlayerManager.h"

class UnitManager {
public:
	UnitManager();
	~UnitManager();

	Unit* getUnit(std::string id);
	Entity* createUnit(std::string id, PlayerManager* player, int xTile, int yTile);

private:
	std::map<std::string, Unit*> units;
};
