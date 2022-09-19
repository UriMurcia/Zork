#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>

using namespace std;

class Player;
class Entity;

class World
{
public:
	World();
	~World();

	void initWorld();
	void gameLoop();
	void createAllEntities(string name);


	//Getters
	inline bool getContinuePlaying() const { return this->continuePlaying; }

	//Setters
	void setContinuePlaying();

private:
	int continuePlaying;
	Player* player;
	vector<Entity*> entities;

};



#endif