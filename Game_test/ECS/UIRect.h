#pragma once

#include "ECS.h"
#include "../AssetManager.h"
#include "../Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UIRect : public Component {
public:
	UIRect(int xPos, int yPos, int width, int height, Uint32 backgroundColor) : bgColor(backgroundColor)
	{
		position.x = xPos;
		position.y = yPos;
		position.w = width;
		position.h = height;

		setTex();
	}

	void setTex() {
		SDL_Surface* surf = SDL_CreateRGBSurface(0, position.w, position.h, 32, 0, 0, 0, 0);
		SDL_FillRect(surf, NULL, bgColor);
		texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(texture, nullptr, nullptr, &position.w, &position.h);
	}

	void draw() override {
		SDL_RenderCopy(Game::renderer, texture, nullptr, &position);
	}

private:
	SDL_Rect position;
	Uint32 bgColor;
	SDL_Texture* texture;
};