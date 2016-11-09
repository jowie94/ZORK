#include "world.h"
#include "room.h"
#include "player.h"
#include "utils.h"


World::World()
{
	Room* first_room = new Room("Testing room", "Just a room");

	entities.push_back(first_room);

	Item* sword = new Item("Sword", "The mystic sword", first_room);

	entities.push_back(sword);

	player = new Player("Joel", "The boss", first_room);
	player->Life = 10;

	entities.push_back(player);
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
	bool ret = true;

	if (str_equals(args[0], "look"))
	{
		player->Look(args);
	}
	else if (str_equals(args[0], "pick") || str_equals(args[0], "take"))
	{
		ret = player->Pick(args);
	}

	return ret;
}
