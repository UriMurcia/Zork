#include <iostream>
#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "windows.h"
#include "Exit.h"
#include <random>

Player::Player(const string name, string description, int health, int maxHealth, int maxNumItems, Room* room)
	: Creature(name, description, health, maxHealth, room) {
	this->maxNumItems = maxNumItems;

	this->currentRoom = room;
	this->setTypeOfEntity(PLAYER);
}

Player::~Player() {


}

void Player::lookInventory() const {
	if (childs.empty()) {
		cout << "Your inventory is empty\n\n";
	}
	else {
		//Iteration of all children (items) from player
		for (int i = 0; i < childs.size(); i++) {
			Item* itt = (Item*)childs[i];

			cout << itt->getName() << ": " << itt->getDescription();
			cout << "\n";
		}
		cout << "\n";
	}
}


bool Player::numItemsInInventory() { //List of all the items in the inventory
	if (childs.empty()) {
		cout << "Your inventory is empty\n\n";
		return false;
	}
	else {
		cout << "0: Exit\n";
		for (int i = 0; i < childs.size(); i++) {
			Item* itt = (Item*)childs[i];

			cout << i + 1 << ": " << itt->getName() << ": " << itt->getDescription();
			cout << "\n";
		}
		cout << "\n";
		return true;
	}
}
