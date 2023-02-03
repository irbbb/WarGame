#pragma once

#include "../Game.h"
#include "Components.h"
#include "../Constants.h"

class KeyboardController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	PlayerManager* player;

	KeyboardController(PlayerManager* p) {
		player = p;
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) 
		{
			switch (Game::event.key.keysym.sym) {
			case SDLK_ESCAPE:
				player->selectUnit(nullptr);
				break;
			case SDLK_DOWN:
				if (Game::camera.y < HEIGHT_MAP * SCALED_TILE_SIZE - CAMERA_HEIGHT) {
					Game::camera.y += CAMERA_SPEED;
				}
				break;
			case SDLK_UP:
				if (Game::camera.y > 0) {
					Game::camera.y -= CAMERA_SPEED;
				}
				break;
			case SDLK_LEFT:
				if (Game::camera.x > 0) {
					Game::camera.x -= CAMERA_SPEED;
				}
				break;
			case SDLK_RIGHT:
				if (Game::camera.x < WIDTH_MAP * SCALED_TILE_SIZE - CAMERA_WIDTH) {
					Game::camera.x += CAMERA_SPEED;
				}
				break;
			default:
				break;
			}
		}
	}
};