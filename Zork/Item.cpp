
#include "Item.h"

Item::Item(string name, string description, int minStats, int maxStats, TypeOfItem typeOfItem, Entity* parent, bool equiped) :
	Entity(name, description, parent) {
	this->minStats = minStats;
	this->maxStats = maxStats;
	this->typeOfItem = typeOfItem;
	this->equiped = equiped;

	this->setTypeOfEntity(ITEM);
}

Item::~Item() {


}
