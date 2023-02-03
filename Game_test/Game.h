#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "Map.h"
#include "UnitManager.h"
#include "MovementMap.h"

class AssetManager;
class Map;
class UnitManager;
class MovementMap;

class Game {
public:
	Game();
	~Game();

	bool running() { return isRunning; }

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();

	static bool isRunning;

	static SDL_Renderer* renderer;
	static SDL_Event event;

	static AssetManager* assets;

	static Map* map;
	static MovementMap* movementMap;

	static UnitManager* unitManager;

	static SDL_Rect camera;

	enum groupLabels : std::size_t {
		groupMap,
		groupPlayers,
		groupBuildings,
		groupUnits,
		groupMovementTile,
		groupUI
	};

private:
	SDL_Window* window;
	
};