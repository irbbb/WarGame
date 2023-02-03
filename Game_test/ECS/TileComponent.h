#pragma once

#include <SDL.h>
#include "ECS.h"
#include "../AssetManager.h"

class TileComponent : public Component {
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;
	
	~TileComponent() {};

	TileComponent(int xSrc, int ySrc, int xPos, int yPos, int tSize, int tScale, std::string id) {
		texture = Game::assets->getTexture(id);

		position.x = xPos;
		position.y = yPos;

		srcRect.x = xSrc;
		srcRect.y = ySrc;
		srcRect.w = srcRect.h = tSize;

		destRect.x = xPos;
		destRect.y = yPos;
		destRect.w = destRect.h = tSize * tScale;
	}

	void update() override {
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	void draw() override {
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};