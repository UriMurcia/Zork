#ifndef ROOM_H
#define ROOM_H

#include "Entity.h"
#include <string>

using namespace std;

class Exit;

class Room : public Entity
{
public:
	Room(string name, string description);
	~Room();

	//Operators

	//Functions
	void look() const;
	Exit* showExits() const;

	//Getters

	//Setters

private:

};

#endif