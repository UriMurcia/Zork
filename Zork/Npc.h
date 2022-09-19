#ifndef NPC_H
#define NPC_H

#include "Creature.h"
#include <string>

using namespace std;

class Npc : public Creature
{
public:
	Npc(string name, string description, int health, int maxHealth, Room* Room, bool isEnemy, bool dead);
	~Npc();

	//Operators

	//Functions


	//Getters
	inline const bool& getIsEnemy() const { return this->isEnemy; }

	//Setters

private:
	bool isEnemy;

};

#endif