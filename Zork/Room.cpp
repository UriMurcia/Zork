#include "Room.h"
#include <iostream>
#include "Npc.h"
#include "Item.h"
#include "Exit.h"


Room::Room(string name, string description)
	: Entity(name, description, NULL) {

	this->setTypeOfEntity(ROOM);
}

Room::~Room() {


}

void Room::look() const {
	//Room
	cout << getName() << ": " << getDescription() << "\n\n";

	//NPCs in the room
	for (vector<Entity*>::const_iterator np = this->childs.begin(); np != this->childs.cend(); ++np)
	{
		if ((*np)->typeOfEntity == NPC)
		{
			Npc* npc = (Npc*)*np;
			cout << npc->getName() << ": " << npc->getDescription() << "\n";
		}
	}
	cout << "\n";

	//ITEMS
	cout << "Items in the room:\n";
	for (vector<Entity*>::const_iterator itm = this->childs.begin(); itm != this->childs.cend(); ++itm)
	{
		if ((*itm)->typeOfEntity == ITEM)
		{
			Item* item = (Item*)*itm;
			cout << item->getName() << "\n";
		}
	}
	cout << "\n\n";

}