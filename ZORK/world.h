#ifndef _WORLD_H_
#define _WORLD_H_

#include <vector>
#include <list>
#include "entity.h"

class World
{
public:
	World();
	~World();

	bool Tick(const std::vector<std::string> &args);
	
private: 
	bool ParseCommand(const std::vector<std::string>& args);
	void GameLoop();

	std::list<Entity*> entities;
};

#endif // _WORLD_H_
