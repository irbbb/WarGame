#pragma once

#include "Unit.h"
#include "ECS/ECS.h"
#include <map>
#include <string>
#include "PlayerManager.h"
#include "Map.h"

class UnitManager {
public:
	UnitManager();
	~UnitManager();

	Unit* getUnit(std::string id);
	Entity* createUnit(std::string id, PlayerManager* player, int xTile, int yTile);
	std::vector<std::string> getAllUnits();
	std::vector<std::string> getLandUnits();
	std::vector<std::string> getWaterUnits();
	std::vector<std::string> getAirUnits();
	bool isValidTileType(char type, char u, std::string unitName);

private:
	std::map<std::string, Unit*> units;
	std::vector<std::string> unitNames;
	std::vector<std::string> landUnitNames;
	std::vector<std::string> waterUnitNames;
	std::vector<std::string> airUnitNames;
};
