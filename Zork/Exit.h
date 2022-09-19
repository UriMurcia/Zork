#ifndef EXIT_H
#define EXIT_H

#include "Entity.h"

class Room;

class Exit : public Entity
{
public:
	Exit(string name, string description, Room* parentRoom, Room* destinationRoom, bool locked);
	~Exit();

	//Operators

	//Functions

	//Getters
	inline const Room* getDestination() const { return this->destinationRoom; }
	inline const bool& isLocked() const { return this->locked; }

	//Setters
	inline void setLocked(bool lock) { this->locked = lock; }

private:
	Room* destinationRoom;
	bool locked;
};

#endif