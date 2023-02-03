#pragma once

#include "ECS/ECS.h"
#include "UIManager.h"
#include "Constants.h"
#include <memory>
#include <vector>

class PlayerManager {
public:
	PlayerManager();
	~PlayerManager();

	void createPlayer();
	void createUI();
	void updateUI();
	void addUnit(std::string textureID, int xTile, int yTile, void* building);
	void addBuilding(std::string textureID, int xTile, int yTile);
	void selectUnit(Entity* unit);
	void calculateAvailableMoves();
	void draw();
	void* getBuilding(int xPos, int yPos);
	Entity* getPlayer();

	Entity* selectedUnit;
	std::bitset<HEIGHT_MAP* WIDTH_MAP> selUnitMov;
	
private:
	UIManager* uiManager;
	Entity* player;
	std::vector<Entity*> units;
	std::vector<Entity*> buildings;
	int gold;
};