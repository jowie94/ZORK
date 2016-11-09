#include "world.h"



World::World()
{
}


World::~World()
{
}

bool World::Tick(const arglist &args)
{
	bool result = true;

	if (args.size() > 0)
	{
		result = ParseCommand(args);
	}

	GameLoop();
	return result;
}

void World::GameLoop()
{
	for (Entity* entity : entities)
	{
		entity->Tick();
	}
}

bool World::ParseCommand(const arglist &args)
{
	return true;
}
