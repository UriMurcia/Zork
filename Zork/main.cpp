#include <iostream>
#include "World.h"


using namespace std;

int main() {
	World world;

	//Create world
	world.initWorld();

	//Game loop
	while (world.getContinuePlaying()) {

		world.gameLoop();

	}

	return 0;
}