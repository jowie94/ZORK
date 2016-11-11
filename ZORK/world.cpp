#include "world.h"
#include "room.h"
#include "player.h"
#include "utils.h"
#include "exit.h"


World::World()
{
	Room* first_room = new Room("Central room", "The central room");
	Room* second_room = new Room("A second room", "The east room");

	entities.push_back(first_room);
	entities.push_back(second_room);

	Exit* door = new Exit("east", "west", "A tiny door", first_room, second_room);

	entities.push_back(door);

	Item* sword = new Item("Sword", "The mystic sword", first_room);

	entities.push_back(sword);

	player = new Player("Joel", "The boss", first_room);
	player->Life = 10;

	entities.push_back(player);
}


World::~World()
{}

bool World::Tick(arglist &args)
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

bool World::ParseCommand(arglist &args)
{
	bool ret = true;

	// TODO: Improve that!!!
	if (str_equals(args[0], "look"))
	{
		player->Look(args);
	}
	else if (str_equals(args[0], "pick") || str_equals(args[0], "take"))
	{
		ret = player->Pick(args);
	}
	else if (str_equals(args[0], "north") || str_equals(args[0], "n") || str_equals(args[0], "south") || str_equals(args[0], "s") 
		|| str_equals(args[0], "east") || str_equals(args[0], "e") || str_equals(args[0], "west") || str_equals(args[0], "w"))
	{
		complete_direction(args[0]);
		player->Move(args);
	}
	else if (str_equals(args[0], "open"))
	{
		player->Open(args);
	}
	else if (str_equals(args[0], "close"))
	{
		player->Close(args);
	}
	else
	{
		ret = false;
	}

	return ret;
}
