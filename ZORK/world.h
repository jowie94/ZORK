#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>
#include <list>
#include "entity.h"
#include "player.h"

class World
{
public:
	World();
	~World();

	bool Tick(const arglist &args);
	
private: 
	bool ParseCommand(const arglist &args);
	void GameLoop();

	std::list<Entity*> entities;
	Player* player;
};

#endif // _WORLD_H_
