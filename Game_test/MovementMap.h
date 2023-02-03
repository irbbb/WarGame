#pragma once

#include "Game.h"
#include <string>
#include <bitset>
#include "Constants.h"


class MovementMap {
public:
	MovementMap();
	~MovementMap();

	void LoadMap(std::bitset<HEIGHT_MAP*WIDTH_MAP> bs);
	void AddTile(int xSrc, int ySrc, int xPos, int yPos);
	void mapUpdateRequest();
	bool isPendingUpdate();

private:
	bool mapNeedUpdate;
};