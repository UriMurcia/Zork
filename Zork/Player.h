#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Creature.h"
#include "Npc.h"

using namespace std;

class Player : public Creature
{
public:
	Player(string name, string description, int health, int maxHealth, int maxNumItems, Room* room, bool dead);
	~Player();

	//Operators

	//Functions
	void lookInventory() const;
	void equipItem(Item* itemToEquip);
	void unequipWeapon();
	void unequipShield();
	bool numItemsInInventory();
	bool attack(Npc* target);


	//Getters


	//Setters

private:
	int maxNumItems;
	Room* currentRoom;


};

#endif