#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <list>
#include <vector>


using namespace std;

enum TypeOfEntity {
	CREATURE,
	ROOM,
	EXIT,
	ITEM,
	PLAYER,
	ENTITY,
	NPC
};

class Entity
{
public:
	Entity(string name, string description, Entity* parent);
	~Entity();

	//Operators

	//Functions
	virtual void look() const;
	void changeParent(Entity* newParent, int childToRemoveFromOldParent);

	//Getters
	inline const string& getName() const { return this->name; }
	inline const string& getDescription() const { return this->description; }
	inline const TypeOfEntity& getTypeOfEntity() const { return this->typeOfEntity; }

	//Setters
	inline void setTypeOfEntity(TypeOfEntity typeOfEntity) {
		this->typeOfEntity = typeOfEntity;
	}
	inline void setNewParent(Entity* newParent) {
		this->parent = newParent;
	}
	inline void setDescription(string newDescription) {
		this->description = newDescription;
	}
public:
	string name;
	string description;
	TypeOfEntity typeOfEntity;
	Entity* parent;
	vector<Entity*> childs;

};

#endif