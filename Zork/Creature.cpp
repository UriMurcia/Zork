#include <iostream>
#include "Creature.h"
#include "Item.h"
#include "Room.h"

using namespace std;

Creature::Creature(string name, string description, int health, int maxHealth, Room* room, bool dead)
	: Entity(name, description, (Entity*)room) {
	this->health = health;
	this->maxHealth = maxHealth;
	this->dead = dead;


	this->setTypeOfEntity(CREATURE);

}

Creature::~Creature() {


}


const int& Creature::getDamageMin() const {
	if (weapon != NULL) {
		return this->weapon->getMinStats();
	}
	else {
		return 0;
	}
}
const int& Creature::getDamageMax() const {
	if (weapon != NULL) {
		return this->weapon->getMaxStats();
	}
	else {
		return 0;
	}
}
const int& Creature::getDefenseMin() const {
	if (weapon != NULL) {
		return this->shield->getMinStats();
	}
	else {
		return 0;
	}
}
const int& Creature::getDefenseMax() const {
	if (weapon != NULL) {
		return this->shield->getMaxStats();
	}
	else {
		return 0;
	}
}


void Creature::dropItem(Item* itemToDrop) {
	Room* roomWhereToDrop = (Room*)this->parent;

	//Find the number of the child
	int numChild = 0;
	for (int i = 0; i < this->childs.size(); i++) {
		Item* itt = (Item*)childs[i];
		if (itt->getName() == itemToDrop->getName()) {
			break;
		}
		numChild++;
	}

	//Remove weapon if the item dropped was an equiped weapon
	if (weapon != NULL) {
		if (itemToDrop->getName() == this->weapon->getName()) {
			this->weapon->setEquiped(false);
			this->weapon = NULL;
		}
	}

	//Remove shield if the item dropped was an equiped shield
	if (shield != NULL) {
		if (itemToDrop->getName() == this->shield->getName()) {
			this->shield->setEquiped(false);
			this->shield = NULL;
		}
	}

	itemToDrop->changeParent(roomWhereToDrop, numChild);
}