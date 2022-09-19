#include <iostream>
#include "Player.h"
#include "Room.h"
#include "Item.h"
#include "windows.h"
#include "Exit.h"
#include <random>

Player::Player(const string name, string description, int health, int maxHealth, int maxNumItems, Room* room, bool dead)
	: Creature(name, description, health, maxHealth, room, dead) {
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
			if (itt->getTypeOfItem() == WEAPON || itt->getTypeOfItem() == SHIELD) { //If item is shield or weapon: print stats
				cout << " MIN: " << itt->getMinStats() << " || MAX: " << itt->getMaxStats();
			}
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
			if (itt->getEquiped()) { //If item is already equpied: print (EQUIPED)
				cout << " (EQUIPED)";
			}
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

bool Player::attack(Npc* target) {

	if (target->getIsEnemy() && !target->dead) { //If target to attack is an enemy and is not dead
		//Default stats if there is not a weapon or shield equiped
		int maxAttack = 1;
		int minAttack = 1;
		int maxDefense = 0;
		int minDefense = 0;
		if (this->weapon != NULL) { //Get stats from the weapon equiped
			maxAttack = this->getDamageMax();
			minAttack = this->getDamageMin();
		}
		if (this->shield != NULL) { //Get stats from the weapon equiped
			maxDefense = this->getDefenseMax();
			minDefense = this->getDefenseMin();
		}

		//Same for enemy
		int maxAttackEnemy = 1;
		int minAttackEnemy = 1;
		int maxDefenseEnemy = 0;
		int minDefenseEnemy = 0;
		if (target->weapon != NULL) {
			maxAttackEnemy = target->getDamageMax();
			minAttackEnemy = target->getDamageMin();
		}
		if (target->shield != NULL) {
			maxDefenseEnemy = target->getDefenseMax();
			minDefenseEnemy = target->getDefenseMin();
		}

		//Initialize damage and defense
		int damage = 0;
		int defensed = 0;

		//To get random variables
		std::random_device rd;
		std::mt19937 gen(rd());

		while (this->health > 0 && target->health > 0) { //While the player and the enemy are not dead
			//Player Attack
			std::uniform_int_distribution<> dist(minAttack, maxAttack); //Random damage number between min and max stats
			damage = dist(gen);

			std::uniform_int_distribution<> distDefEnemy(minDefenseEnemy, maxDefenseEnemy); //Random defense number between min and max stats
			defensed = distDefEnemy(gen);

			if (defensed >= damage) { //If the defense is greater than the attack, we only deal 1 of damage
				defensed = damage - 1;
			}
			damage -= defensed; //Damage done is damage - defense
			target->health -= damage;

			cout << "Damage Done: " << damage << "\n";
			cout << "Damage stopped by" << target->getName() << ": " << defensed << "\n";
			cout << target->getName() << " Health: " << target->health << "\n\n";

			//Stop time of the game for 800ms
			cout.flush();
			Sleep(800);


			if (target->health > 0) { //Same for the enemy
				//Enemy Attack
				std::uniform_int_distribution<> distEnemy(minAttackEnemy, maxAttackEnemy);
				damage = distEnemy(gen);

				std::uniform_int_distribution<> distDef(minDefense, maxDefense);
				defensed = distDef(gen);

				if (defensed >= damage) {
					defensed = damage - 1;
				}
				damage -= defensed;

				this->health -= damage;

				cout << "Damage Received: " << damage << "\n";
				cout << "Damage stopped: " << defensed << "\n";
				cout << "Your Health: " << this->health << "\n\n";

				cout.flush();
				Sleep(800);
			}
		}
		if (target->health <= 0) { //If the enemy is the one dead
			target->dead = true;
			if (target->getName() == "Final boss") { //If the enemy dead is the final boss, the game is finished
				cout << "Mage: Congratulations traveler! You defeated the strongest enemy in the Paradise Tower!\n";
				cout << "Now, it is your turn to defend this tower, you are the king of the Paradise tower!\n";
				return true;
			}
			else { //If the enemy dead is not the final boss
				cout << "You killed " << target->getName() << "\n\n";
				int maxChilds = target->childs.size();
				for (int i = 0; i < maxChilds; i++) { //The enemy's items are droped
					cout << target->getName() << " dropped " << target->childs[0]->getName() << "\n";
					target->dropItem((Item*)target->childs[0]);
				}
				cout << "\n\n";
			}

		}
		if (this->health <= 0) { //If the player dies, the game is finished
			cout << "YOU DIED!";
			return true;
		}
		else { //If the one dead is the enemy, we return false to not finish the game
			return false;
		}
	}
	else { //If the creature in the room is not an enemy or is dead
		if (target->dead) {
			cout << target->getName() << " is dead. \n\n";
			target->setDescription("(DEAD)");
		}
		else {
			cout << "You cannot attack " << target->getName() << "\n\n";
		}
		return false;
	}
}

void Player::useItem(Item* itemToUse, int numChildToDelete) {
	if (itemToUse->getTypeOfItem() == WEAPON || itemToUse->getTypeOfItem() == SHIELD) {
		cout << "Weapons and shields cannot be used\n\n";
	}
	else {

		if (itemToUse->getTypeOfItem() == POTION) { //Use of potion
			//Restore health
			this->health = maxHealth;
			cout << "Health restored to " << this->health << "\n\n";

			//Delete potion
			vector<Entity*>::iterator q = this->childs.begin();
			q += numChildToDelete;
			vector<Entity*>::iterator p = this->childs.erase(q);

			itemToUse = NULL;
		}
		else {
			if (itemToUse->getTypeOfItem() == CHEST) { //Use of chest
				//Change parent of the key inside of it (new parent = player)
				itemToUse->childs[0]->changeParent(this, 0);
				cout << "Chest opened. You obtained key.\n\n";

				//Delete chest
				vector<Entity*>::iterator q = this->childs.begin();
				q += numChildToDelete;
				vector<Entity*>::iterator p = this->childs.erase(q);

				itemToUse = NULL;
			}
			else {
				if (itemToUse->getTypeOfItem() == KEY) { //Use of potion
					if (this->parent->getName() == "Floor 3") { //If key used in the correct room

						//Iteration to get the exit of the door closed
						for (vector<Entity*>::const_iterator ex = this->parent->childs.begin(); ex != this->parent->childs.cend(); ++ex)
						{
							if ((*ex)->typeOfEntity == EXIT && (*ex)->getName() == "Go floor 4")
							{
								Exit* exit = (Exit*)(*ex);
								//Open door
								exit->setLocked(false);
							}
						}
						cout << "Door opened\n\n";

						//Delete key
						vector<Entity*>::iterator q = this->childs.begin();
						q += numChildToDelete;
						vector<Entity*>::iterator p = this->childs.erase(q);

						itemToUse = NULL;
					}
					else {
						cout << itemToUse->getName() << " cannot be used in this room\n\n";
					}
				}
			}
		}
	}
}
