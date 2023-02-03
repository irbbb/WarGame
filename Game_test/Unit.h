#pragma once

#include <string>

class Unit {
public:

	Unit();
	Unit(std::string name, int h, std::size_t t, int mRange);
	~Unit();

	std::string getName();
	int getHealth();
	int getMovementRange();

	enum type : std::size_t {
		land,
		water,
		air
	};
	
private:
	std::string nameUnit;
	int healthUnit;
	std::size_t typeUnit;
	int movementRange;
};