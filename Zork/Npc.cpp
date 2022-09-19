#include "Npc.h"
#include "Room.h"

Npc::Npc(const string name, string description, int health, int maxHealth, Room* room, bool isEnemy, bool dead)
	: Creature(name, description, health, maxHealth, room, dead) {
	this->isEnemy = isEnemy;

	this->setTypeOfEntity(NPC);
}

Npc::~Npc() {


}

