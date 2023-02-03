#pragma once

#include <map>
#include <string>
#include <SDL_ttf.h>
#include "Vector2D.h"
#include "ECS/ECS.h"
#include "TextureManager.h"

class AssetManager {
public:
	AssetManager(Manager* man);
	~AssetManager();

	void AddTexture(std::string id, const char* path);
	SDL_Texture* getTexture(std::string);

	void AddFont(std::string id, std::string path, int fontSize);
	TTF_Font* getFont(std::string id);

private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
};