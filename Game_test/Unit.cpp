#include "Unit.h"

Unit::Unit() {};

Unit::Unit(std::string name, int h, std::size_t t, int mRange) : nameUnit(name), healthUnit(h), typeUnit(t), movementRange(mRange){

}

Unit::~Unit() {};

std::string Unit::getName() {
	return nameUnit;
}

int Unit::getHealth() {
	return healthUnit;
}

int Unit::getMovementRange() {
	return movementRange;
}