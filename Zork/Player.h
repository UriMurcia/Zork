#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Creature.h"
#include "Npc.h"

using namespace std;

class Player : public Creature
{
public:
	Player(string name, string description, int health, int maxHealth, int maxNumItems, Room* room);
	~Player();

	//Operators

	//Functions
	void lookInventory() const;
	bool numItemsInInventory();


	//Getters


	//Setters

private:
	int maxNumItems;
	Room* currentRoom;


};

#endif