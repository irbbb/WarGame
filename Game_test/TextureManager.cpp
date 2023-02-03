#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName) {
	SDL_Surface* tempSurface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect srcR, SDL_Rect destR, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::renderer, tex, &srcR, &destR, NULL, NULL, flip);
}