#include <iostream>
#include "Creature.h"
#include "Item.h"
#include "Room.h"

using namespace std;

Creature::Creature(string name, string description, int health, int maxHealth, Room* room)
	: Entity(name, description, (Entity*)room) {
	this->health = health;
	this->maxHealth = maxHealth;


	this->setTypeOfEntity(CREATURE);

}

Creature::~Creature() {


}
