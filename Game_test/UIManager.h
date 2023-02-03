#pragma once

#include <map>
#include "ECS/ECS.h"
#include <SDL.h>

class UIManager {
public:
	UIManager();
	~UIManager();

	void addText(std::string id, int xPos, int yPos, std::string text, std::string font, SDL_Color color);
	void updateUiText(std::string id, std::string text);
	void draw();

private:
	std::map<std::string, Entity*> texts;
};