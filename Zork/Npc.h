#ifndef NPC_H
#define NPC_H

#include "Creature.h"
#include <string>

using namespace std;

class Npc : public Creature
{
public:
	Npc(string name, string description, int health, int maxHealth, Room* Room, bool isEnemy);
	~Npc();

	//Operators

	//Functions


	//Getters

	//Setters

private:
	bool isEnemy;

};

#endif