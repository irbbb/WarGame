#include "UIManager.h"
#include "ECS/Components.h"

extern Manager manager;

UIManager::UIManager() {

}

UIManager::~UIManager(){
}

void UIManager::addText(std::string id, int xPos, int yPos, std::string text, std::string font, SDL_Color color) {
	Entity* label = &manager.addEntity();
	label->addComponent<UIText>(xPos, yPos, text, font, color);
	label->addGroup(Game::groupUI);

	texts.emplace(id, label);
}

void UIManager::updateUiText(std::string id, std::string text) {
		texts[id]->getComponent<UIText>().setText(text, "arial");
}

void UIManager::addRect(int xPos, int yPos, int w, int h, Uint32 bgColor) {
	Entity* square = &manager.addEntity();

	square->addComponent<UIRect>(xPos, yPos, w, h, bgColor);
	square->addGroup(Game::groupUI);

}