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

Exit* Room::showExits() const { //Show a list of all the exits in the room and select to go one of them
	int numerization = 0;

	cout << "0: Exit\n";

	vector<Entity*> exitsVector;

	for (vector<Entity*>::const_iterator ex = this->childs.begin(); ex != this->childs.cend(); ++ex)
	{
		if ((*ex)->typeOfEntity == EXIT)
		{
			cout << numerization + 1 << ": ";
			Exit* exit = (Exit*)*ex;
			exitsVector.push_back(exit);
			cout << exit->getName() << "\n";

			numerization++;
		}
	}
	cout << "\n";

	int exitToGo;
	cin >> exitToGo;
	if (!cin || exitToGo < 0 || exitToGo>numerization) { //If its not an integer or incorrect value
		throw string("Incorrect value \n\n");
	}
	else {
		if (exitToGo == 0) { //If the player wants to go back to menu and do not select an exit
			throw string("\n");
		}
		else { //Return exit selected to go
			return (Exit*)exitsVector[exitToGo - 1];

		}
	}
}
