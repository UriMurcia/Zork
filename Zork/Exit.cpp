#include "Exit.h"

Exit::Exit(string name, string description, Room* parentRoom, Room* destinationRoom, bool locked)
	: Entity(name, description, (Entity*)parentRoom) {
	this->destinationRoom = destinationRoom;
	this->locked = locked;

	this->setTypeOfEntity(EXIT);
}

Exit::~Exit() {


}