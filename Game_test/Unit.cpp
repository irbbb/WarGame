#include "Unit.h"

Unit::Unit() {};

Unit::Unit(std::string name, int h, char t, int mRange, int cost) : 
	nameUnit(name), healthUnit(h), typeUnit(t), movementRange(mRange), costUnit(cost){

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

int Unit::getCost() {
	return costUnit;
}

char Unit::getType() {
	return typeUnit;
}