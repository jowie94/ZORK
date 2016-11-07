#include "world.h"



World::World()
{
}


World::~World()
{
}

bool World::Tick(const std::vector<std::string>& args)
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

bool World::ParseCommand(const std::vector<std::string>& args)
{
	return true;
}
