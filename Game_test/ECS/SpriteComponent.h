#pragma once

#include "Components.h"
#include <SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "Game.h"

class SpriteComponent : public Component {
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

public:
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	
	SpriteComponent() = default;

	SpriteComponent(std::string tID) {
		setTexture(tID);
	}

	~SpriteComponent() {}

	void setTexture(std::string tID) {
		texture = Game::assets->getTexture(tID);
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = 0;
		srcRect.y = 0;

		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override {
		destRect.x = transform->position.x - Game::camera.x;
		destRect.y = transform->position.y - Game::camera.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}
};