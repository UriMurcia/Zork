#include <iostream>
#include <time.h>
#include "World.h"
#include "Entity.h"
#include "Player.h"
#include "Item.h"
#include "Npc.h"
#include "Room.h"
#include "Exit.h"


World::World() {
	this->continuePlaying = true;
}

World::~World() {


}


void World::createAllEntities(string playerName) {

	//ROOM CREATION
	Room* floor1 = new Room("Floor 1", "It is the first floor of the Paradise tower. \nYou can go up 1 floor.");


	//PLAYER CREATION
	player = new Player(playerName, "A traveler from other lands.", 100, 100, 4, floor1);
	entities.push_back(player);
	//SWORD CREATION
	Item* sword = new Item("Sword", "Big sword with a lot of consistency.", 6, 11, WEAPON, floor1, false);
	entities.push_back(sword);

	//GUARDIAN CREATION
	Npc* guardian = new Npc("Guardian", "He is the guardian of the tower.", 100, 100, floor1, false);
	entities.push_back(guardian);


	//ENEMIES CREATION
	Npc* troll = new Npc("Big troll", "This troll is big, but does not seem very smart.", 25, 25, floor1, true);
	Item* mace = new Item("Mace", "Big mace with a lot of spikes.", 2, 6, WEAPON, troll, true);
	troll->weapon = mace;
	Item* shield = new Item("Shield", "Small but usefull sheild.", 2, 5, SHIELD, troll, true);
	troll->shield = shield;
	entities.push_back(troll);
	entities.push_back(mace);
	entities.push_back(shield);


}


void World::initWorld() {
	srand(time(0));
	//game initialization
	cout << "Guardian: Welcome traveler! You made it to the Paradise Tower. \n";
	cout << "What is your name? \n\n";
	cout << "Name: ";
	string name;
	cin >> name;

	cout << "\nGuardian: Hi " + name + ", ";
	cout << "in this tower you will have to battle against dangerous enemies. \n";
	cout << "To come out victorious, you need a weapon, here you have a sword, take it and do not forget to equip it. \n\n";

	createAllEntities(name);
}


void World::gameLoop() {
	int choice;

	cin.clear();
	cin.ignore();

	//Menu interface
	cout << "||||||||||||||||||||||||||||||||||||||||||||\n";
	cout << "0: Quit \n";
	cout << "1: Look around \n";
	cout << "2: Select where you want to go \n";
	cout << "3: Attack creature in the room \n";
	cout << "4: Pick items in the room \n";
	cout << "5: Inventory \n";
	cout << "6: Equip weapon or shield from inventory \n";
	cout << "7: Use objects from inventory \n";
	cout << "8: Unequip weapon \n";
	cout << "9: Unequip shield \n";
	cout << "10: Drop items from inventory\n";
	cout << "||||||||||||||||||||||||||||||||||||||||||||\n\n";

	cout << "Choice: ";
	cin >> choice;
	cout << "\n";

	if (!cin) { //If its not an integer
		cout << "Incorrect value \n\n";
	}
	else {
		int numerization = 0;
		switch (choice) {
		case 0: //Quit game
			this->continuePlaying = false;
			break;
		case 1: //Look room
			cout << "You look around \n\n";
			player->parent->look();
			break;
		case 2: //Move to other rooms
			cout << "Choose room to go\n\n";
			break;
		case 3: //Attack enemies
			cout << "You attack creature in the room \n";
			break;
		case 4: //Pick items in the room
			cout << "Select item to pick: \n";
			cout << "0: Exit\n";

			//Iteration of all entities in the room with type of entity ITEM to find the objects in the room
			for (int i = 0; i < player->parent->childs.size(); i++) {
				if (player->parent->childs[i]->getTypeOfEntity() == ITEM) {
					cout << (numerization + 1) << ": ";
					cout << player->parent->childs[i]->getName() + "\n";
					numerization++;
				}
			}

			cout << "Pick: ";
			cin >> choice;
			cout << "\n";
			if (!cin) { //If its not an integer
				cout << "Incorrect value \n\n";
			}
			else {
				if (choice == 0) { //Exit
					break;
				}
				else {
					if (choice < 0 || choice > numerization) { //Number not in the list
						cout << "Incorrect value \n\n";
					}
					else {
						int i = 0;
						while (choice > 0) { //countdown to select the entity depending on the number of items
							//It is used choice-- to get the iteration number of the item select
							if (player->parent->childs[i]->getTypeOfEntity() == ITEM) {
								choice--;
							}
							i++;
						}
						cout << player->parent->childs[i - 1]->getName() << " picked \n\n";
						//change parent from room to player
						player->parent->childs[i - 1]->changeParent(player, i - 1);
					}
				}
			}
			break;
		case 5: //Look items in inventory
			cout << "You look Inventory: \n\n";
			player->lookInventory();
			break;
		case 6: //Equip items in inventory
			cout << "You equip items";
			{
				bool hasSomething = player->numItemsInInventory();

				if (hasSomething) { //If inventory is not empty
					int itemPicked;
					cin >> itemPicked;
					if (!cin || itemPicked < 0 || itemPicked > player->childs.size()) { //If its not an integer or is bigger or lower than the allowed
						cout << "Incorrect value \n\n";
					}
					else {
						if (itemPicked > 0) { //0: Exit
							Item* itt = (Item*)player->childs[itemPicked - 1];
							player->equipItem(itt);
						}
					}
				}
			}
			break;
		case 7: //Use item in inventory
			cout << "Select item to use:";
			break;
		case 8: //Unequip weapon
			cout << "You unequip weapon";
			break;
		case 9: //Unequip shield
			cout << "You unequip shield";
			break;
		case 10: //Drop items from inventory
			cout << "You drop item";
		}
	}
}