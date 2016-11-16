#include "world.h"
#include "room.h"
#include "player.h"
#include "utils.h"
#include "exit.h"
#include "SimpleAI.h"
#include "finalroom.h"


World::World()
{
	puzzles_solved = new vector<bool>(1, false);

	Room* first_room = new Room("Central room", "The central room");
	FinalRoom* second_room = new FinalRoom("A second room", "The east room", "You're escaping", puzzles_solved);

	entities.push_back(first_room);
	entities.push_back(second_room);

	Item* key = new Item("Key", "Opens the east room", first_room);
	key->ItemType = KEY;

	entities.push_back(key);

	Exit* door = new Exit("east", "west", "A tiny door", first_room, second_room, key);

	entities.push_back(door);

	Item* box = new Item("Box", "A simple box", first_room);
	box->Openable = box->Closed = true;
	Item* sword = new Item("Sword", "The mystic sword", box);
	sword->ItemType = WEAPON;
	sword->MaxValue = 2;
	sword->MinValue = 1;

	entities.push_back(box);
	entities.push_back(sword);

	player = new Player("Joel", "The boss", first_room);
	player->Life = 10;

	entities.push_back(player);

	Creature* enemy1 = new Creature("enemy", "A Simple enemy", first_room);
	enemy1->AI = new SimpleAI(enemy1);
	enemy1->Target = player;

	entities.push_back(enemy1);
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

bool World::AllPuzzlesSolved() const
{
	return all(*puzzles_solved);
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
	else if (str_equals(args[0], "drop"))
	{
		ret = player->Drop(args);
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
	else if (str_equals(args[0], "unlock"))
	{
		ret = player->UnLock(args);
	}
	else if (str_equals(args[0], "lock"))
	{
		ret = player->Lock(args);
	}
	else if (str_equals(args[0], "inventory"))
	{
		player->Inventory();
	}
	else if (str_equals(args[0], "equip"))
	{
		ret = player->Equip(args);
	}
	else if (str_equals(args[0], "unequip"))
	{
		ret = player->UnEquip(args);
	}
	else if (str_equals(args[0], "attack"))
	{
		ret = player->Attack(args);
	}
	else if (str_equals(args[0], "stats"))
	{
		player->Stats(args);
	}
	else if (str_equals(args[0], "examine"))
	{
		ret = player->Examine(args);
	}
	else if (str_equals(args[0], "loot"))
	{
		ret = player->Loot(args);
	}
	else
	{
		ret = false;
	}

	return ret;
}
