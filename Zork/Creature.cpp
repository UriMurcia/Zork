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