#pragma once

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D velocity;
	
	int height = 32, width = 32;

	int scale = 1;
	
	TransformComponent() {
		position.Zero();
	}

	TransformComponent(int x, int y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(int x, int y, int h, int w) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
	}

	TransformComponent(int x, int y, int h, int w, int sc) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = sc;
	}

	void init() override {
		velocity.Zero();
	}

	void update() override {
		position += velocity;
	}
	

};