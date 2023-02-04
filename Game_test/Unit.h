#pragma once

#include <string>

class Unit {
public:

	Unit();
	Unit(std::string name, int h, char t, int mRange, int cost);
	~Unit();

	std::string getName();
	int getHealth();
	int getMovementRange();
	int getCost();
	char getType();

	enum type : char {
		land,
		water,
		air
	};
	
private:
	std::string nameUnit;
	int healthUnit;
	char typeUnit;
	int movementRange;
	int costUnit;
};