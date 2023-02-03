#pragma once

#include "Vector2D.h"
#include "Constants.h"

Vector2D::Vector2D() {
	x = 0;
	y = 0;
}

Vector2D::Vector2D(int x, int y) {
	this->x = x;
	this->y = y;
}


Vector2D& Vector2D::Add(const Vector2D& vec) {
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::Substract(const Vector2D& vec) {
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec) {
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec) {
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2) {
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2) {
	return v1.Substract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2) {
	return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2) {
	return v1.Divide(v2);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec) {
	return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec) {
	return this->Substract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec) {
	return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec) {
	return this->Divide(vec);
}

bool Vector2D::operator==(const Vector2D& vec) {
	return this->x == vec.x && this->y == vec.y;
}

Vector2D& Vector2D::operator*(const int& i) {
	this->x *= i;
	this->y *= i;

	return *this;
}

Vector2D& Vector2D::Zero() {
	this->x = 0;
	this->y = 0;

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector2D vec) {
	stream << "(" << vec.x << "," << vec.y << ")";
	return stream;
}

bool Vector2D::sameTile(Vector2D a, Vector2D b) {
	return a.x / SCALED_TILE_SIZE * SCALED_TILE_SIZE == b.x / SCALED_TILE_SIZE * SCALED_TILE_SIZE &&
		a.y / SCALED_TILE_SIZE * SCALED_TILE_SIZE == b.y / SCALED_TILE_SIZE * SCALED_TILE_SIZE;
}
