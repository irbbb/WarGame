#include "AssetManager.h"
#include "ECS/Components.h"
#include "Game.h"
#include "TextureManager.h"
#include "Vector2D.h"
#include "PlayerManager.h"
#include "Constants.h"

Manager manager;

AssetManager* Game::assets = new AssetManager(&manager);
Map* Game::map = new Map("terrain", SCALE, TILE_SIZE);
UnitManager* Game::unitManager = new UnitManager();
MovementMap* Game::movementMap = new MovementMap();

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

PlayerManager* player = new PlayerManager();
bool Game::isRunning = false;

SDL_Rect Game::camera = {0, 0, CAMERA_WIDTH, CAMERA_HEIGHT};

Game::Game() {
	window = NULL;
	renderer = NULL;
}

Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int window_flags = 0;
	if (fullscreen) {
		window_flags = SDL_WINDOW_FULLSCREEN;
	}

	// Initialize SDL, window and renderer
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL Initialized... " << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, window_flags);
		if (window != NULL) {
			std::cout << "Window created!" << std::endl;

			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer != NULL) {
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				std::cout << "Renderer created!" << std::endl;
				isRunning = true;
			}
		}
	}

	if (!isRunning) {
		std::cout << "Initialization failed!" << std::endl;
		return;
	}

	if (TTF_Init() == -1) {
		std::cout << "Error: SDL_TFF " << std::endl;
	}
	
	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("movementAvailableTile", "assets/movementAvailableTile.png");
	assets->AddTexture("player", "assets/hoveredTile.png");
	assets->AddTexture("tank", "assets/tank.png");
	assets->AddTexture("soldier", "assets/soldier.png");
	assets->AddTexture("helicopter", "assets/helicopter.png");
	assets->AddTexture("city", "assets/city.png");
	assets->AddTexture("airport", "assets/airport.png");

	assets->AddFont("arial", "assets/arial.ttf", FONT_SIZE);

	
	Game::map->LoadMap("assets/map.map", WIDTH_MAP, HEIGHT_MAP);
	

	player->createPlayer();
	player->createUI();
	player->addUnit("tank", 1, 1, nullptr);
	player->addUnit("soldier", 2, 2, nullptr);
	player->addUnit("soldier", 2, 3, nullptr);
	player->addUnit("helicopter", 4, 4, nullptr);
	player->addBuilding("city", 2, 4);
	player->addBuilding("city", 3, 5);
	player->addBuilding("airport", 6, 3);

	SDL_Color white = { 255, 255, 255 };

}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& cities(manager.getGroup(Game::groupBuildings));
auto& units(manager.getGroup(Game::groupUnits));
auto& movementTiles(manager.getGroup(Game::groupMovementTile));
auto& uiElements(manager.getGroup(Game::groupUI));


void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	manager.refresh();
	manager.update();
	player->updateUI();
	if (Game::movementMap->isPendingUpdate()) {
		Game::movementMap->LoadMap(player->selUnitMov);
	}
}

void Game::render() {
	SDL_RenderClear(renderer);

	for (auto& t : tiles) {
		t->draw();
	}

	for (auto& p : players) {
		p->draw();
	}

	for (auto& c : cities) {
		c->draw();
	}

	for (auto& u : units) {
		u->draw();
	}

	for (auto& mt : movementTiles) {
		mt->draw();
	}

	for (auto& ui : uiElements) {
		ui->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game closed!" << std::endl;
}