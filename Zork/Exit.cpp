#include "Exit.h"

Exit::Exit(string name, string description)
	: Entity(name, description, NULL) {

	this->setTypeOfEntity(EXIT);
}

Exit::~Exit() {


}