#include <iostream>
#include "Entity.h"
#include "Room.h"

Entity::Entity(string name, string description, Entity* parent = NULL) {
	this->name = name;
	this->description = description;
	this->parent = parent;


	this->setTypeOfEntity(ENTITY);

	if (parent != NULL) {
		this->parent->childs.push_back(this);
	}
}

Entity::~Entity() {


}

void Entity::look() const {
	cout << this->getName() + ": " + this->getDescription() + "\n\n";
}

void Entity::changeParent(Entity* newParent, int childToRemoveFromOldParent) {
	if (this->typeOfEntity != NULL) {
		vector<Entity*>::iterator q = this->parent->childs.begin(); //begin iterator
		q += childToRemoveFromOldParent; //sum number of the child
		vector<Entity*>::iterator p = this->parent->childs.erase(q); //Remove child
		this->parent = newParent; //Attach new parent
		parent->childs.push_back(this); //Add to the child list of the parent

	}
}

