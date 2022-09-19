#ifndef CREATURE_H
#define CREATURE_H

#include "Entity.h"
#include <vector>
#include <string>

class Room;
class Item;

class Creature : public Entity
{
public:
	Creature(string name, string description, int health, int maxHealth, Room* room, bool dead);
	~Creature();

	//Operators

	//Functions

	//Getters
	inline const int& getHealth() const { return this->health; }
	inline const int& getMaxHealth() const { return this->maxHealth; }
	const int& getDamageMin() const;
	const int& getDamageMax() const;
	const int& getDefenseMin() const;
	const int& getDefenseMax() const;
	inline const bool& isDead() const { return this->dead; }

	//Setters

public:
	int health;
	int maxHealth;
	Item* weapon;
	Item* shield;
	bool dead;
};

#endif