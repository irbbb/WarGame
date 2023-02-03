#pragma once

#include "ECS.h"
#include "../AssetManager.h"
#include "../Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UIText : public Component {
public:
	UIText(int xPos, int yPos, std::string t, std::string font, SDL_Color color) :
		text(t), textFont(font), textColor(color)
	{
		position.x = xPos;
		position.y = yPos;

		setText(t, font);
	}

	void setText(std::string t, std::string font) {
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->getFont(font), t.c_str(), textColor);
		texture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		SDL_QueryTexture(texture, nullptr, nullptr, &position.w, &position.h);
	}

	void draw() override {
		SDL_RenderCopy(Game::renderer, texture, nullptr, &position);
	}

private:
	SDL_Rect position;
	std::string text;
	std::string textFont;
	SDL_Color textColor;
	SDL_Texture* texture;
};