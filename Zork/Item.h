#ifndef ITEM_H
#define ITEM_H

#include "Entity.h"
#include <string>

using namespace std;

enum TypeOfItem {
	WEAPON,
	SHIELD,
	POTION,
	KEY,
	CHEST
};

class Item : public Entity
{
public:
	Item(string name, string description, int minStats, int maxStats, TypeOfItem typeOfItem, Entity* parent, bool equiped);
	~Item();

	//Operators

	//Functions

	//Getters
	inline const TypeOfItem& getTypeOfItem() const { return this->typeOfItem; }
	inline const bool& getEquiped() const { return this->equiped; }
	inline const int& getMinStats() const { return this->minStats; }
	inline const int& getMaxStats() const { return this->maxStats; }


	//Setters
	inline void setEquiped(bool eq) { equiped = eq; }

private:
	string name;
	int minStats;
	int maxStats;
	TypeOfItem typeOfItem;
	bool equiped;

};

#endif