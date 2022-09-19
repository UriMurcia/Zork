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
	Room* floor2 = new Room("Floor 2", "It is the second floor of the Paradise tower. \nYou can go up 1 floor and down 1 floor.");
	Room* floor3 = new Room("Floor 3", "It is the third floor of the Paradise tower. \nYou can go up 1 floor and down 1 floor. It seems like there is a hidden room.");
	Room* misteriousRoom = new Room("Misterious room", "This room seems to hide something. \nYou can go back to Floor 3.");
	Room* finalFloor = new Room("Final Floor", "It is the final floor of the Paradise tower. \nYou can go down 1 floor.");
	entities.push_back(floor1);
	entities.push_back(floor2);
	entities.push_back(floor3);
	entities.push_back(misteriousRoom);
	entities.push_back(finalFloor);


	//EXIT CREATION
	Exit* exit1Floor1 = new Exit("Go floor 2", "This exit goes to Floor 2", floor1, floor2, false);

	Exit* exit1Floor2 = new Exit("Go floor 1", "This exit goes to Floor 1", floor2, floor1, false);
	Exit* exit2Floor2 = new Exit("Go floor 3", "This exit goes to Floor 3", floor2, floor3, false);

	Exit* exit1Floor3 = new Exit("Go floor 2", "This exit goes to Floor 2", floor3, floor2, false);
	Exit* exit2Floor3 = new Exit("Go floor 4", "This exit goes to Floor 4", floor3, finalFloor, false);
	Exit* exit3Floor3 = new Exit("Go misterious room", "This exit goes to the misterious room", floor3, misteriousRoom, false);

	Exit* exit1MisteriousRoom = new Exit("Go floor 3", "This exit goes back to Floor 3", misteriousRoom, floor3, false);

	Exit* exit1FinalFloor = new Exit("Go floor 3", "This exit goes to Floor 3", finalFloor, floor3, false);
	entities.push_back(exit1Floor1);
	entities.push_back(exit1Floor2);
	entities.push_back(exit2Floor2);
	entities.push_back(exit1Floor3);
	entities.push_back(exit2Floor3);
	entities.push_back(exit3Floor3);
	entities.push_back(exit1MisteriousRoom);
	entities.push_back(exit1FinalFloor);


	//PLAYER CREATION
	player = new Player(playerName, "A traveler from other lands.", 100, 100, 4, floor1, false);
	entities.push_back(player);
	//SWORD CREATION
	Item* sword = new Item("Sword", "Big sword with a lot of consistency.", 6, 11, WEAPON, floor1, false);
	entities.push_back(sword);

	//GUARDIAN CREATION
	Npc* guardian = new Npc("Guardian", "He is the guardian of the tower.", 100, 100, floor1, false, false);
	entities.push_back(guardian);


	//ENEMIES CREATION
	Npc* troll = new Npc("Big troll", "This troll is big, but does not seem very smart.", 25, 25, floor2, true, false);
	Item* mace = new Item("Mace", "Big mace with a lot of spikes.", 2, 6, WEAPON, troll, true);
	troll->weapon = mace;
	Item* shield = new Item("Shield", "Small but usefull sheild.", 2, 5, SHIELD, troll, true);
	troll->shield = shield;
	entities.push_back(troll);
	entities.push_back(mace);
	entities.push_back(shield);

	Npc* knight = new Npc("Dark knight", "Seems like a dangerous dark knight.", 75, 75, floor3, true, false);
	Item* longSword = new Item("Long Sword", "This sword is so long it can deal a lot of damage, it is difficult to use though.", 1, 15, WEAPON, knight, true);
	knight->weapon = longSword;
	entities.push_back(longSword);
	entities.push_back(knight);

	Npc* finalBoss = new Npc("Final boss", "Final boss of the Paradise Tower. He does not have weapons, it seems like he fights with his hands.", 120, 120, finalFloor, true, false);
	Item* hands = new Item("Big hands", "Big and ugly hands.", 5, 12, WEAPON, finalBoss, true);
	finalBoss->weapon = hands;
	entities.push_back(hands);
	entities.push_back(finalBoss);


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
		{
			Room* ro = (Room*)player->parent;
			try {
				Exit* exitToGo = ro->showExits();
				if (exitToGo->isLocked()) { //If exit is locked
					cout << "This door is locked. Maybe there is some key that can open it.\n\n";
				}
				else {
					int numChild = 0;
					//get Num of child (player) to remove it from childs (of the room)
					for (vector<Entity*>::const_iterator ch = player->parent->childs.begin(); ch != player->parent->childs.cend(); ++ch)
					{
						if ((*ch)->getName() == player->getName())
						{
							break;
						}
						numChild++;
					}

					player->changeParent((Entity*)exitToGo->getDestination(), numChild);


					player->parent->look();
				}
			}
			catch (string err) {

				cout << err;
			}
		}
		break;
		case 3: //Attack enemies
		{
			cout << "You attack creature in the room \n";
			int numNpcs = 0; //variable to see if there are no enemies in the room
			//Iteration of all entities in the room with type of entity NPC to find the enemy in the room
			for (vector<Entity*>::const_iterator np = player->parent->childs.begin(); np != player->parent->childs.cend(); ++np)
			{
				if ((*np)->typeOfEntity == NPC)
				{
					numNpcs++;
					Npc* npc = (Npc*)*np;
					bool finishGame = player->attack(npc);
					if (finishGame) { //If we win the game or we die
						this->continuePlaying = false;
					}
					break;
				}
			}
			if (numNpcs == 0) {
				cout << "There are no creatures in this room\n\n";
			}
		}

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
			player->unequipWeapon();
			break;
		case 9: //Unequip shield
			player->unequipShield();
			break;
		case 10: //Drop items from inventory
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
						player->dropItem(itt);
					}
				}
			}
		}
		break;
		default:
			cout << "Incorrect value \n\n";
		}
	}
}