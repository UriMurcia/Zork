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
			if (itt->getEquiped()) { //If item is equpied: print (EQUIPED)
				cout << " (EQUIPED)";
			}
			cout << "\n";
		}
		cout << "\n";
	}
}

void Player::unequipWeapon() {
	if (weapon == NULL) {
		cout << "You do not have weapons equiped\n\n";
	}
	else {
		cout << weapon->getName() << " unequiped\n\n";
		weapon->setEquiped(false);
		weapon = NULL;
	}
}

void Player::unequipShield() {
	if (shield == NULL) {
		cout << "You do not have shields equiped\n\n";
	}
	else {
		cout << shield->getName() << " unequiped\n\n";
		shield->setEquiped(false);
		shield = NULL;
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

void Player::equipItem(Item* itemToEquip) {
	if (itemToEquip->getTypeOfItem() == WEAPON) {
		if (weapon != NULL) {
			cout << "\n" << "There is already a weapon equiped. Unequip it before equiping another one";
		}
		else {
			weapon = itemToEquip;
			weapon->setEquiped(true);
			cout << "\n" << weapon->getName() << " EQUIPED";
		}
	}
	else {
		if (itemToEquip->getTypeOfItem() == SHIELD) {
			if (shield != NULL) {
				cout << "\n" << "There is already a shield equiped. Unequip it before equiping another one";
			}
			else {
				shield = itemToEquip;
				shield->setEquiped(true);
				cout << "\n" << shield->getName() << " EQUIPED";
			}
		}
		else { //If item to equip is not a weapon or shield
			cout << "You can only equip weapons and shields";
		}
	}
	cout << "\n\n\n";
}